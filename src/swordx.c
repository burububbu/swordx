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
#include "parLog.h"

/* flags */
static int recursive_flag;
static int follow_flag;
static int alpha_flag;
static int sort_flag;

static char *fileToExclude;
static int numMin = 0;
static char *wordToIgnore = NULL;
static char *logFile;
char *outputFile = "swordx.out";

int count[2] = {0,0};

void sort();
void checkName(char*);
void counter(node*);
void updateList(char*);
void UpdateListwLog(char*);
void writeOnFile();
void writeLogFile();
void readIgnore();
void printHelp();
char* canPath(char*);


int isDirectory(char*);
int isRegular(char*);
int isLink(char*);
int fileInDirUpdate(char*);


static node* firstNode;
static parLog* firstLogNode;
static char ** wordsToIgnore;

extern char *canonicalize_file_name(const char*);


int main (int argc, char *argv[]) 
{
	char **files;
	int c;
	
	while (1)
	{
		  static struct option long_options[] =
		  {
			  /* These options set a flag. */
			  {"recursive", no_argument, &recursive_flag, 1},
			  {"follow", no_argument, &follow_flag, 1},
			  {"alpha", no_argument, &alpha_flag, 1},
			  {"sortbyoccurrency", no_argument, &sort_flag, 1},
			  /* These options set a flag.
				 We distinguish them by their indices. */
			  {"help",  no_argument, 0, 'h'},
			  {"explude",  required_argument, 0, 'e'},
			  {"min",  required_argument, 0, 'm'},
			  {"ignore",  required_argument, 0, 'i'},
			  {"log",  required_argument, 0, 'l'},
			  {"output",  required_argument, 0, 'o'},
			  {0, 0, 0, 0}
		  };
		  
        int option_index = 0;
		c = getopt_long_only (argc, argv, "he:m:i:l:o:", long_options, &option_index);
	  
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
		  case 'h':
				printHelp();
				exit(0);
			
		  case 'e':
					fileToExclude = optarg;
					break;
		  case 'm':
					numMin = atoi(optarg);
					break;
		  case 'i':
					wordToIgnore = optarg;
					readIgnore();
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
		
		while (optind < argc)
		{
			files[z] = argv[optind];
			optind++;
			z++;
		}
			
		for (int j= 0; j < z; j++)
			checkName(files[j]);
			
		free(files);
		writeOnFile(outputFile);
		sort(); 
		
		if (logFile != NULL)
			writeLogFile();
	}
	else
	{
		printf("There aren't input files\r\n");
		exit(0);
	}
}

void sort()
{
	if (sort_flag == 0)
	{
		int size = ((strlen(outputFile)*2) + 9); /* 9 -> 1 + 8 (length di " sort -o " )*/
		char inout[size];
		strcpy(inout, "sort -o ");
		strcat(inout, outputFile);
		strcat(inout, " ");
		strcat(inout, outputFile);
		system(inout);
	}
	/*SORT BY OCCURRENCE*/
	else 
	{
		int size = ((strlen(outputFile)*2) + 17); /* 17 -> 1 + 16 (length di " sort -n -o " )*/
		char inout[size];
		strcpy(inout, "sort -k 2 -n -o ");
		strcat(inout, outputFile);
		strcat(inout, " ");
		strcat(inout, outputFile);
		system(inout);
	}
}


/* controlla che il nome sia un file o una directory, nel caso in cui fosse una directory */
void checkName(char* filename)
{
	filename = canPath(filename);
	/* se non � una directory fa l'update della lista passa a updateList il file, se no
	 *  apre la directory, controlla i file e fa l'updateList su ognuno di loro*/
	if(isDirectory(filename)== 0)
	{
		if (isRegular(filename) == 1)
		{
			if (logFile == NULL)
				updateList(filename);
			/* LOG FILE __exec time*/
			else 
				UpdateListwLog(filename);
		}
	}
	else
		fileInDirUpdate(filename);
}

void counter(node* nod)
{
	if(nod != NULL)
		count[0] += 1;
	else
		count[1] += 1;
}

void updateList(char* filename)
{
	FILE *fd;
	char buf[40];
	node* app;
	fd = fopen(filename, "r");
	
	if( fd==NULL )
	{
		perror("Errore in apertura del file");
		exit(1);
	}
	else 
	{
		/* assumes no word exceeds length of 40 */
		while (fscanf(fd, " %40s", buf) == 1) 
		{	
			if (firstNode == NULL)
			{
				firstNode = storeString(firstNode,buf,alpha_flag,numMin, wordsToIgnore);
				counter(firstNode);
			}
			else 
			{
				app = storeString(firstNode,buf,alpha_flag,numMin,wordsToIgnore);
				counter(app);
			}
		}
	}
}

void writeOnFile()
{
	FILE *fp;
	
	/* from append mode to write mode*/
	fp = fopen(outputFile ,"w");
	
	if (fp == NULL)
	{
		printf("Error in output file");
		exit(-1);
	}
	
	/* write on the file all word and occurrence*/
	node *po = firstNode;
	while (po != NULL) 
	{
		fprintf(fp, "%s ", po -> word);
		int number = (po -> occurrence);
		fprintf(fp, " %d \n", number);
		po = (po -> next);
	}
	
	fflush(fp);
	fclose(fp);
}


