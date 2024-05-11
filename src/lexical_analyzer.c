#include <lexical_analyzer.h>
#include <stdio.h>
#include <states.h>

/* Check if a state is a terminal state */
int is_terminal(state_t curr_state) {
    state_t terminal_states[12] = {q5, q2, q7, q8, q9, q11, q12, q14, q17, q15, q18, q16};
    int qtde_terminal_states = 12;
    int result = 0;
    
    for(int i = 0; i < qtde_terminal_states; i++) {
       result |= (curr_state == terminal_states[i]);
    }
    
    return result;
}

/* The MIGHTY (or maybe not so) LEXICAL ANALYZER */
token_t lexical_analyzer(FILE *tape) {
    token_t token;
   
    /* Feature to know the line of where which token were in the code.
     * This will help to give more informative messages to the user now
     * and in the future with the syntactic and semantic analyzers*/
    static int number_of_the_line = 1;

    /* Initializes the token that will be built */ 
    memset(token.data, 0, sizeof(token.data));
    token.tape_fd = tape;
    token.type = _unclassified;
    token.error = none;
    token.line_number = -1;

    state_t curr_state = q0; // Initial state 

    /* An array of function pointers (the states) */
    state_t (*states[QTDE_STATES]) (char, token_t*) = {
        &q0_function,   &q1_function,   &q2_function,
        &q3_function,   &q4_function,   &q5_function,
        &q6_function,   &q7_function,   &q8_function,
        &q9_function,   &q10_function,  &q11_function,
        &q12_function,  &q13_function,  &q14_function,
        &q15_function,  &q16_function,  &q17_function,
        &q18_function
    };
    
    /* Initializes the token iterator with 0 */
    token.itr = 0;
    
    char new_symbol = '\0';             // Declares the symbol that will come from the tape 
    int already_assigned_a_line_number = 0;
    while(is_terminal(curr_state) != 1) {
        new_symbol = getc(tape);        // Pops out the symbol from the tape
        
        if(new_symbol == '\n') number_of_the_line++; // Workarround to know the current line number
        
        curr_state = states[curr_state](new_symbol, &token); // Performs the state transition
        
        if(!already_assigned_a_line_number) {
            token.line_number = number_of_the_line;
            already_assigned_a_line_number = 1;
        } 
        
        if((curr_state != q0) && (curr_state != q3)) { // Workarround to ignore comments and
                                                       // invisible characters (states q0 and q3)
            token.data[token.itr++] = new_symbol; // Builds the token
            if(curr_state != q18) // avoids losing where first the comment were opened 
                token.line_number = number_of_the_line; // Ignores comments and invisible
                                                         // characters for normal tokens
        }
    }
    
    states[curr_state](new_symbol, &token); // Performs the function of the final state 
    
    if( new_symbol == '\n' &&   (   (curr_state == q2) || // Workarround to account to backtracks  
                                    (curr_state == q5) || // occured with a '\n' pushed to the tape
                                    (curr_state == q9) ||
                                    (curr_state == q17)
                                )
      ) number_of_the_line--;
            
    return token;
}

/* Dealocates the token chain */
// This function could be in the main.c file, but until further notice it will stay here
void free_token_chain(tk_node_t* token_chain) {
    if(token_chain == NULL) {
        return;
    }

    free_token_chain(token_chain->next);
    free(token_chain);
}
