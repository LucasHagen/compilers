#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "lexeme.h"
#include "defines.h"
#include "tree.h"

typedef struct scope_struct {

    ST_LINE** children;
    int       max_size;
    int       size    ;

} Scope;

/**
 * Creates a empty scope
 */
Scope* create_empty_scope();

/**
 * Adds a register in the scope
 */
void add_register(Scope* stack, ST_LINE* value);

ST_LINE* identifier_in_scope(Scope* scope, char* id);

ST_LINE* create_function_register(Node* node);
ST_LINE* create_var_register(Node* node);

#endif
