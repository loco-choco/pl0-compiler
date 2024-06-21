#include <syntactic_analyzer.h>
#include <lexical_analyzer.h>
#include <symbols.h>
#include <error_handler.h>
#include <stdio.h>
#include <stdlib.h>

symbol_t* extend_sync_symbols(symbol_t* sync_symbols, int original_size, int added_symbols){
  symbol_t* syncs_block = malloc(sizeof(symbol_t) * (original_size + added_symbols));
  memcpy(syncs_block, sync_symbols, original_size);
  return syncs_block;
}

void syntactic_analyser(FILE *file, FILE *error_output){
  token_t current_symbol = lexical_analyzer(file);
  symbol_t* syncs_symbs = malloc(sizeof(symbol_t) * 1);
  syncs_symbs[0] = _end_of_file; //So it can always recover if it find an EOF, exiting all the call tree
  program(file, &current_symbol, syncs_symbs, 1, error_output);
  free(syncs_symbs);
}

void syntactic_panic_handler(FILE *file, token_t* current_symbol, char* error, symbol_t* sync_symbols, int sync_symbols_num, FILE *error_output){
  fprintf(error_output, "Syntactic Error: '%s' at line %d\n", error, current_symbol->line_number);
  
  if(current_symbol->error != none){ //Lexical Error!
    char error_type[30];
    get_error_description(current_symbol->error, error_type);
    fprintf(error_output, "\tLexical Error: '%s' at line %d\n", error_type, current_symbol->line_number);
  }
  printf("Entering panic mode!\n");
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
  printf("Found sync symbol, exiting panic mode!\n");
}

