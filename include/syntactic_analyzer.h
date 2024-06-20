#ifndef __SYNTACTIC_ANALYZER_H__
#define __SYNTACTIC_ANALYZER_H__
#include <lexical_analyzer.h>
#include <error_handler.h>
#include <stdio.h>
#include <stdlib.h>

//typedef struct token_t token_t;
//typedef struct token_tNode tk_node_t;
//token_t lexical_analyzer(FILE *tape);
void syntactic_analyser(FILE *file, FILE *error_output);

void syntactic_panic_handler(FILE *file, token_t* current_symbol, char* error, symbol_t* sync_symbols, int sync_symbols_num, FILE *error_output);

//Procedures of the syntactic grammar
void program(FILE* file, token_t* current_symbol, symbol_t* sync_symbols, int sync_symbols_num, FILE *error_output);
void block(FILE* file, token_t* current_symbol, symbol_t* sync_symbols, int sync_symbols_num, FILE *error_output);
void declaration(FILE* file, token_t* current_symbol, symbol_t* sync_symbols, int sync_symbols_num, FILE *error_output);
void constant(FILE* file, token_t* current_symbol, symbol_t* sync_symbols, int sync_symbols_num, FILE *error_output);
void variable(FILE* file, token_t* current_symbol, symbol_t* sync_symbols, int sync_symbols_num, FILE *error_output);
void procedure(FILE* file, token_t* current_symbol, symbol_t* sync_symbols, int sync_symbols_num, FILE *error_output);
void command(FILE* file, token_t* current_symbol, symbol_t* sync_symbols, int sync_symbols_num, FILE *error_output);
void expression(FILE* file, token_t* current_symbol, symbol_t* sync_symbols, int sync_symbols_num, FILE *error_output);
void unary_operator(FILE* file, token_t* current_symbol, symbol_t* sync_symbols, int sync_symbols_num, FILE *error_output);
void term(FILE* file, token_t* current_symbol, symbol_t* sync_symbols, int sync_symbols_num, FILE *error_output);
void factor(FILE* file, token_t* current_symbol, symbol_t* sync_symbols, int sync_symbols_num, FILE *error_output);
void condition(FILE* file, token_t* current_symbol, symbol_t* sync_symbols, int sync_symbols_num, FILE *error_output);
void relational(FILE* file, token_t* current_symbol, symbol_t* sync_symbols, int sync_symbols_num, FILE *error_output);

#endif
