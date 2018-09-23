#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include "node.h"


/* flags */
static int recursive_flag;
static int follow_flag;
static int alpha_flag;

static int sort_flag;

static char *fileToExclude;
static int numMin = 0;
static char *fileToIgnore;
static char *logFile;

char *outputFile = "sword.out";


/*struttura utilizzata in CheckName() e fileInDirUpdate()*/
typedef struct parLog{
	char* name;
	int cw;
	int iw;
	double time;
	struct parLog *next;
}parLog;

void sort();
void checkName(char*);
void updateList(char*);
void UpdateListwLog(char*);
void writeOnFile();
void writeLogFile();


int isDirectory(char*);
int isRegular(char*);
int isLink(char*);
int fileInDirUpdate(char*, int); /*lista, file name, boolean is is a  sub or not*/
char* createPath (char*, char*);
parLog* createLogNode(char*);


/*deve cambiare in firstNode*/
static node* firstNode;

static parLog* firstLogNode;

/*
 * argc num parametri
 * argv array di puntatori ai parametri (parti da argv[1])
 * 
 * */
int main (int argc, char *argv[]) {
	char **files;
	int c;
	while (1){
		  static struct option long_options[] =
        {
          /* These options set a flag. */
          {"recursive", no_argument, &recursive_flag, 1},
          {"follow", no_argument, &follow_flag, 1},
          {"alpha", no_argument, &alpha_flag, 1},
          {"sortbyoccurrence", no_argument, &sort_flag, 1},
          /* These options don’t set a flag.
             We distinguish them by their indices. */
          {"explude",  required_argument, 0, 'e'},
          {"min",  required_argument, 0, 'm'},
          {"ignore",  required_argument, 0, 'i'},
          {"log",  required_argument, 0, 'l'},
          {"output",  required_argument, 0, 'o'},
          {0, 0, 0, 0}
        };
        int option_index = 0;

		c = getopt_long_only (argc, argv, "e:m:i:l:o:", long_options, &option_index);
	  
		/* Detect the end of the options. */
		if (c == -1) break;
        
		switch (c)
		{
		  case 0:
			  /* If this option set a flag, do nothing else now. */
			  if (long_options[option_index].flag != 0) break;
			  printf ("option %s", long_options[option_index].name);
			  if (optarg)
				printf (" with arg %s", optarg);
			  printf ("\n");
			  break;
			
		  case 'e':
				fileToExclude = optarg;
				break;
		  case 'm':
				numMin = atoi(optarg);
				break;
		  case 'i':
				fileToIgnore = optarg;
				break;
		  case 'l':
				logFile = optarg;
				break;
		  case 'o':
				outputFile = optarg;
				break;
		  case '?':
			  /* getopt_long already printed an error message. */
				break;
		default:
				abort ();
			 }
	}
/* Print any remaining command line arguments (not options). sono quindi i file di input */
  if (optind < argc)
    {
	int size = (argc - optind);
	files = calloc(size, sizeof(char**));
	int z = 0;
    printf ("input files: \n ");
    while (optind < argc){
		files[z] = argv[optind];
		optind++;
		printf ("%s \n", files[z]);
		z++;
		}
	for (int j= 0; j < z; j++){
		checkName(files[j]);
		}
	free(files);
	writeOnFile(outputFile);
	sort(); 
	if (logFile != NULL) { 
		writeLogFile();
    }
    } 
  else("There aren't input files");
  exit (0);
}

void sort(){
	if (sort_flag == 0){
		int size = ((strlen(outputFile)*2) + 10); /* 10 -> 1 + 9 (length di " sort -o " )*/
		char inout[size];
		strcpy(inout, "sort -o ");
		strcat(inout, outputFile);
		strcat(inout, " ");
		strcat(inout, outputFile);
		system(inout);
		}
	/*SORT BY OCCURRENCE*/
	 else {}
	}


/* controlla che il nome sia un file o una directory, nel caso in cui fosse una directory */
void checkName(char* filename){
	/* se NON è una directory fa l'update della lista passa a updateList il file, se no
	 *  apre la directory, controlla i file e fa l'updateList su ognuno di loro */

	if(isDirectory(filename)== 0){
	
		if (logFile == NULL){
			updateList(filename);
		}
		/* LOG FILE __exec time*/
		else {
			UpdateListwLog(filename);
			}
	}
	else{
		fileInDirUpdate(filename, 0); 
		}
	}


