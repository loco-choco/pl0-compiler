#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <lexical_analyzer.h>

#define VERSION 0.0
#define EXPECTED_ARGUMENTS 1

int main(int argc, char* argv[]) {
    char pl0_file_name[60];
    int number_argument = 0;
    int incorrect_usage_of_args = 0;
    
    for(int i = 1; i < argc; i++) {
        if(argv[i][0] == '-') { // this is a flag
	        if(strcmp(argv[i],"-h") == 0) incorrect_usage_of_args = 1; //force help text
	        else if(strcmp(argv[i],"-v") == 0) {
                printf("Version: %.1f\n", VERSION);
                return 0;
            }
            else printf("There is no option for flag %s\n",argv[i]);
	    }
	    else { // this is an arg
	        //char* end;
            if(number_argument == 0) { //first number argument
	    	   memcpy(pl0_file_name, argv[i], 60);
                //if(*end != '\0' || order < 2) {
	    	    //    incorrect_usage_of_args = 1;
	    	    //    printf("Order is not a number bigger then 2!\n");
	    	    //}
	        
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
    
    if(incorrect_usage_of_args == 1) {
        printf("Usage:\n");
        printf("$ ./pl0-compiler <file_name>\n");
        printf("\tfile_name - source's code file name\n"); 
        printf("Flags:\n");
        printf("\t-h - displays help message\n");
        printf("\t-v - displays version\n");
        exit(-1);
    }
  
    printf("Hello from pl0-compiler!\n");
    printf("File name: %s\n", pl0_file_name);

    FILE* fd_source_code = fopen(pl0_file_name,"r");
    if(fd_source_code == NULL) {
      printf("Error while opening file: %s\n", pl0_file_name);
      exit(1);
    }

    //char buffer[1024];

    // Reading lines until the end of the file
    //while (fgets(buffer, sizeof(buffer), fd_source_code) != NULL) {
    //    printf("%s", buffer);
    //}
   
    token_t tk = lexical_analyzer(fd_source_code);
    printf("Token: %s\n", tk.data);
    
    tk = lexical_analyzer(fd_source_code);
    printf("Token: %s\n", tk.data);
    
    tk = lexical_analyzer(fd_source_code);
    printf("Token: %s\n", tk.data);

    tk = lexical_analyzer(fd_source_code);
    printf("Token: %s\n", tk.data);
    
    tk = lexical_analyzer(fd_source_code);
    printf("Token: %s\n", tk.data);
    
    tk = lexical_analyzer(fd_source_code);
    printf("Token: %s\n", tk.data);
    
    tk = lexical_analyzer(fd_source_code);
    printf("Token: %s\n", tk.data);

    tk = lexical_analyzer(fd_source_code);
    printf("Token: %s\n", tk.data);
    
    tk = lexical_analyzer(fd_source_code);
    printf("Token: %s\n", tk.data);

    tk = lexical_analyzer(fd_source_code);
    printf("Token: %s\n", tk.data);
    
    tk = lexical_analyzer(fd_source_code);
    printf("Token: %s\n", tk.data);
    
    tk = lexical_analyzer(fd_source_code);
    printf("Token: %s\n", tk.data);

    tk = lexical_analyzer(fd_source_code);
    printf("Token: %s\n", tk.data);
    
    tk = lexical_analyzer(fd_source_code);
    printf("Token: %s\n", tk.data);
    
    tk = lexical_analyzer(fd_source_code);
    printf("Token: %s\n", tk.data);

    tk = lexical_analyzer(fd_source_code);
    printf("Token: %s\n", tk.data);
    
    tk = lexical_analyzer(fd_source_code);
    printf("Token: %s\n", tk.data);

    tk = lexical_analyzer(fd_source_code);
    printf("Token: %s\n", tk.data);
    
    tk = lexical_analyzer(fd_source_code);
    printf("Token: %s\n", tk.data);
    
    tk = lexical_analyzer(fd_source_code);
    printf("Token: %s\n", tk.data);

    tk = lexical_analyzer(fd_source_code);
    printf("Token: %s\n", tk.data);
    
    tk = lexical_analyzer(fd_source_code);
    printf("Token: %s\n", tk.data);
    
    fclose(fd_source_code);
    return 0;
}
