#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include "utils.h"
#include "global.h"

int recursive_flag;
int follow_flag;
int alpha_flag;
char *fileToExclude;
int numMin;
char *fileToIgnore;
char *logFile;


/* controlla che il nome sia un file o una directory, nel caso in cui fosse una directory */
void checkName(list* lst, char* filename){
	/* se NON è una directory fa l'update della lista passa a updateList il file, se no
	 *  apre la directory, mette tutti i file nella directory in un'array di file
	 * fa l'updateList su ognuno di loro */
	 
	 // 0 false 1 true
	if(isDirectory(filename)== 0){
		updateList(lst, filename);
	}
	else{
		fileInDirUpdate(lst, filename, 0); 
		}
	}

void updateList(list* lst, char* filename){
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
    	storeString(lst, buf);
	}
	} 
}

void writeOnFile(list* lst, char* outputFile){
	FILE *fp;
	/* from appen mode to write mode*/
	fp = fopen(outputFile ,"w");
	if (fp == NULL){
		exit(-1);
		}
	/* write on the file all word and occurrence*/
	node *po = lst-> first;
	while (po-> next != NULL) {
		fprintf(fp, "%s ", po -> word);
		int number = (po -> occurrence);
		fprintf(fp, " %d \n", number);
		po = (po -> next);
	};
	fflush(fp);
	fclose(fp);
}

/*sub is 0 if the dir is a subdir, 1 otherwise
 * 1 -> not recursion*/
int fileInDirUpdate (list* lst, char* filename, int sub){
	DIR *dp;
	struct dirent *ep;
	dp = opendir (filename);
	if (dp != NULL)
    { 
		while (ep = readdir (dp)){
			/* EXCLUDE FILE */
			if ((fileToExclude != NULL) && (strcmp(ep -> d_name, fileToExclude) == 0)){
				 printf ("\n escludo il file %s dalla statistica\n", ep -> d_name);
			}
			else {
				int sizePath =  strlen(filename) + strlen(ep -> d_name);
				char name[sizePath];
				strcpy(name, filename);
				strcat(name, ep -> d_name );
				if (isRegular(name) == 1){
					printf("%s è regolare\n", name);
					updateList(lst, name);
					}
				else {
					 printf("/n%s non è regolare\n", name); 
					 if (name[strlen(name)-1] != '.'){  /*ultimo char è .*/
					 if (sub == 0){
						 /*RECURSIVE*/
						if(recursive_flag == 1){
							if (!isLink(name))
							{
							char newname[sizePath + 1];
							strcpy(newname,name);
							strcat(newname, "/");
							if (isDirectory(newname)) fileInDirUpdate(lst, newname, 1);
							}
						};
						 /*FOLLOW*/
						if ((follow_flag == 1) && isLink(name)){
							char newname[sizePath + 1];
							strcpy(newname,name);
							strcat(newname, "/");
							fileInDirUpdate(lst, newname, 1);
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

