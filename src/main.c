#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <syntactic_analyzer.h>

#define VERSION 0.0
#define EXPECTED_ARGUMENTS 2
/* The two arguments are <source_file_name> <log_file_name> */

int main(int argc, char* argv[]) {
    /* Strings to store the file names */
    char pl0_source_file_name[60];
    char pl0_log_file_name[60];
    
    /* Variables used during the validation process of the flags and parameters passed */
    int number_argument = 0;
    int incorrect_usage_of_args = 0;
    int set_verbose_errors = 0;
    
    /* Validation and parsing of program inputs (parameters) and flags */ 
    for(int i = 1; i < argc; i++) {
        if(argv[i][0] == '-') {                                         // this is a flag
	        if(strcmp(argv[i],"-h") == 0) incorrect_usage_of_args = 1;  // force help text
            else if(strcmp(argv[i],"-v") == 0) set_verbose_errors = 1;  // set verbose errors
	        else if(strcmp(argv[i],"--version") == 0) {
                printf("Version: %.1f\n", VERSION);
                return 0;
            }
            else printf("There is no option for flag %s\n",argv[i]);
	    }
	    else {                                              // this is an arg
            if(number_argument == 0) {                      //first number argument
	    	   memcpy(pl0_source_file_name, argv[i], 60);
            } else if(number_argument == 1) {               //second number argument
	    	   memcpy(pl0_log_file_name, argv[i], 60);
            } else {
                incorrect_usage_of_args = 1;
	    	    printf("Too many arguments!\n");
	        }
	        number_argument++;
	    }
    }
    if(number_argument < EXPECTED_ARGUMENTS) {
        printf("Arguments missing!\n");
	incorrect_usage_of_args = 1;
    }
    
    /* Displays help message if needed */
    if(incorrect_usage_of_args == 1) {
        printf("Usage:\n");
        printf("$ ./pl0-compiler <source_file_name> <log_file_name>\n");
        printf("\tsource_file_name - source's code file name\n"); 
        printf("\tlog_file_name - log's file name\n"); 
        printf("Flags:\n");
        printf("\t-h - displays help message\n");
        printf("\t-v - displays verbose errors\n");
        printf("\t--version - displays version\n");
        exit(-1);
    }
    /* END of Validation process */
    
    /* Actual init of the code */
    
    /* Process of opening the file descriptors for Source Code and Log files  */
    FILE* fd_source_code = fopen(pl0_source_file_name,"r");
    if(fd_source_code == NULL) {
      printf("Error while opening file: %s\n", pl0_source_file_name);
      exit(1);
    }
    
    FILE* fd_log = fopen(pl0_log_file_name,"w+");
    if(fd_log == NULL) {
      printf("Error while opening file: %s\n", pl0_log_file_name);
      exit(1);
    }
    /* END of the process */
    
    syntactic_analyser(fd_source_code, fd_log);
        
    /* Closes the open file descriptors */
    fclose(fd_source_code);
    fclose(fd_log);
    
    return 0;
}
