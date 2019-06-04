#include "scope.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Authors:
- Gabriel Pakulski da Silva - 00274701
- Lucas Sonntag Hagen       - 00274698
*/

/**
 * Creates a empty scope
 */
Scope* create_empty_scope(char* offset_reg)
{
    Scope* s = (Scope*) malloc(sizeof(Scope));

    s->children = (ST_LINE**) malloc(sizeof(ST_LINE**));
    s->max_size = 1;
    s->size = 0;
    s->offset_reg = offset_reg;

    return s;
}

/**
 * Adds a register in the scope
 */
void add_register(Scope* scope, ST_LINE* value)
{
    ST_LINE** children;
    if(scope->size >= scope->max_size)
    {
        scope->max_size++;

        children = (ST_LINE**) realloc(scope->children,
            scope->max_size * sizeof(ST_LINE**));
        if(children != NULL)
            scope->children = children;
    }

    // IMPLEMENTED ONLY FOR INTEGER AND BOOL VARIABLES
    if(value->nature == NATUREZA_VARIAVEL && (value->token_type == INT || value->token_type == BOOL))
    {
        value->offset = get_current_offset(scope);
    }

    scope->children[scope->size] = value;
    scope->size++;
}

ST_LINE* get_top_register(Scope* scope)
{
    ST_LINE* result = NULL;

    if(scope->size != 0)
    {
        result = scope->children[scope->size - 1];
    }

    return result;
}

int get_current_offset(Scope* scope)
{
    // IMPLEMENTED ONLY FOR INTEGER AND BOOL VARIABLES
    int result = 0;
    for(int i = scope->size - 1; i >= 0; i--)
    {
        if(scope->children[i]->nature == NATUREZA_VARIAVEL &&
                (scope->children[i]->token_type == INT || scope->children[i]->token_type == BOOL))
        {
            result += scope->children[i]->token_size;
        }
    }

    return result;
}

ST_LINE* identifier_in_scope(Scope* scope, char* id)
{
    for(int i = scope->size - 1; i >= 0; i--)
    {
        if(scope->children[i]->nature > NATUREZA_LITERAL_BOOL && strcmp(scope->children[i]->id, id) == 0)
        {
            return scope->children[i];
        }
    }

    return NULL;
}

ST_LINE* create_function_register(Lexeme* identifier, Node* params, int val_type, int is_static)
{
    ST_LINE* reg = (ST_LINE*) malloc(sizeof(ST_LINE));
    reg->id                 = identifier->token_value.v_string;
    reg->declaration_line   = identifier->line_number;
    reg->nature             = NATUREZA_FUNCAO;
    reg->token_type         = val_type;
    reg->token_size         = type_size(val_type);
    reg->is_static          = is_static;
    reg->is_const           = 0;
    reg->lexeme             = identifier;
    reg->num_function_args  = 0;
    reg->offset             = 0;

    add_function_args(reg, params);
    return reg;
}

int count_params(Node* params){
    Node* aux = params;
    int i = 0;
    if(params){
        do{
            i++;
            aux = aux->seq;
        }while(aux != NULL);
    }
    return i;
}

void add_function_args(ST_LINE* reg, Node* params){
    Node* aux = params;
    int i = 0;;
    if(params){
        i = count_params(params);
        aux = params;
        reg->function_args = (function_arg*) malloc(i*sizeof(function_arg));
        reg->function_args[0] = new_function_arg(aux);
        reg->num_function_args++;
        while(aux->seq != NULL){
            aux = aux->seq;
      //reg->function_args = realloc(reg->function_args,reg->num_function_args*sizeof(struct fuction_argument));
            reg->function_args[reg->num_function_args] = new_function_arg(aux);
            reg->num_function_args++;
        }
    }

#ifdef COMP_DEBUG
  printf("Added %d arguments\n",reg->num_function_args);
  for(i=0;i<reg->num_function_args;i++){
    printf("Type: %d \tId: %s\n",reg->function_args[i].type,reg->function_args[i].identifier);
  }
#endif
    aux = NULL;
    return;
}

