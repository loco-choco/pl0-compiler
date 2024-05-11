#ifndef __LEXICAL_ANALYZER_H__
#define __LEXICAL_ANALYZER_H__
#include <error_handler.h>
#include <symbols.h>
#include <stdio.h>
#include <stdlib.h>

#define QTDE_STATES 19
#define MAX_TOKEN_LENGTH 100

/* The states of the lexical analyzer FSA (Finate State Automaton)*/
// This should be at state.h, but due to problems with circular inclusion it ended up here.
typedef enum {
    q0 = 0,   q1,  q2,
    q3,  q4,  q5,  q6,
    q7,  q8,  q9,  q10,
    q11, q12, q13, q14,
    q15, q16, q17, q18
} state_t;

typedef struct Token token_t;

struct Token { // This is "more than just a token"
               // It is the structure used by the lexical to construct the token.
    char data[1024]; // Warn! this is 1024 because, despite the maximum token
                     // is limited to 100 of length. To avoid security problems 
                     // (and segmentation faults) due to "troublemater" tokens
                     // the size of the token is much higher than the limit.
    symbol_t type;
    error_t error;
    int line_number;
    FILE* tape_fd;
    int itr;
};

typedef struct TokenNode tk_node_t;

struct TokenNode { // This is "more like just the token itself", but with some "extras"
                   // to allow a formation of a linked-list.
    char data[1024]; // Warn! this is 1024 because, despite the maximum token
                     // is limited to 100 of length. To avoid security problems 
                     // (and segmentation faults) due to "troublemater" tokens
                     // the size of the token is much higher than the limit.
    symbol_t type;
    error_t error;
    int line_number;
    tk_node_t* next;
};

// TODO or not TODO (is it really a question?): create properly a Token "itself".

int is_terminal(state_t curr_state);
token_t lexical_analyzer(FILE *tape);

/* I can still hear you sayin' You would never break the chain...
 * But yeah, this breaks the chain (the token chain created at the main.c)!
 * See comment at the src/logic_analyzer.c */
void free_token_chain(tk_node_t* token_chain);
#endif
