#ifndef __SYMBOLS_H__
#define __SYMBOLS_H__

#include <string.h>
#define RESERVED_LIST_LENGTH 27
#define SYMBOL_LIST_LENGTH 32
typedef enum {
    _procedure=0,   _const=1,       _var=2,         _call=3,        _begin=4,
    _end=5,         _if=6,          _then=7,        _while=8,       _do=9,
    _odd=10,        _plus=11,       _minus=12,      _mult=13,       _div=14,
    _diff=15,       _less=16,       _bigger=17,     _less_eq=18,    _bigg_eq=19,
    _equal=20,      _assign=21,     _end_prog=22,   _end_exp=23,    _separator=24,
    _open_exp=25,   _close_exp=26,  _ident,         _number,        _unclassified,
    _defective,     _end_of_file    
} symbol_t;

int search_reserved_table(char* token, symbol_t* type); 

void get_symbol_description(symbol_t symbol, char* symbol_text);
#endif
