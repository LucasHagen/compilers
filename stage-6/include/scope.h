#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "lexeme.h"
#include "defines.h"
#include "tree.h"
#include "stack_frame.h"

/*
Authors:
- Gabriel Pakulski da Silva - 00274701
- Lucas Sonntag Hagen       - 00274698
*/

typedef struct scope_struct {

    ST_LINE** children;
    int       max_size;
    int       size    ;
    char*     offset_reg;

    int       is_global_scope;
    int       used_size;

} Scope;

/**
 * Creates a empty scope
 */
Scope* create_empty_scope(char* offset_reg, int is_global_scope);

/**
 * Adds a register in the scope
 */
void add_register(Scope* scope, ST_LINE* value, Scope* base_scope);

ST_LINE* get_top_register(Scope* scope);

ST_LINE* identifier_in_scope(Scope* scope, char* id);

int get_current_offset(Scope* scope);

ST_LINE* create_function_register(Lexeme* identifier, Node* params, int val_type, int is_static);
ST_LINE* create_var_register(Node* node);
ST_LINE* create_literal(Lexeme* node, int nature);

int type_size(int type);

void throw_error(int error_code, int line_number);


//A lista de argumentos está invertida !!!!!!!!!!!!!!
void add_function_args(ST_LINE* reg, Node* params);
function_arg new_function_arg(Node* param);
int get_lexeme_type(Lexeme* keyword);

/** Compares a function call with its declaration.
*   Returns
*       0 <- if the function call is correct.
*       ERR_MISSING_ARGS
*       ERR_EXCESS_ARGS
*       ERR_WRONG_TYPE_ARGS
*/
int match_decl_with_call(ST_LINE* decl, Node* params, int line);
#endif
