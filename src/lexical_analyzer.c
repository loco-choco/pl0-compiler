#include <lexical_analyzer.h>
#include <stdio.h>

#define QTDE_STATES 19

typedef struct Token token_t;

struct Token {
    char data[100];
    char class[60];
};

typedef enum {
    q0 = 0,   q1,  q2,
    q3,  q4,  q5,  q6,
    q7,  q8,  q9,  q10,
    q11, q12, q13, q14,
    q15, q16, q17, q18
} state_t;

// Pensar em uma struct unica

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
    
    if( (('a' <= new_symbol) && (new_symbol <= 'z')) ||
        (('A' <= new_symbol) && (new_symbol <= 'Z')) 
    ) {
        next_state = q1;
    } else if(('0' <= new_symbol) && (new_symbol <= '9')) {
        next_state = q4; 
    } else if(  (new_symbol == ' ') ||
                (new_symbol == '\r') ||
                (new_symbol == '\t') ||
                (new_symbol == '\n')
    ) {
        next_state = q0;
    } else if(new_symbol == '<') {
        next_state = q6;
    } else if(new_symbol == '>') {
        next_state = q10;
    } else if(new_symbol == ':') {
        next_state = q13;
    } else if(new_symbol == '{') {
        next_state = q3;
    } else if(  (new_symbol == '(') ||
                (new_symbol == ')') ||
                (new_symbol == '\\') ||
                (new_symbol == '*') || 
                (new_symbol == '-') ||
                (new_symbol == '+') ||
                (new_symbol == '=') ||
                (new_symbol == ';') ||
                (new_symbol == ',') ||
                (new_symbol == '.')
    ) {
        next_state = q15;
    } else {
        next_state = q16;
    }
    
    return next_state;
}

state_t q1_function(char new_symbol) {
    state_t next_state;
    
    if( (('a' <= new_symbol) && (new_symbol <= 'z')) ||
        (('A' <= new_symbol) && (new_symbol <= 'Z')) ||
        (('0' <= new_symbol) && (new_symbol <= '9'))
    ) {
        next_state = q1;
    } else {
        next_state = q2;
    }
    
    return next_state;
}

state_t q3_function(char new_symbol) {
    state_t next_state;
    
    if(new_symbol == EOF) {
        next_state = q18;
    } else if(new_symbol == '}') {
        next_state = q0;
    } else {
        next_state = q3;
    }
    
    return next_state;
}

state_t q4_function(char new_symbol) {
    state_t next_state;
    
    if(('0' <= new_symbol) && (new_symbol <= '9')) {
        next_state = q4;
    } else {
        next_state = q5;
    }
    
    return next_state;
}

state_t q6_function(char new_symbol) {
    state_t next_state;
    
    if(new_symbol == '>') {
        next_state = q7;
    } else if(new_symbol == '=') {
        next_state = q8;
    } else {
        next_state = q9;
    }
    
    return next_state;
}

state_t q10_function(char new_symbol) {
    state_t next_state;
    
    if(new_symbol == '=') {
        next_state = q11;
    } else {
        next_state = q12;
    }
    
    return next_state;
}

state_t q13_function(char new_symbol) {
    state_t next_state;
    
    if(new_symbol == '=') {
        next_state = q14;
    } else {
        next_state = q17;
    }
    
    return next_state;
}

token_t lexical_analyzer(int* index_ptr, FILE *tape) {
    int index = *index_ptr;
    token_t token;
    state_t curr_state = q0; // Initial state 

    // create the array of function pointers
    state_t (*states[QTDE_STATES]) (char) = {
        &q0_function,
        &q1_function,
        NULL,
        &q3_function,
        &q4_function,
        NULL,
        &q6_function,
        NULL,
        NULL,
        NULL,
        &q10_function,
        NULL,
        NULL,
        &q13_function,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    };
    int itr = 0;
    while(is_terminal(curr_state) != 1) {
        char new_symbol = getc(tape);
        state_t next_state = states[curr_state](new_symbol); 
        curr_state = next_state;

        token.data[itr++] = new_symbol;
    }
    token.data[itr] = '\0';
    
    *index_ptr = index; // Return index
    return token;
}
