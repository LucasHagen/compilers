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

int identifier_in_scope(Scope* scope, char* id)
{
    for(int i = 0; i < scope->size; i++)
    {
        if(strcmp(scope->children[i]->id, id) == 0)
        {
            return 1;
        }
    }

    return 0;
}

ST_LINE* create_function_register(Node* node)
{
    ST_LINE* reg = (ST_LINE*) malloc(sizeof(ST_LINE));

    reg->id                 = node->n_func_decl.identifier->token_value.v_string;
    reg->declaration_line   = node->n_func_decl.identifier->line_number;
    reg->nature             = NATUREZA_FUNCAO;
    reg->token_type         = node->n_func_decl.type_id;
    reg->token_size         = strlen(reg->id);
    reg->is_static          = node->n_func_decl.is_static;
    reg->is_const           = 0;
    reg->lexeme             = node->n_func_decl.identifier;
    // TODO: PARAMS

    return reg;
}

void throw_error(int error_code, int line_number)
{
    const char* err_format = "Erro na linha %d: %s;\n";
    switch(error_code)
    {
        case ERR_UNDECLARED:
        	printf(err_format, line_number, "identificador não declarado");
        	break;

        case ERR_DECLARED:
        	printf(err_format, line_number, "identificador já declarado");
        	break;

        case ERR_VARIABLE:
        	printf(err_format, line_number, "identificador deve ser utilizado como variável");
        	break;

        case ERR_VECTOR:
        	printf(err_format, line_number, "identificador deve ser utilizado como vetor");
        	break;

        case ERR_FUNCTION:
        	printf(err_format, line_number, "identificador deve ser utilizado como função");
        	break;

        case ERR_WRONG_TYPE:
        	printf(err_format, line_number, "tipos incompatíveis");
        	break;

        case ERR_STRING_TO_X:
        	printf(err_format, line_number, "coerção impossível de var do tipo string");
        	break;

        case ERR_CHAR_TO_X:
        	printf(err_format, line_number, "coerção impossível de var do tipo char");
        	break;

        case ERR_MISSING_ARGS:
        	printf(err_format, line_number, "faltam argumentos");
        	break;

        case ERR_EXCESS_ARGS:
        	printf(err_format, line_number, "sobram argumentos");
        	break;

        case ERR_WRONG_TYPE_ARGS:
        	printf(err_format, line_number, "argumentos incompatíveis");
        	break;

        case ERR_WRONG_PAR_INPUT:
        	printf(err_format, line_number, "parâmetro não é identificador");
        	break;

        case ERR_WRONG_PAR_OUTPUT:
        	printf(err_format, line_number, "parâmetro não é literal string ou expressão");
        	break;

        case ERR_WRONG_PAR_RETURN:
        	printf(err_format, line_number, "parâmetro não é expressão compatível com tipo do retorno");
        	break;

        default:
            printf("Erro na linha %d;\n", line_number);
            break;
    }
    exit(error_code);
}
