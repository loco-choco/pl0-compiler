#include <lexical_analyzer.h>
#include <states.h>
#include <stdio.h>

int is_terminal(state_t curr_state) {
    state_t terminal_states[12] = {q5, q2, q7, q8, q9, q11, q12, q14, q17, q15, q18, q16};
    int qtde_terminal_states = 12;
    int result = 0;
    
    for(int i = 0; i < qtde_terminal_states; i++) {
       result |= (curr_state == terminal_states[i]);
    }
    
    return result;
}

token_t lexical_analyzer(int* index_ptr, FILE *tape) {
    int index = *index_ptr;
    token_t token;
    state_t curr_state = q0; // Initial state 

    // create the array of function pointers
    state_t (*states[QTDE_STATES]) (char, token_t) = {
        &q0_function,
        &q1_function,
        &q2_function,
        &q3_function,
        &q4_function,
        &q5_function,
        &q6_function,
        &q7_function,
        &q8_function,
        &q9_function,
        &q10_function,
        &q11_function,
        &q12_function,
        &q13_function,
        &q14_function,
        &q15_function,
        &q16_function,
        &q17_function,
        &q18_function
    };
    int itr = 0;
    char new_symbol = '\0';
    while(is_terminal(curr_state) != 1) {
        new_symbol = getc(tape);
        curr_state = states[curr_state](new_symbol, token); 
        token.data[itr++] = new_symbol;
    }

    token.data[itr] = '\0';
    
    states[curr_state](new_symbol, token); // Performs the function of the final state
    
    *index_ptr = index; // Return index
    return token;
}
