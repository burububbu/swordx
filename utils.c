#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include "utils.h"

/* controlla che il nome sia un file o una directory, nel caso in cui fosse una directory */
void checkName(list* lst, char* filename){
	
	/* se NON è una directory fa l'update della lista passa a updateList il file, se no
	 *  apre la directory, mette tutti i file nella directory in un'array di file
	 * fa l'updateList su ognuno di loro */
	 
	 // 0 false 1 true
	if( isDirectory(filename)== 0 ){
		updateList(lst, filename);
	}
	else{
		fileInDirUpdate(lst, filename);
		}
	}

void updateList(list* lst, char* filename){
	
	FILE *fd;
	char buf[40];
	/*open the file*/
	fd = fopen(filename, "r");
	
	if( fd==NULL ){
		perror("Errore in apertura del file");
		exit(1);
	}
	else {
	//printf("\n non ci sono problemi con l'apertura del file %s", filename);}
    /* assumes no word exceeds length of 40 */
    while (fscanf(fd, " %40s", buf) == 1) {
        addWord(lst, buf);
    }
}
}

void writeOnFile(list* lst, char* outputFile){
	/* open/create output file */	
	FILE *fp;
	fp = fopen(outputFile ,"a");
	if (fp == NULL){
		exit(-1);
		}
	/* write on the file all word and occurrence*/
	node *po = lst-> first;
	while (po!= NULL) {
		fputs((po -> word), fp);
		int number = (po -> occurrence);
		fprintf(fp, " %d \n", number);
		po = (po -> next);
	};
	fflush(fp);
	fclose(fp);
}

int isDirectory(char *path) {
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}

int fileInDirUpdate(list* lst, char* filename){
	DIR *dp;
	struct dirent *ep;
	dp = opendir (filename);
	if (dp != NULL)
    {
		while (ep = readdir (dp)){
			printf (ep -> d_name);
			//printf ("\n");
			/* concatenare path/file */
			int sizePath =  strlen(filename) + strlen(ep -> d_name);
			char name[sizePath];
			strcpy(name, filename);
			strcat(name, ep -> d_name );
			if (isRegular(name) == 1){
				printf(" è regolare\n quindi \n");
				updateList(lst, name); 
			}
			else{
				 printf(" non è regolare\n"); 
			}
			
			
    }
      (void) closedir (dp);
    }
  else
    perror ("Couldn't open the directory");

  return 0;
}

int isRegular(char* path){
	struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
	}



