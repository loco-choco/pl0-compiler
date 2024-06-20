#include <syntactic_analyzer.h>
#include <lexical_analyzer.h>
#include <symbols.h>
#include <error_handler.h>
#include <stdio.h>
#include <stdlib.h>

void syntactic_analyser(FILE *file, FILE *error_output){
  token_t current_symbol = lexical_analyzer(file);
  symbol_t* syncs_symbs = malloc(sizeof(symbol_t) * 1);
  syncs_symbs[0] = _end_of_file; //So it can always recover if it find an EOF, exiting all the call tree
  program(file, &current_symbol, syncs_symbs, 1, error_output);
  free(syncs_symbs);
}

void syntactic_panic_handler(FILE *file, token_t* current_symbol, char* error, symbol_t* sync_symbols, int sync_symbols_num, FILE *error_output){
  fprintf(error_output, "Syntactic Error: '%s' at line %d\n", error, current_symbol->line_number);

  if(current_symbol->type == _unclassified){ //Lexical Error!
    char error_type[30];
    get_error_description(current_symbol->error, error_type);
    fprintf(error_output, "\tLexical Error: '%s' at line %d\n", error_type, current_symbol->line_number);
  }
  //Panic recovery
  int found_sync_symbol = 0;
  while(!found_sync_symbol){
    for(int i = 0; i < sync_symbols_num; i++){
      if(current_symbol->type == sync_symbols[i]){
        found_sync_symbol = 1;
        continue;
      }
    }
    if(!found_sync_symbol){
      *current_symbol = lexical_analyzer(file);
    }
  }
}

