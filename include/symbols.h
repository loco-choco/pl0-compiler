#ifndef __SYMBOLS_H__
#define __SYMBOLS_H__

#include <string.h>
#define RESERVED_LIST_LENGTH 11

typedef enum {
    _procedure = 0, _const,     _var,       _call,      _begin,
    _end,           _if,        _then,      _while,     _do,
    _odd,           _number,    _diff,      _less_eq,   _less,
    _bigg_eq,       _bigger,    _plus,      _minus,     _mult,
    _div,           _equal,     _end_prog,  _end_exp,   _separator,
    _open_exp,      _close_exp, _ident,     _assign
} symbol_t;

int search_reserved_table(char* token, symbol_t* type); 
#endif