void writeLogFile()
{
	FILE *fp;
	fp = fopen(logFile ,"w");
	
	if (fp == NULL)
	{
		printf("Error in log file");
		exit(-1);
	}
	
	parLog *app = firstLogNode;
	do
	{
		fprintf(fp, "%s ", app -> name);
		fprintf(fp, "  %d ", app -> cw);
		fprintf(fp, "  %d ", app -> iw);
		fprintf(fp, "  %f\n", app -> time);
		app = app -> next;
	} while(app != NULL);
	
	fflush(fp);
	fclose(fp);
}

/*sub is 0 if the dir is a subdir, 1 otherwise
 * 1 -> not recursion*/
int fileInDirUpdate (char* path)
{
	DIR *dp;
	struct dirent *ep;
	dp = opendir (path);
	
	if (dp != NULL)
    { 
		while ((ep = readdir (dp)))
		{
			/* EXCLUDE FILE */
			if ((fileToExclude != NULL) && (strcmp(ep -> d_name, fileToExclude) == 0))
			{
			}
			else if (ep -> d_name[0] != '.')
			{
				int sizePath =  strlen(path) + strlen(ep -> d_name) + 1;
				
				char filename[sizePath];
				
				strcpy(filename, path);
				strcat(filename, "/");
				strcat(filename, ep -> d_name );
				
				if (isRegular(filename) == 1)
				{
					if (logFile != NULL)
						UpdateListwLog(filename);
					else 
						updateList(filename);
				}
				else 
				{ 
					 /*RECURSIVE*/
					if(recursive_flag == 1)
					{
						if (!isLink(filename))
						{
							if (isDirectory(filename)) fileInDirUpdate(filename);
						}
					}
					 /*FOLLOW*/
					if ((follow_flag == 1) && isLink(filename))
					{
						fileInDirUpdate(filename);
					} 
				}
				}
			}
		(void) closedir (dp);
	}
	else 
	{
		perror ("Couldn't open the directory");
	}
	
	return 0;
}

void UpdateListwLog(char* filename)
{
	clock_t t;
	t = clock();
	
	updateList(filename);
	parLog* n =createLogNode(filename, count[0], count[1], firstLogNode);
	if (firstLogNode == NULL) 
		firstLogNode = n;
	
	t = clock() - t;
	
	double time_taken = ((double)t)/ CLOCKS_PER_SEC;
	n -> time = time_taken;
	
	count[0] = 0;
	count[1] = 0;
}

void readIgnore()
{
	wordsToIgnore = malloc(sizeof(char**));
	int i = 0;
	FILE *fd;
	char buf[40];
	fd = fopen(wordToIgnore, "r");
	
	if( fd==NULL )
	{
		perror("Errore in apertura del file");
		exit(1);
	}
	else 
	{
		/* assumes no word exceeds length of 40 */
		while (fscanf(fd, " %40s", buf) == 1) 
		{
			wordsToIgnore[i] = strdup(buf);
			i++;
			wordsToIgnore = (char**) realloc(wordsToIgnore, sizeof(char*)* i+1);
		}
	}
}

void printHelp()
{
	printf("swordx [options] [inputs]\n");
	printf("\tswordx counts the occurrencies of each word input files and print them into a new output file.\n");
	printf("\n");
	printf("\t[inputs]\n");
	printf("\t\t files or Directory to read\n");
	printf("\t[options]\n");
	printf("\t\t -h | -help : print help message \n");
	printf("\t\t -r | -recursive : follow subdirectories \n");
	printf("\t\t -o <file> | -output <file> : write the result in the <file> (sword.out by default)\n");
	printf("\t\t -f | -follow : follow links \n");
	printf("\t\t -e <file> | -explude <file> : exclude <file> from the statistic \n");
	printf("\t\t -a | -alpha : consider alphabetic characters only \n");
	printf("\t\t -m <num> | -min <num> : consider words with at least <num> characters\n");
	printf("\t\t -i <file> | -ignore <file> : exclude words contained in <file> are ignored\n");
	printf("\t\t -s | -sortbyoccurrency : sort by number of occurrences (file is sorted by alphabetical order by default)\n");
	printf("\t\t -l <file> | -log <file> : write log informations in <file> \n");
	printf("\t\t\t the row sintax of this file is \n");
	printf("\t\t\t <name> cw iw time \n");
	printf("\t\t\t\t <name> : processed file\n");
	printf("\t\t\t\t cw : recorded words\n");
	printf("\t\t\t\t iw : ignored words\n");
	printf("\t\t\t\t time : file processing time");
	printf("\n");
}

char* canPath(char* path)
{
	char* newpath = canonicalize_file_name(path);
	
	if (newpath == NULL)
	{
		printf("Percorso '%s' non valido\r\n",path);
		exit(EXIT_FAILURE);
	}
	return newpath;
}

int isDirectory(char *path) 
{
   struct stat statbuf;
   
   if (stat(path, &statbuf) != 0)
       return 0;
   
   return S_ISDIR(statbuf.st_mode);
}

int isRegular(char* path)
{
	struct stat path_stat;
    stat(path, &path_stat);
    
    return S_ISREG(path_stat.st_mode);
}

int isLink(char* path)
{
	 struct stat path_stat;
	 lstat(path, &path_stat);
	 
	 return S_ISLNK(path_stat.st_mode);
}