void updateList(char* filename){
	FILE *fd;
	char buf[40];
	fd = fopen(filename, "r");
	
	if( fd==NULL ){
		perror("Errore in apertura del file");
		exit(1);
	}
	else {
    /* assumes no word exceeds length of 40 */
    while (fscanf(fd, " %40s", buf) == 1) {
		if (firstNode == NULL){
			firstNode = storeString(firstNode,buf,alpha_flag,numMin);
			printf("\nLa parola del primo nodo è %s \n", firstNode -> word);
			}
    	else {
			storeString(firstNode,buf,alpha_flag,numMin);
		}
	}
	} 
}

void writeOnFile(){
	FILE *fp;
	/* from append mode to write mode*/
	fp = fopen(outputFile ,"w");
	if (fp == NULL){
		printf("Error in output file");
		exit(-1);
		}
	/* write on the file all word and occurrence*/
	node *po = firstNode;
	while (po != NULL) {
		fprintf(fp, "%s ", po -> word);
		int number = (po -> occurrence);
		fprintf(fp, " %d \n", number);
		po = (po -> next);
	};
	fflush(fp);
	fclose(fp);
}


void writeLogFile(){
	FILE *fp;
	fp = fopen(logFile ,"w");
	if (fp == NULL){
		printf("Error in log file");
		exit(-1);
		}
	parLog *app = firstLogNode;
	do{
		fprintf(fp, "%s ", app -> name);
		fprintf(fp, "  %d ", app -> cw);
		fprintf(fp, "  %d ", app -> iw);
		fprintf(fp, "  %f\n", app -> time);
		app = app -> next;
	} while(app != NULL);
	fflush(fp);
	fclose(fp);
	printf("\nFile di log %s creato!\n", logFile);
	};

/*sub is 0 if the dir is a subdir, 1 otherwise
 * 1 -> not recursion*/
int fileInDirUpdate (char* path, int sub){
	DIR *dp;
	struct dirent *ep;
	dp = opendir (path);
	if (dp != NULL)
    { 
		while (ep = readdir (dp)){
			/* EXCLUDE FILE */
			if ((fileToExclude != NULL) && (strcmp(ep -> d_name, fileToExclude) == 0)){
				 printf ("\n escludo il file %s dalla statistica\n", ep -> d_name);
			}
			else {
				int sizePath =  strlen(path) + strlen(ep -> d_name);
				
				char filename[sizePath];
				
				strcpy(filename, path);
				strcat(filename, ep -> d_name );
				
				if (isRegular(filename) == 1){
				//	printf("%s è regolare\n", filename);
					if (logFile != NULL){
						UpdateListwLog(filename);
					}
					else {
						updateList(filename);
						}
					}
				else {
					// printf("/n%s non è regolare\n", filename); 
					 if (filename[strlen(filename)-1] != '.'){  /*ultimo char è .*/
					 if (sub == 0){
						 /*RECURSIVE*/
						if(recursive_flag == 1){
							if (!isLink(filename))
							{
							char newname[sizePath + 1];
							strcpy(newname,filename);
							strcat(newname, "/");
							if (isDirectory(newname)) fileInDirUpdate(newname, 1);
							}
						};
						 /*FOLLOW*/
						if ((follow_flag == 1) && isLink(filename)){
							char newname[sizePath + 1];
							strcpy(newname,filename);
							strcat(newname, "/");
							fileInDirUpdate(newname, 1);
							} 
						 } 
					}
				}
		} 
	}
  (void) closedir (dp);
  }
  else {
    perror ("Couldn't open the directory");
   }
  return 0;
}

parLog* createLogNode(char* filename){
	parLog *n = malloc(sizeof(parLog));
	n -> name = strdup(filename); /*duplica stringhe, cpia dati da un puntatore ad un altro*/
	n -> cw = 0;
	n -> iw = 0;
	n -> next = NULL;
	
	if (firstLogNode == NULL){
		firstLogNode = n;
		}
	else {
		parLog* app = firstLogNode;	
		while (app -> next  != NULL){	
			app = app-> next;
		}
		app -> next = n;
		}
	return n;
	};

void UpdateListwLog(char* filename){
	parLog* n =createLogNode(filename);
	clock_t t;
	t = clock();
	updateList(filename);
	t = clock() - t;
	double time_taken = ((double)t)/ CLOCKS_PER_SEC;
	n -> time = time_taken;
};

int isDirectory(char *path) {
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}

int isRegular(char* path){
	struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
	}

int isLink(char* path){
	 struct stat path_stat;
	 lstat(path, &path_stat);
	 return S_ISLNK(path_stat.st_mode);
	}
