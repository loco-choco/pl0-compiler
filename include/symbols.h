#pragma once

#include<string.h>
#define RESERVED_LIST_LENGTH 11

typedef enum {
    _procedure = 0, _const,     _var,       _call,      _begin,
    _end,           _if,        _then,      _while,     _do,
    _odd,           _number,    _diff,      _less_eq,   _less,
    _bigg_eq,       _bigger,    _plus,      _minus,     _mult,
    _div,           _equal,     _end_prog,  _end_exp,   _separator,
    _open_exp,      _close_exp, _ident,     _assign
} symbol_t;

char reserved_table[RESERVED_LIST_LENGTH][12] = {
    "PROCEDURE\0",
    "CONST\0",
    "VAR\0",
    "CALL\0",
    "BEGIN\0",
    "END\0",
    "IF\0",
    "THEN\0",
    "WHILE\0",
    "DO\0",
    "ODD\0"
};

int search_reserved_table(char* token, symbol_t* type) {
    for(int i = 0; i < RESERVED_LIST_LENGTH; i++) {
        if(strcmp(token, reserved_table[i]) == 1) {
            (*type) = (symbol_t) i;
            return 1;
        }
    }
    return 0;
}