//Procedures of the syntactic grammar
void program(FILE* file, token_t* current_symbol, symbol_t* sync_symbols, int sync_symbols_num, FILE *error_output){
  printf("PROGRAM\n");
  //Sync symbols for block
  symbol_t* syncs_block = extend_sync_symbols(sync_symbols, sync_symbols_num, 2);
  syncs_block[sync_symbols_num] = _end_prog;
  syncs_block[sync_symbols_num + 1] = _end_exp;
  block(file, current_symbol, syncs_block, sync_symbols_num + 2, error_output);
  if(current_symbol->type == _end_prog){
    *current_symbol = lexical_analyzer(file);
  } else {
    syntactic_panic_handler(file, current_symbol, "No End Program", sync_symbols, sync_symbols_num, error_output);
  }
  free(syncs_block);
  return;
}
void block(FILE* file, token_t* current_symbol, symbol_t* sync_symbols, int sync_symbols_num, FILE *error_output){
  printf("BLOCK\n");
  //Sync symbs for declaration
  symbol_t* syncs_declaration = extend_sync_symbols(sync_symbols, sync_symbols_num, 7);
  syncs_declaration[sync_symbols_num]     = _ident;
  syncs_declaration[sync_symbols_num + 1] = _call;
  syncs_declaration[sync_symbols_num + 2] = _begin;
  syncs_declaration[sync_symbols_num + 3] = _if;
  syncs_declaration[sync_symbols_num + 4] = _while;
  syncs_declaration[sync_symbols_num + 5] = _end_prog;
  syncs_declaration[sync_symbols_num + 6] = _end_exp;
  //Sync symbs for command
  symbol_t* syncs_command = extend_sync_symbols(sync_symbols, sync_symbols_num, 7);
  syncs_command[sync_symbols_num]     = _end;
  syncs_command[sync_symbols_num + 1] = _end_prog;
  syncs_command[sync_symbols_num + 2] = _ident;
  syncs_command[sync_symbols_num + 3] = _call;
  syncs_command[sync_symbols_num + 4] = _begin;
  syncs_command[sync_symbols_num + 5] = _if;
  syncs_command[sync_symbols_num + 6] = _while;

  declaration(file, current_symbol, syncs_declaration, sync_symbols_num + 7, error_output);
  command(file, current_symbol, syncs_command, sync_symbols_num + 7, error_output);

  free(syncs_declaration);
  free(syncs_command);
}
void declaration(FILE* file, token_t* current_symbol, symbol_t* sync_symbols, int sync_symbols_num, FILE *error_output){
  printf("DECLARATION\n");
  //Sync symbs for constant
  symbol_t* syncs_constant = extend_sync_symbols(sync_symbols, sync_symbols_num, 9);
  syncs_constant[sync_symbols_num]     = _var;
  syncs_constant[sync_symbols_num + 1] = _procedure;
  syncs_constant[sync_symbols_num + 2] = _ident;
  syncs_constant[sync_symbols_num + 3] = _call;
  syncs_constant[sync_symbols_num + 4] = _begin;
  syncs_constant[sync_symbols_num + 5] = _if;
  syncs_constant[sync_symbols_num + 6] = _while;
  syncs_constant[sync_symbols_num + 7] = _end_prog;
  syncs_constant[sync_symbols_num + 8] = _end_exp;
  //Sync symbs for variable
  symbol_t* syncs_variable = extend_sync_symbols(sync_symbols, sync_symbols_num, 8);
  syncs_variable[sync_symbols_num]     = _procedure;
  syncs_variable[sync_symbols_num + 1] = _ident;
  syncs_variable[sync_symbols_num + 2] = _call;
  syncs_variable[sync_symbols_num + 3] = _begin;
  syncs_variable[sync_symbols_num + 4] = _if;
  syncs_variable[sync_symbols_num + 5] = _while;
  syncs_variable[sync_symbols_num + 6] = _end_prog;
  syncs_variable[sync_symbols_num + 7] = _end_exp;
  //Sync symbs for procedure
  symbol_t* syncs_procedure = extend_sync_symbols(sync_symbols, sync_symbols_num, 7);
  syncs_procedure[sync_symbols_num]     = _ident;
  syncs_procedure[sync_symbols_num + 1] = _call;
  syncs_procedure[sync_symbols_num + 2] = _begin;
  syncs_procedure[sync_symbols_num + 3] = _if;
  syncs_procedure[sync_symbols_num + 4] = _while;
  syncs_procedure[sync_symbols_num + 5] = _end_prog;
  syncs_procedure[sync_symbols_num + 6] = _end_exp;

  constant(file, current_symbol, syncs_constant, sync_symbols_num + 9, error_output);
  variable(file, current_symbol, syncs_variable, sync_symbols_num + 8, error_output);
  procedure(file, current_symbol, syncs_procedure, sync_symbols_num + 7, error_output);

  free(syncs_constant);
  free(syncs_variable);
  free(syncs_procedure);
}
void constant(FILE* file, token_t* current_symbol, symbol_t* sync_symbols, int sync_symbols_num, FILE *error_output){
  printf("CONSTANT\n");
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
  printf("VARIABLE\n");
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
  printf("PROCEDURE\n");
  //Sync symbols for block
  symbol_t* syncs_block = extend_sync_symbols(sync_symbols, sync_symbols_num, 2);
  syncs_block[sync_symbols_num] = _end_prog;
  syncs_block[sync_symbols_num + 1] = _end_exp;
  //Sync symbs for procedure
  symbol_t* syncs_procedure = extend_sync_symbols(sync_symbols, sync_symbols_num, 7);
  syncs_procedure[sync_symbols_num]     = _ident;
  syncs_procedure[sync_symbols_num + 1] = _call;
  syncs_procedure[sync_symbols_num + 2] = _begin;
  syncs_procedure[sync_symbols_num + 3] = _if;
  syncs_procedure[sync_symbols_num + 4] = _while;
  syncs_procedure[sync_symbols_num + 5] = _end_prog;
  syncs_procedure[sync_symbols_num + 6] = _end_exp;

  if(current_symbol->type != _procedure){
    free(syncs_block);
    free(syncs_procedure);
    return;
  }
  *current_symbol = lexical_analyzer(file);

  if(current_symbol->type == _ident){
    *current_symbol = lexical_analyzer(file);
  } else {
    syntactic_panic_handler(file, current_symbol, "No IDENT in procedure definition", sync_symbols, sync_symbols_num, error_output);
    free(syncs_block);
    free(syncs_procedure);
    return;
  }

  if(current_symbol->type == _end_exp){
    *current_symbol = lexical_analyzer(file);
  } else {
    syntactic_panic_handler(file, current_symbol, "No ';' closing procedure definition", sync_symbols, sync_symbols_num, error_output);
    free(syncs_block);
    free(syncs_procedure);
    return;
  }
  
  block(file, current_symbol, syncs_block, sync_symbols_num + 2, error_output);

  if(current_symbol->type == _end_exp){
    *current_symbol = lexical_analyzer(file);
  } else {
    syntactic_panic_handler(file, current_symbol, "No ';' closing procedure block", sync_symbols, sync_symbols_num, error_output);
    free(syncs_block);
    free(syncs_procedure);
    return;
  }

  procedure(file, current_symbol, syncs_procedure, sync_symbols_num + 7, error_output);
  free(syncs_block);
  free(syncs_procedure);
}
void command(FILE* file, token_t* current_symbol, symbol_t* sync_symbols, int sync_symbols_num, FILE *error_output){
  printf("COMMAND\n");
  //Sync symbs for expression
  symbol_t* syncs_expression = extend_sync_symbols(sync_symbols, sync_symbols_num, 12);
  syncs_expression[sync_symbols_num]     = _close_exp;
  syncs_expression[sync_symbols_num + 1] = _then;
  syncs_expression[sync_symbols_num + 2] = _do;
  syncs_expression[sync_symbols_num + 3] = _equal;
  syncs_expression[sync_symbols_num + 4] = _diff;
  syncs_expression[sync_symbols_num + 5] = _bigger;
  syncs_expression[sync_symbols_num + 6] = _bigg_eq;
  syncs_expression[sync_symbols_num + 7] = _less;
  syncs_expression[sync_symbols_num + 8] = _less_eq;
  syncs_expression[sync_symbols_num + 9] = _end_exp;
  syncs_expression[sync_symbols_num +10] = _end;
  syncs_expression[sync_symbols_num +11] = _end_prog;
  //Sync symbs for condition
  symbol_t* syncs_condition = extend_sync_symbols(sync_symbols, sync_symbols_num, 2);
  syncs_condition[sync_symbols_num]     = _then;
  syncs_condition[sync_symbols_num + 1] = _do;
  //Sync symbs for command
  symbol_t* syncs_command = extend_sync_symbols(sync_symbols, sync_symbols_num, 7);
  syncs_command[sync_symbols_num]     = _end;
  syncs_command[sync_symbols_num + 1] = _end_prog;
  syncs_command[sync_symbols_num + 2] = _ident;
  syncs_command[sync_symbols_num + 3] = _call;
  syncs_command[sync_symbols_num + 4] = _begin;
  syncs_command[sync_symbols_num + 5] = _if;
  syncs_command[sync_symbols_num + 6] = _while;

  if(current_symbol->error != none) { //Preemptivily check for invalid token, and search for valid start before going down the call tree
      syntactic_panic_handler(file, current_symbol, "Invalid Token in Command Start", syncs_command, sync_symbols_num + 7, error_output);
  }

  if(current_symbol->type == _ident){
    *current_symbol = lexical_analyzer(file);
    if(current_symbol->type == _assign){
      *current_symbol = lexical_analyzer(file);
    } else {
      syntactic_panic_handler(file, current_symbol, "No ':=' on assignment", sync_symbols, sync_symbols_num, error_output);
      free(syncs_condition);
      free(syncs_expression);
      free(syncs_command);
      return;
    }
    expression(file, current_symbol, syncs_expression, sync_symbols_num + 12, error_output);
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
      command(file, current_symbol, syncs_command, sync_symbols_num + 7, error_output);
      if(current_symbol->type == _end_exp){
        more_commands = 1;
        *current_symbol = lexical_analyzer(file);
      } else {
        more_commands = 0;
      }
    } while(more_commands);
    if(current_symbol->type == _end){
      *current_symbol = lexical_analyzer(file);
    } else {
      syntactic_panic_handler(file, current_symbol, "BEGIN not closing with END", sync_symbols, sync_symbols_num, error_output);
      free(syncs_condition);
      free(syncs_expression);
      free(syncs_command);
      return;
    }

  } else if(current_symbol->type == _if) {
    *current_symbol = lexical_analyzer(file);
    condition(file, current_symbol, syncs_condition, sync_symbols_num + 2, error_output);
    if(current_symbol->type == _then){
      *current_symbol = lexical_analyzer(file);
    } else {
      syntactic_panic_handler(file, current_symbol, "No THEN on IF", sync_symbols, sync_symbols_num, error_output);
      free(syncs_condition);
      free(syncs_expression);
      free(syncs_command);
      return;
    }
    command(file, current_symbol, syncs_command, sync_symbols_num + 7, error_output);

  } else if(current_symbol->type == _while) {
    *current_symbol = lexical_analyzer(file);
    condition(file, current_symbol, syncs_condition, sync_symbols_num + 2, error_output);
    if(current_symbol->type == _do){
      *current_symbol = lexical_analyzer(file);
    } else {
      syntactic_panic_handler(file, current_symbol, "No DO on WHILE", sync_symbols, sync_symbols_num, error_output);
      free(syncs_condition);
      free(syncs_expression);
      free(syncs_command);
      return;
    }
    command(file, current_symbol, syncs_command, sync_symbols_num + 7, error_output);
  }
  free(syncs_condition);
  free(syncs_expression);
      free(syncs_command);
}
void expression(FILE* file, token_t* current_symbol, symbol_t* sync_symbols, int sync_symbols_num, FILE *error_output){
  printf("EXPRESSION\n");
  //Sync symbs for unary_operator
  symbol_t* syncs_unary_operator = extend_sync_symbols(sync_symbols, sync_symbols_num, 3);
  syncs_unary_operator[sync_symbols_num]     = _ident;
  syncs_unary_operator[sync_symbols_num + 1] = _number;
  syncs_unary_operator[sync_symbols_num + 2] = _open_exp;
  //Sync symbs for term
  symbol_t* syncs_term = extend_sync_symbols(sync_symbols, sync_symbols_num, 14);
  syncs_term[sync_symbols_num]     = _minus;
  syncs_term[sync_symbols_num + 1] = _plus;
  syncs_term[sync_symbols_num + 2] = _close_exp;
  syncs_term[sync_symbols_num + 3] = _then;
  syncs_term[sync_symbols_num + 4] = _do;
  syncs_term[sync_symbols_num + 5] = _equal;
  syncs_term[sync_symbols_num + 6] = _diff;
  syncs_term[sync_symbols_num + 7] = _less;
  syncs_term[sync_symbols_num + 8] = _less_eq;
  syncs_term[sync_symbols_num + 9] = _bigger;
  syncs_term[sync_symbols_num +10] = _bigg_eq;
  syncs_term[sync_symbols_num +11] = _end_exp;
  syncs_term[sync_symbols_num +12] = _end;
  syncs_term[sync_symbols_num +13] = _end_prog;

  unary_operator(file, current_symbol, syncs_unary_operator, sync_symbols_num + 3, error_output);
  int more_terms = 0;
  do{
    term(file, current_symbol, syncs_term, sync_symbols_num + 14, error_output);

    if(current_symbol->type == _plus || current_symbol->type == _minus){
      more_terms = 1;
      *current_symbol = lexical_analyzer(file);
    } else {
      more_terms = 0;
    }
  } while(more_terms);
  free(syncs_unary_operator);
  free(syncs_term);
}
void unary_operator(FILE* file, token_t* current_symbol, symbol_t* sync_symbols, int sync_symbols_num, FILE *error_output){
  printf("UNARY OP\n");
    if(current_symbol->type == _plus || current_symbol->type == _minus){
      *current_symbol = lexical_analyzer(file);
    } 
}
void term(FILE* file, token_t* current_symbol, symbol_t* sync_symbols, int sync_symbols_num, FILE *error_output){
  printf("TERM\n");
  //Sync symbs for factor
  symbol_t* syncs_factor = extend_sync_symbols(sync_symbols, sync_symbols_num, 16);
  syncs_factor[sync_symbols_num]     = _mult;
  syncs_factor[sync_symbols_num + 1] = _div;
  syncs_factor[sync_symbols_num + 2] = _minus;
  syncs_factor[sync_symbols_num + 3] = _plus;
  syncs_factor[sync_symbols_num + 4] = _close_exp;
  syncs_factor[sync_symbols_num + 5] = _then;
  syncs_factor[sync_symbols_num + 6] = _do;
  syncs_factor[sync_symbols_num + 7] = _equal;
  syncs_factor[sync_symbols_num + 8] = _diff;
  syncs_factor[sync_symbols_num + 9] = _less;
  syncs_factor[sync_symbols_num +10] = _less_eq;
  syncs_factor[sync_symbols_num +11] = _bigger;
  syncs_factor[sync_symbols_num +12] = _bigg_eq;
  syncs_factor[sync_symbols_num +13] = _end_exp;
  syncs_factor[sync_symbols_num +14] = _end;
  syncs_factor[sync_symbols_num +15] = _end_prog;
  int more_factors = 0;
  do{
    factor(file, current_symbol, syncs_factor, sync_symbols_num + 16, error_output);

    if(current_symbol->type == _mult || current_symbol->type == _div){
      more_factors = 1;
      *current_symbol = lexical_analyzer(file);
    } else {
      more_factors = 0;
    }
  } while(more_factors);
  free(syncs_factor);
}
void factor(FILE* file, token_t* current_symbol, symbol_t* sync_symbols, int sync_symbols_num, FILE *error_output){
  printf("FACTOR\n");
  //Sync symbs for expression
  symbol_t* syncs_expression = extend_sync_symbols(sync_symbols, sync_symbols_num, 12);
  syncs_expression[sync_symbols_num]     = _close_exp;
  syncs_expression[sync_symbols_num + 1] = _then;
  syncs_expression[sync_symbols_num + 2] = _do;
  syncs_expression[sync_symbols_num + 3] = _equal;
  syncs_expression[sync_symbols_num + 4] = _diff;
  syncs_expression[sync_symbols_num + 5] = _bigger;
  syncs_expression[sync_symbols_num + 6] = _bigg_eq;
  syncs_expression[sync_symbols_num + 7] = _less;
  syncs_expression[sync_symbols_num + 8] = _less_eq;
  syncs_expression[sync_symbols_num + 9] = _end_exp;
  syncs_expression[sync_symbols_num +10] = _end;
  syncs_expression[sync_symbols_num +11] = _end_prog;

  if(current_symbol->type == _ident){
    *current_symbol = lexical_analyzer(file);
  } else if(current_symbol->type == _number){
    *current_symbol = lexical_analyzer(file);
  } else if(current_symbol->type == _open_exp){
    *current_symbol = lexical_analyzer(file);
    expression(file, current_symbol, syncs_expression, sync_symbols_num + 12, error_output);
    if(current_symbol->type == _close_exp){
      *current_symbol = lexical_analyzer(file);
    } else {
      syntactic_panic_handler(file, current_symbol, "Expression not closed with ')'", sync_symbols, sync_symbols_num, error_output);
    }
  } else if(current_symbol->error != none) { //Added as a way to remove possible invalid token, and restore to a valid symbol
      syntactic_panic_handler(file, current_symbol, "Invalid Token in Expression", sync_symbols, sync_symbols_num, error_output);
  }
  free(syncs_expression);
}
void condition(FILE* file, token_t* current_symbol, symbol_t* sync_symbols, int sync_symbols_num, FILE *error_output){
  printf("CONDITION\n");
  //Sync symbs for expression
  symbol_t* syncs_expression = extend_sync_symbols(sync_symbols, sync_symbols_num, 12);
  syncs_expression[sync_symbols_num]     = _close_exp;
  syncs_expression[sync_symbols_num + 1] = _then;
  syncs_expression[sync_symbols_num + 2] = _do;
  syncs_expression[sync_symbols_num + 3] = _equal;
  syncs_expression[sync_symbols_num + 4] = _diff;
  syncs_expression[sync_symbols_num + 5] = _bigger;
  syncs_expression[sync_symbols_num + 6] = _bigg_eq;
  syncs_expression[sync_symbols_num + 7] = _less;
  syncs_expression[sync_symbols_num + 8] = _less_eq;
  syncs_expression[sync_symbols_num + 9] = _end_exp;
  syncs_expression[sync_symbols_num +10] = _end;
  syncs_expression[sync_symbols_num +11] = _end_prog;
  //Sync symbs for relational
  symbol_t* syncs_relational = extend_sync_symbols(sync_symbols, sync_symbols_num, 5);
  syncs_relational[sync_symbols_num]     = _minus;
  syncs_relational[sync_symbols_num + 1] = _plus;
  syncs_relational[sync_symbols_num + 2] = _ident;
  syncs_relational[sync_symbols_num + 3] = _number;
  syncs_relational[sync_symbols_num + 4] = _open_exp;

  if(current_symbol->type == _odd){
    *current_symbol = lexical_analyzer(file);
    expression(file, current_symbol, syncs_expression, sync_symbols_num + 12, error_output);
  } else {
    expression(file, current_symbol, syncs_expression, sync_symbols_num + 12, error_output);
    relational(file, current_symbol, syncs_relational, sync_symbols_num + 5, error_output);
    expression(file, current_symbol, syncs_expression, sync_symbols_num + 12, error_output);
  }
  free(syncs_expression);
  free(syncs_relational);
}
void relational(FILE* file, token_t* current_symbol, symbol_t* sync_symbols, int sync_symbols_num, FILE *error_output){
  printf("RELATIONAL\n");
  if(current_symbol->type == _equal   || current_symbol->type == _diff    ||
      current_symbol->type == _bigger  || current_symbol->type == _bigg_eq ||
      current_symbol->type == _less    || current_symbol->type == _less_eq){
    *current_symbol = lexical_analyzer(file);
  } 
  else {
    syntactic_panic_handler(file, current_symbol, "Not a relational operator", sync_symbols, sync_symbols_num, error_output);
  }
}
