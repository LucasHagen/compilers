#include "scope.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Creates a empty scope
 */
Scope* create_empty_scope()
{
    Scope* s = (Scope*) malloc(sizeof(Scope));

    s->children = (ST_LINE**) malloc(sizeof(ST_LINE**));
    s->max_size = 1;
    s->size = 0;

    return s;
}

/**
 * Adds a register in the scope
 */
void add_register(Scope* stack, ST_LINE* value)
{
    if(stack->size >= stack->max_size)
    {
        stack->max_size++;

        stack->children = (ST_LINE**) realloc(stack->children,
            stack->max_size * sizeof(ST_LINE**));
    }

    stack->children[stack->size] = value;
    stack->size++;
}

ST_LINE* identifier_in_scope(Scope* scope, char* id)
{
    for(int i = scope->size - 1; i >= 0; i--)
    {
        if(strcmp(scope->children[i]->id, id) == 0)
        {
            return scope->children[i];
        }
    }

    return NULL;
}

ST_LINE* create_function_register(Node* node)
{
    ST_LINE* reg = (ST_LINE*) malloc(sizeof(ST_LINE));

    reg->id                 = node->n_func_decl.identifier->token_value.v_string;
    reg->declaration_line   = node->n_func_decl.identifier->line_number;
    reg->nature             = NATUREZA_FUNCAO;
    reg->token_type         = node->val_type;
    reg->token_size         = strlen(reg->id);
    reg->is_static          = node->n_func_decl.is_static;
    reg->is_const           = 0;
    reg->lexeme             = node->n_func_decl.identifier;
    // TODO: PARAMS

    return reg;
}

ST_LINE* create_var_register(Node* node)
{
    ST_LINE* reg = (ST_LINE*) malloc(sizeof(ST_LINE));

    reg->id                 = node->n_var_decl.identifier->token_value.v_string;
    reg->declaration_line   = node->n_var_decl.identifier->line_number;
    reg->nature             = NATUREZA_VARIAVEL;
    reg->token_type         = node->val_type;
    reg->token_size         = strlen(reg->id);
    reg->is_static          = node->n_var_decl.is_static;
    reg->is_const           = node->n_var_decl.is_const;
    reg->lexeme             = node->n_var_decl.identifier;
    // TODO: PARAMS

    return reg;
}