function_arg new_function_arg(Node* param){
    function_arg arg;
    int type = get_lexeme_type(param->n_var_decl.type);
    if(type == NO_TYPE)
    {
        printf("Erro na captura do tipo do parametro de funcao\n");
    }
    else
    {
        arg.type = type;
        arg.is_const = param->n_var_decl.is_const;
        arg.identifier = param->n_var_decl.identifier->token_value.v_string;
    }
    return arg;
}

int get_lexeme_type(Lexeme* keyword){
  if(keyword->token_type == KEYWORD){
    if(strcmp(keyword->token_value.v_string,"int") == 0)
      return INT;
    else if(strcmp(keyword->token_value.v_string,"float") == 0)
      return FLOAT;
    else if(strcmp(keyword->token_value.v_string,"char") == 0)
      return CHAR;
    else if(strcmp(keyword->token_value.v_string,"string") == 0)
      return STRING;
    else if(strcmp(keyword->token_value.v_string,"bool") == 0)
      return BOOL;
    else
      return NO_TYPE;
  }
  return NO_TYPE;
}

ST_LINE* create_literal(Lexeme* lex, int nature){
    ST_LINE* reg = (ST_LINE*) malloc(sizeof(ST_LINE));
    reg->id                 = (char*) "";
    reg->declaration_line   = lex->line_number;
    reg->is_static          = 0;
    reg->is_const           = 1;
    reg->lexeme             = lex;
    reg->num_function_args  = 0;
    reg->function_args      = NULL;
    reg->offset             = 0;
    switch(nature){
        case NATUREZA_LITERAL_INT:
            reg->token_type = INT;
            reg->nature     = NATUREZA_LITERAL_INT;
            reg->token_size = SIZE_INT;
        break;
        case NATUREZA_LITERAL_FLOAT:
            reg->token_type = FLOAT;
            reg->nature     = NATUREZA_LITERAL_FLOAT;
            reg->token_size = SIZE_FLOAT;
        break;
        case NATUREZA_LITERAL_CHAR:
            reg->token_type = CHAR;
            reg->nature     = NATUREZA_LITERAL_CHAR;
            reg->token_size = SIZE_CHAR;
        break;
        case NATUREZA_LITERAL_STRING:
            reg->token_type = STRING;
            reg->nature     = NATUREZA_LITERAL_STRING;
            reg->token_size = SIZE_STRING*strlen(reg->id);
        break;
        case NATUREZA_LITERAL_BOOL:
            reg->token_type = BOOL;
            reg->nature     = NATUREZA_LITERAL_BOOL;
            reg->token_size = SIZE_BOOL;
        break;
    }
    return reg;
}

ST_LINE* create_var_register(Node* node)
{
    ST_LINE* reg = (ST_LINE*) malloc(sizeof(ST_LINE));

    reg->id                 = node->n_var_decl.identifier->token_value.v_string;
    reg->declaration_line   = node->n_var_decl.identifier->line_number;
    reg->nature             = NATUREZA_VARIAVEL;
    reg->token_type         = node->val_type;
    reg->token_size         = type_size(node->val_type);
    reg->is_static          = node->n_var_decl.is_static;
    reg->is_const           = node->n_var_decl.is_const;
    reg->lexeme             = node->n_var_decl.identifier;
    reg->offset             = 0;
    reg->num_function_args  = 0;
    reg->function_args      = NULL;

    return reg;
}

int type_size(int type)
{
    switch(type)
    {
        case INT:
            return SIZE_INT;
            break;
        case FLOAT:
            return SIZE_FLOAT;
            break;
        case BOOL:
            return SIZE_BOOL;
            break;
        case CHAR:
            return SIZE_CHAR;
            break;
        case STRING:
            return SIZE_STRING;
            break;
    }
    return 1;
}

int match_decl_with_call(ST_LINE* decl, Node* params, int line){
    // Missing args.
    if(decl->num_function_args > count_params(params)) {
        throw_error(ERR_MISSING_ARGS, line);
    }
    // Excess args.
    else if(decl->num_function_args < count_params(params)) {
        throw_error(ERR_EXCESS_ARGS, line);
    }

    // Type mismatch.
    Node* aux = params;
    for(int i = 0; i < decl->num_function_args; i++)
    {
        can_convert(decl->function_args[i].type, aux->val_type, 0, ERR_WRONG_TYPE_ARGS);
        aux = aux->seq;
    }

    return 0;
}