//Procedures of the syntactic grammar
void program(FILE* file, token_t* current_symbol, symbol_t* sync_symbols, int sync_symbols_num, FILE *error_output){
  //Sync symbols for block
  symbol_t* syncs_block = malloc(sizeof(symbol_t) * (sync_symbols_num + 1));
  memcpy(syncs_block, sync_symbols, sync_symbols_num);
  syncs_block[sync_symbols_num] = _end_prog;
   
  block(file, current_symbol, syncs_block, sync_symbols_num + 1, error_output);
  if(current_symbol->type == _end_prog){
    *current_symbol = lexical_analyzer(file);
  } else {
    syntactic_panic_handler(file, current_symbol, "No End Program", sync_symbols, sync_symbols_num, error_output);
  }
  free(syncs_block);
  return;
}
void block(FILE* file, token_t* current_symbol, symbol_t* sync_symbols, int sync_symbols_num, FILE *error_output){
  //TODO ADD SYNC SYMBS
  declaration(file, current_symbol, sync_symbols, sync_symbols_num, error_output);
  command(file, current_symbol, sync_symbols, sync_symbols_num, error_output);
}
void declaration(FILE* file, token_t* current_symbol, symbol_t* sync_symbols, int sync_symbols_num, FILE *error_output){
  //TODO ADD SYNC SYMBS
  constant(file, current_symbol, sync_symbols, sync_symbols_num, error_output);
  variable(file, current_symbol, sync_symbols, sync_symbols_num, error_output);
  procedure(file, current_symbol, sync_symbols, sync_symbols_num, error_output);
}
void constant(FILE* file, token_t* current_symbol, symbol_t* sync_symbols, int sync_symbols_num, FILE *error_output){
  //TODO ADD SYNC SYMBS
  if(current_symbol->type != _const){
    return;
  }
  *current_symbol = lexical_analyzer(file);

  int more_const = 0;
  do {
    if(current_symbol->type == _ident){
      *current_symbol = lexical_analyzer(file);
    } else {
      syntactic_panic_handler(file, current_symbol, "No IDENT in constant definition", sync_symbols, sync_symbols_num, error_output);
      return;
    }

    if(current_symbol->type == _equal){
      *current_symbol = lexical_analyzer(file);
    } else {
      syntactic_panic_handler(file, current_symbol, "No '=' in constant definition", sync_symbols, sync_symbols_num, error_output);
      return;
    }

    if(current_symbol->type == _number){
      *current_symbol = lexical_analyzer(file);
    } else {
      syntactic_panic_handler(file, current_symbol, "No NUMBER in constant definition", sync_symbols, sync_symbols_num, error_output);
      return;
    }
    if(current_symbol->type == _separator){
      more_const = 1;
      *current_symbol = lexical_analyzer(file);
    } else {
      more_const = 0;
    }
  } while(more_const);

  if(current_symbol->type == _end_exp){
    *current_symbol = lexical_analyzer(file);
  } else {
    syntactic_panic_handler(file, current_symbol, "Constant definition wasnt closed with ';'", sync_symbols, sync_symbols_num, error_output);
  }
}
void variable(FILE* file, token_t* current_symbol, symbol_t* sync_symbols, int sync_symbols_num, FILE *error_output){
  //TODO ADD SYNC SYMBS
  if(current_symbol->type != _var){
    return;
  }
  *current_symbol = lexical_analyzer(file);

  int more_var = 0;
  do {
    if(current_symbol->type == _ident){
      *current_symbol = lexical_analyzer(file);
    } else {
      syntactic_panic_handler(file, current_symbol, "No IDENT in variable definition", sync_symbols, sync_symbols_num, error_output);
      return;
    }
    
    if(current_symbol->type == _separator){
      more_var = 1;
      *current_symbol = lexical_analyzer(file);
    } else {
      more_var = 0;
    }
  } while(more_var);

  if(current_symbol->type == _end_exp){
    *current_symbol = lexical_analyzer(file);
  } else {
    syntactic_panic_handler(file, current_symbol, "Variable definition wasnt closed with ';'", sync_symbols, sync_symbols_num, error_output);
  }
}
void procedure(FILE* file, token_t* current_symbol, symbol_t* sync_symbols, int sync_symbols_num, FILE *error_output){
  //TODO ADD SYNC SYMBS
  if(current_symbol->type != _procedure){
    return;
  }
  *current_symbol = lexical_analyzer(file);

  if(current_symbol->type == _ident){
    *current_symbol = lexical_analyzer(file);
  } else {
    syntactic_panic_handler(file, current_symbol, "No IDENT in procedure definition", sync_symbols, sync_symbols_num, error_output);
    return;
  }

  if(current_symbol->type == _end_exp){
    *current_symbol = lexical_analyzer(file);
  } else {
    syntactic_panic_handler(file, current_symbol, "No ';' closing procedure definition", sync_symbols, sync_symbols_num, error_output);
    return;
  }
  
  block(file, current_symbol, sync_symbols, sync_symbols_num + 1, error_output);

  if(current_symbol->type == _end_exp){
    *current_symbol = lexical_analyzer(file);
  } else {
    syntactic_panic_handler(file, current_symbol, "No ';' closing procedure block", sync_symbols, sync_symbols_num, error_output);
    return;
  }

  procedure(file, current_symbol, sync_symbols, sync_symbols_num, error_output);
}
void command(FILE* file, token_t* current_symbol, symbol_t* sync_symbols, int sync_symbols_num, FILE *error_output){
  //TODO ADD SYNC SYMBS
  if(current_symbol->type == _ident){
    *current_symbol = lexical_analyzer(file);
    if(current_symbol->type == _assign){
      *current_symbol = lexical_analyzer(file);
    } else {
      syntactic_panic_handler(file, current_symbol, "No ':=' on assignment", sync_symbols, sync_symbols_num, error_output);
      return;
    }
    expression(file, current_symbol, sync_symbols, sync_symbols_num, error_output);
  } else if(current_symbol->type == _call) {
    *current_symbol = lexical_analyzer(file);
    if(current_symbol->type == _ident){
      *current_symbol = lexical_analyzer(file);
    } else {
      syntactic_panic_handler(file, current_symbol, "No IDENT for CALL", sync_symbols, sync_symbols_num, error_output);
    }
  } else if(current_symbol->type == _begin) {
    *current_symbol = lexical_analyzer(file);
    int more_commands = 0;
    do {
      if(current_symbol->type == _ident){
        *current_symbol = lexical_analyzer(file);
      } else {
        syntactic_panic_handler(file, current_symbol, "No IDENT for CALL", sync_symbols, sync_symbols_num, error_output);
      }
      if(current_symbol->type == _end_exp){
        more_commands = 1;
        *current_symbol = lexical_analyzer(file);
      } else {
        more_commands = 0;
      }
    } while(more_commands);
  } else if(current_symbol->type == _if) {
    *current_symbol = lexical_analyzer(file);
    condition(file, current_symbol, sync_symbols, sync_symbols_num, error_output);
    if(current_symbol->type == _then){
      *current_symbol = lexical_analyzer(file);
    } else {
      syntactic_panic_handler(file, current_symbol, "No THEN on IF", sync_symbols, sync_symbols_num, error_output);
      return;
    }
    condition(file, current_symbol, sync_symbols, sync_symbols_num, error_output);
  } else if(current_symbol->type == _while) {
    *current_symbol = lexical_analyzer(file);
    condition(file, current_symbol, sync_symbols, sync_symbols_num, error_output);
    if(current_symbol->type == _do){
      *current_symbol = lexical_analyzer(file);
    } else {
      syntactic_panic_handler(file, current_symbol, "No DO on WHILE", sync_symbols, sync_symbols_num, error_output);
      return;
    }
    condition(file, current_symbol, sync_symbols, sync_symbols_num, error_output);
  }
}
void expression(FILE* file, token_t* current_symbol, symbol_t* sync_symbols, int sync_symbols_num, FILE *error_output){
  //TODO ADD SYNC SYMBS
  unary_operator(file, current_symbol, sync_symbols, sync_symbols_num, error_output);
  int more_terms = 0;
  do{
    term(file, current_symbol, sync_symbols, sync_symbols_num, error_output);

    if(current_symbol->type == _plus || current_symbol->type == _minus){
      more_terms = 1;
      *current_symbol = lexical_analyzer(file);
    } else {
      more_terms = 0;
    }
  } while(more_terms);
}
void unary_operator(FILE* file, token_t* current_symbol, symbol_t* sync_symbols, int sync_symbols_num, FILE *error_output){
  //TODO ADD SYNC SYMBS
    if(current_symbol->type == _plus || current_symbol->type == _minus){
      *current_symbol = lexical_analyzer(file);
    } 
}
void term(FILE* file, token_t* current_symbol, symbol_t* sync_symbols, int sync_symbols_num, FILE *error_output){
  //TODO ADD SYNC SYMBS
  int more_factors = 0;
  do{
    factor(file, current_symbol, sync_symbols, sync_symbols_num, error_output);

    if(current_symbol->type == _mult || current_symbol->type == _div){
      more_factors = 1;
      *current_symbol = lexical_analyzer(file);
    } else {
      more_factors = 0;
    }
  } while(more_factors);
}
void factor(FILE* file, token_t* current_symbol, symbol_t* sync_symbols, int sync_symbols_num, FILE *error_output){
  //TODO ADD SYNC SYMBS
  if(current_symbol->type == _ident){
    *current_symbol = lexical_analyzer(file);
  } else if(current_symbol->type == _ident){
    *current_symbol = lexical_analyzer(file);
  } else if(current_symbol->type == _open_exp){
    *current_symbol = lexical_analyzer(file);
    expression(file, current_symbol, sync_symbols, sync_symbols_num, error_output);
    if(current_symbol->type == _close_exp){
      *current_symbol = lexical_analyzer(file);
    } else {
      syntactic_panic_handler(file, current_symbol, "Expression not closed with ')'", sync_symbols, sync_symbols_num, error_output);
    }
  } 
}
void condition(FILE* file, token_t* current_symbol, symbol_t* sync_symbols, int sync_symbols_num, FILE *error_output){
  //TODO ADD SYNC SYMBS
  if(current_symbol->type == _odd){
    *current_symbol = lexical_analyzer(file);
    expression(file, current_symbol, sync_symbols, sync_symbols_num, error_output);
  } else {
    expression(file, current_symbol, sync_symbols, sync_symbols_num, error_output);
    relational(file, current_symbol, sync_symbols, sync_symbols_num, error_output);
    expression(file, current_symbol, sync_symbols, sync_symbols_num, error_output);
  }
}
void relational(FILE* file, token_t* current_symbol, symbol_t* sync_symbols, int sync_symbols_num, FILE *error_output){
  //TODO ADD SYNC SYMBS
  if(current_symbol->type == _equal   || current_symbol->type == _diff    ||
      current_symbol->type == _bigger  || current_symbol->type == _bigg_eq ||
      current_symbol->type == _less    || current_symbol->type == _less_eq){
    *current_symbol = lexical_analyzer(file);
  } 
  else {
    syntactic_panic_handler(file, current_symbol, "Not a relational operator", sync_symbols, sync_symbols_num, error_output);
  }
}
