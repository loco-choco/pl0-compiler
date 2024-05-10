#ifndef __LEXICAL_ANALYZER_H__
#define __LEXICAL_ANALYZER_H__
#include <error_handler.h>
#include <symbols.h>
#include <stdio.h>

#define QTDE_STATES 19
#define MAX_TOKEN_LENGTH 100

typedef enum {
    q0 = 0,   q1,  q2,
    q3,  q4,  q5,  q6,
    q7,  q8,  q9,  q10,
    q11, q12, q13, q14,
    q15, q16, q17, q18
} state_t;

typedef struct Token token_t;

struct Token {
    char data[1024];
    symbol_t type;
    error_t error;
    FILE* tape_fd;
    int itr;
};

int is_terminal(state_t curr_state);
token_t lexical_analyzer(FILE *tape);

#endif
