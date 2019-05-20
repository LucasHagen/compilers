#include "scope.h"

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

ST_LINE* create_function_register(Lexeme* func, int type, int is_const, int is_static)
{
    ST_LINE* reg = (ST_LINE*) malloc(sizeof(ST_LINE));

    reg->id                 = func->token_value.v_string;
    reg->declaration_line   = func->line_number;
    reg->nature             = NATUREZA_FUNCAO;
    reg->token_type         = type;
    reg->token_size         = strlen(reg->id);
    reg->is_static          = is_static;
    reg->is_const           = is_const;
    reg->lexeme             = func;

    return reg;
}
