#include <states.h>
#include <string.h>

/* Internally implements the backtrack operation (increase modularity) for the final states */
void backtrack(token_t* token, char lookahead) {
    token->data[--token->itr] = '\0';
    ungetc(lookahead, token->tape_fd);
}

state_t q2_function(char new_symbol, token_t* token) {
    backtrack(token, new_symbol);   // First perform the backtrack to allow the correct regonition
                                    // of the token in the reserved symbol table.
    if(search_reserved_table(token->data, &token->type)){
    } else {
        if(strlen(token->data) <= MAX_TOKEN_LENGTH) {
            token->type = _ident;
        } else {
            token->error = identifier_too_long;
            token->type = _defective;
        }
    }
    return q2;
}

state_t q5_function(char new_symbol, token_t* token) {
    backtrack(token, new_symbol);
    if(strlen(token->data) <= MAX_TOKEN_LENGTH) {
        token->type = _number;
    } else {
        token->error = number_too_long;
        token->type = _defective;
    }

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
    backtrack(token, new_symbol);
    token->type = _less;
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
    token->type = _defective;
    return q16;
}

state_t q17_function(char new_symbol, token_t* token) {
    backtrack(token, new_symbol);
    token->error = malformed_assign_operator;
    token->type = _defective;
    return q17;
}

state_t q18_function(char new_symbol, token_t* token) {
    token->error = unexpected_end_of_file;
    token->type = _defective;
    return q18;
}

state_t q19_function(char new_symbol, token_t* token) {
    token->error = multiline_comment_not_supported;
    token->type = _defective;
    return q19;
}
