#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "utils.h"
#include "global.h"

/* flags */

int recursive_flag;
int follow_flag;
int alpha_flag;

static int sort_flag;

char *fileToExclude;
int numMin;
char *fileToIgnore;
char *logFile;

char *outputFile = "sword.out";

void sort();

/*
 * argc num parametri
 * argv array di puntatori ai parametri (parti da argv[1])
 * 
 * */
int main (int argc, char *argv[]) {
	list *sword = createList();
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
          {"exclude",  required_argument, 0, 'e'},
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
				numMin = *optarg;
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
		printf ("%s ", files[z]);   
		putchar ('\n');
		z++;
		}
	for (int j= 0; j < z; j++){
		checkName(sword, files[j]);
		}
	free(files);
	writeOnFile(sword, outputFile);
//	sort(); 
    } 
  else("There aren't input files");
  exit (0);
}

void sort(){
	/*se quindi il sort è in normale ordine alfabetico*/
	char command[80];
	printf("arriva qui");
	strcpy(command, "/bin/sh -c sort -o ");
	char inout[61];
	if (sort_flag == 0){
		/*sort file on bash -> sort -o input output*/
		strcpy(inout, outputFile);
		strcat(inout, " ");
		strcat(inout, outputFile);
		strcat(command, inout);
		system(command);
	}
	/*se quindi il sort è in base al numero di occorrenza*/
	else {}
}
				
		
	
	
	
	
	

