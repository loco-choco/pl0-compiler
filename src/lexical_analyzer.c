#include <lexical_analyzer.h>

typedef struct Token token_t;

struct Token {
    char token[100];
    char class[60];
};

typedef enum {
    q0 = 0,   q1,  q2,
    q3,  q4,  q5,  q6,
    q7,  q8,  q9,  q10,
    q11, q12, q13, q14,
    q15, q16, q17, q18,
    invalid
} state_t;

int is_terminal(state_t curr_state) {
    state_t terminal_states[12] = {q5, q2, q7, q8, q9, q11, q12, q14, q17, q15, q18, q16};
    int qtde_terminal_states = 12;
    int result = 0;
    
    for(int i = 0; i < qtde_terminal_states; i++) {
       result |= (curr_state == terminal_states[i]);
    }
    
    return result;
}

state_t q0_function(char new_symbol) {
    state_t next_state;
    return next_state;
}

token_t lexical_analyzer(int* index_ptr, char *tape) {
    int index = *index_ptr;
    token_t token;
    state_t curr_state = q0; // Initial state 
    
    while(is_terminal(curr_state) != 1) {
        
    }

    *index_ptr = index; // Return index
    return token;
}
