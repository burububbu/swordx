#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include "list.h"

void openFile(const char*);

int main(void)
{
	FILE *fd;
	char buf[200];
	char *res;


	/* apre il file */
	fd=fopen("/home/michele/swordx/test.txt", "r");
	if( fd==NULL ) {
    perror("Errore in apertura del file");
    exit(1);
    }


	/* legge e stampa ogni riga */
	while(1) 
	{
		res = fgets(buf, 2000, f);
		if( res==NULL )
		  break;
	  
		storeString(swordx,buf);
	}


	/* chiude il file */
	fclose(fd);

	//create the file swordnordered.out (it isn't ordered)		
	int file_created;
	
	file_created=creat("swordnordered.out", 0644);
	if(file_created == 1) {printf("error");}
	
	//open the file sword.out 
	
	FILE *fp;
	
	fp = fopen("./swordnordered.out", "a");
	
	if (fp == NULL){
		exit(-1);
		}
		
	//write on the file all word and occurrence
	
	node *po = swordx -> first; //returns first node
	
	while (i < countWord(swordx,buf))
	{
		fputs((po -> word), fp);
		int number = (po -> occurrence);
		fprintf(fp, " %d \n", number);
		po = (po -> next);
	}

	{
		fputs((po -> word), fp);
		int number = (po -> occurrence);
		fprintf(fp, " %d \n", number);
		po = (po -> next);
	} while (po -> next != NULL);
		
	fflush(fp);
	fclose(fp);
	
	//write this on the shell
	
	system("/bin/sh -c sort  <./swordnordered.out > sword.out");
	
	if (remove("swordnordered.out") != 0) printf("Unable to delete the file");
}