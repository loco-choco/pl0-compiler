#include <symbols.h>

/* In fact the reserved symbol table of the language.
 * Corresponds to the first 27 symbols of the symbol table 
 * (the ones which are explictly numbered) to allow direct map 
 * between the symbol and its type (or class) symbol_t */
char reserved_table[RESERVED_LIST_LENGTH][12] = {
    "PROCEDURE",
    "CONST",
    "VAR",
    "CALL",
    "BEGIN",
    "END",
    "IF",
    "THEN",
    "WHILE",
    "DO",
    "ODD",
    "+",
    "-",
    "*",
    "/",
    "<>",
    "<",
    ">",
    "<=",
    ">=",
    "=",
    ":=",
    ".",
    ";",
    ",",
    "(",
    ")"
};

/* The table containing the readable name of the symbols defined
 * including symbols like _unclassified and _defective, created to improve 
 * code robustness to errors (bug tollerance).
 *
 * The names are in order with the symbol's enum declaration
 * (to allow a direct map from the symbol_t code).*/
char symbol_name_table[SYMBOL_LIST_LENGTH][22] = {
    "PROCEDURE",
    "CONST",
    "VAR",
    "CALL",
    "BEGIN",
    "END",
    "IF",
    "THEN",
    "WHILE",
    "DO",
    "ODD",
    "Plus",
    "Minus",
    "Multiplication",
    "Division",
    "Different",
    "Less than",
    "Greater than",
    "Less than or equal",
    "Greater than or equal",
    "Equal",
    "Assign",
    "Dot",
    "Semicolon",
    "Comma",
    "Open parenthesis",
    "Close parenthesis",
    "Identifier",
    "Number",
    "Unclassified",
    "Defective"
};

int search_reserved_table(char* token, symbol_t* type) {
    for(int i = 0; i < RESERVED_LIST_LENGTH; i++) {
        if(strcmp(token, reserved_table[i]) == 0) {
            (*type) = (symbol_t) i;
            return 1;
        }
    }
    return 0;
}

void get_symbol_description(symbol_t symbol, char* symbol_text) {
    strcpy(symbol_text, symbol_name_table[(int) symbol]);
}
