#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <lexical_analyzer.h>

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
   
    /* FROM HERE WE WILL ACTUALLY STARTS THE LEXICAL ANALYSIS */
    
    /* Creates a linked-list (a chain) for the Tokens that 
     * are going to be parsed and classified */
    tk_node_t* token_chain_head = malloc(sizeof(tk_node_t));
    token_chain_head->next = NULL;
    tk_node_t* token_chain = token_chain_head; 
    
    /* Defines the auxiliary variables to the sucessive calls of lexical analyzer */ 
    char lookahead; // A "lookahead"ahead character to detect the END OF THE FILE (EOF)
    tk_node_t* token_previous = NULL; // A previous token to detect the "dot" that indicates
                                      // The end of the program
    
    /* Successively calls the lexical analyzer until the EOF, or the end-of-program token */ 
    while ( (lookahead = getc(fd_source_code)) != EOF && 
            (   (token_previous == NULL) ||         // Uses the power of the short-circuit in C
                (token_previous->type != _end_prog) // to avoid misreading a NULL pointer.
            )
    ) {
        ungetc(lookahead, fd_source_code); // A simple "backtrack()"
        

        /* HERE (FINALLY) THE CALL OF THE LONG AWAITED LEXICAL ANALYZER!! */
        token_t tk = lexical_analyzer(fd_source_code);
        /* more space to emphasize the call */
    

        /* Converts the log provided by the lexical 
         * analyzer into a token-chain element */
        strcpy(token_chain->data, tk.data);
        token_chain->error = tk.error;
        token_chain->type = tk.type;
        token_chain->line_number = tk.line_number;
        
        /* Allocates space to the next token and initialize it */
        token_chain->next = malloc(sizeof(tk_node_t));  
        token_chain->next->next = NULL;
        token_chain->next->data[0] = '\0';
        
        /* Updates the previous token */ 
        token_previous = token_chain;
        
        /* Iterates to the next token */
        token_chain = token_chain->next;
    }
    /* At the end frees the last unused chain element
     * allocated at the end of the for-loop */
    if(token_previous != NULL) { // If the code ever entered the loop
        free(token_chain);
        token_previous->next = NULL;
    }

    token_chain = token_chain_head; // Points again to the head of the chain
    
    /* Reads the token chain and prints it to the log file */
    while(token_chain != NULL) {
        char error_type[30];
        char symbol_type[30];
        char error_detailed_description[1024];
 
        get_symbol_description(token_chain->type, symbol_type); // Returns the symbol type name
        
        /* Prints the respective token and its class
         * (which was called 'type' within the context of this code). */
        fprintf(fd_log, "Token:( %s ),\tClass:( %s ),\t", token_chain->data, symbol_type);
        
        /* If the token has errors (defective), display the error found.*/
        if(token_chain->error != none) {
           get_error_description(token_chain->error, error_type); // Returns the error type basic description
           /* Prints the error basic message (basically the error type) */ 
           fprintf(fd_log, "Error: ( %s )", error_type); 
            if(set_verbose_errors) {
                fprintf(fd_log, " found at line %d", token_chain->line_number);
                get_error_verbose(token_chain->error, error_detailed_description); // Returns the error detailed message
                fprintf(fd_log, "\nDetailed description: %s", error_detailed_description);
            } 
        } 
        fprintf(fd_log, "\n");
         
        token_chain = token_chain->next; // Iterates to the next token
    }
    
    /* Frees memory allocated to the token chain */
    free_token_chain(token_chain_head); 
    
    /* Closes the open file descriptors */
    fclose(fd_source_code);
    fclose(fd_log);
    
    return 0;
}
