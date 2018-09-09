#include <stdio.h>
#include <stdlib.h>
#include "list.h"


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
		printf("ritorna nel while");
        printf("\n %s", buf);
        //IL PROBLEMA E' QUI
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


