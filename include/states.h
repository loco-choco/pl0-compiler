#pragma once
#include<lexical_analyzer.h>

typedef enum {
    q0 = 0,   q1,  q2,
    q3,  q4,  q5,  q6,
    q7,  q8,  q9,  q10,
    q11, q12, q13, q14,
    q15, q16, q17, q18
} state_t;

state_t q0_function(char new_symbol, token_t token);
state_t q1_function(char new_symbol, token_t token);
state_t q2_function(char new_symbol, token_t token);
state_t q3_function(char new_symbol, token_t token);
state_t q4_function(char new_symbol, token_t token);
state_t q5_function(char new_symbol, token_t token);
state_t q6_function(char new_symbol, token_t token);
state_t q7_function(char new_symbol, token_t token);
state_t q8_function(char new_symbol, token_t token);
state_t q9_function(char new_symbol, token_t token);
state_t q10_function(char new_symbol, token_t token);
state_t q11_function(char new_symbol, token_t token);
state_t q12_function(char new_symbol, token_t token);
state_t q13_function(char new_symbol, token_t token);
state_t q14_function(char new_symbol, token_t token);
state_t q15_function(char new_symbol, token_t token);
state_t q16_function(char new_symbol, token_t token);
state_t q17_function(char new_symbol, token_t token);
state_t q18_function(char new_symbol, token_t token);
