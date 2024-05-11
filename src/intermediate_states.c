#include <states.h>

state_t q0_function(char new_symbol, token_t* token) {
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
                (new_symbol == '/') ||
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

state_t q1_function(char new_symbol, token_t* token) {
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

state_t q3_function(char new_symbol, token_t* token) {
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

state_t q4_function(char new_symbol, token_t* token) {
    state_t next_state;
    
    if(('0' <= new_symbol) && (new_symbol <= '9')) {
        next_state = q4;
    } else {
        next_state = q5;
    }
    
    return next_state;
}

state_t q6_function(char new_symbol, token_t* token) {
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

state_t q10_function(char new_symbol, token_t* token) {
    state_t next_state;
    
    if(new_symbol == '=') {
        next_state = q11;
    } else {
        next_state = q12;
    }
    
    return next_state;
}

state_t q13_function(char new_symbol, token_t* token) {
    state_t next_state;
    
    if(new_symbol == '=') {
        next_state = q14;
    } else {
        next_state = q17;
    }
    
    return next_state;
}
