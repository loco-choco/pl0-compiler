#include <states.h>
#include <stdio.h>
#include <string.h>

state_t q2_function(char new_symbol, token_t* token) {
    if(search_reserved_table(token->data, &token->type)){
    } else {
        if(strlen(token->data) <= MAX_TOKEN_LENGTH) {
            token->type = _ident;
        } else {
            token->error = identifier_too_long;
        }
    }
    ungetc(new_symbol, token->tape_fd);
    token->itr--;
    return q2;
}

state_t q5_function(char new_symbol, token_t* token) {
    if(strlen(token->data) <= MAX_TOKEN_LENGTH) {
    } else {
        token->error = number_too_long;
    }
    ungetc(new_symbol, token->tape_fd);
    token->itr--;
    return q5;
}

state_t q7_function(char new_symbol, token_t* token) {
    token->type = _diff;
    return q7;
}

state_t q8_function(char new_symbol, token_t* token) {
    token->type = _less_eq;
    return q8;
}

state_t q9_function(char new_symbol, token_t* token) {
    token->type = _less;
    ungetc(new_symbol, token->tape_fd);
    token->itr--;
    return q9;
}

state_t q11_function(char new_symbol, token_t* token) {
    token->type = _bigg_eq;
    return q11;
}

state_t q12_function(char new_symbol, token_t* token) {
    token->type = _bigger;
    return q12;
}

state_t q14_function(char new_symbol, token_t* token) {
    token->type = _assign;
    return q14;
}

state_t q15_function(char new_symbol, token_t* token) {
    search_reserved_table(token->data, &token->type);
    return q15;
}

state_t q16_function(char new_symbol, token_t* token) {
    token->error = invalid_char;
    return q16;
}

state_t q17_function(char new_symbol, token_t* token) {
    token->error = malformed_assign_operator;
    ungetc(new_symbol, token->tape_fd);
    token->itr--;
    return q17;
}

state_t q18_function(char new_symbol, token_t* token) {
    token->error = unexpected_end_of_file;
    return q18;
}
