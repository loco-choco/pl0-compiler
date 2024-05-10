#pragma once
#include <error_handler.h>
#include <symbols.h>

#define QTDE_STATES 19
#define MAX_TOKEN_LENGTH 100

typedef struct Token token_t;

struct Token {
    char data[1024];
    symbol_t type;
    error_t error;
};
