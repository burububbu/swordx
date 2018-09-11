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
	char buf[2000];
	char *res;
	list* swordx = listCreate();
	
	/*FILE *f = openFile("D:/Michele/Documents/Università/2° Anno/Secondo Semestre/Sistemi Operativi/Sistemi Operativi Laboratorio/Esercizi/Progetto/test.txt");
	
	while(1) 
	{
		res = fgets(buf, 2000, f);
		if( res==NULL )
		  break;
	  
		storeString(swordx,buf);
	}*/
	const char* s = "D:/Michele/Documents/Università/2° Anno/Secondo Semestre/Sistemi Operativi/Sistemi Operativi Laboratorio/Esercizi/Progetto";
	openFile(s);
	//fclose(f);
	
	//create the file swordnordered.out (it isn't ordered)
	/*		
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
	
	if (remove("swordnordered.out") != 0) printf("Unable to delete the file");*/
	
}

void openFile(const char *path)
{
	DIR* d = opendir(path);
	struct dirent *pent;

	if (!d)
	{
	  printf ("opendir() failure; terminating");
	  exit(1);
	}
	 
	while ((pent=readdir(d)))
	{
		printf("%s\n", pent->d_name);
	}
 
 
 closedir(d);
	/* open the File */
	/*FILE *fd = fopen(path, "r");
	
	if( fd==NULL ) 
	{
		perror("Errore in apertura del file");
		exit(1);
	}
	else
		return fd;*/
}