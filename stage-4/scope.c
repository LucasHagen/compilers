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
    reg->num_function_args  = 0;
    add_function_args(reg,node->n_func_decl.param);
    return reg;
}

void add_function_args(ST_LINE* reg, Node* params){
  Node* aux = params;
  int i = -1;
  do{
    i++;
    aux = aux->seq;
  }while(aux != NULL);

  aux = params;
  if(params){
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
    printf("Type: %d\nId: %s\n",reg->function_args[i].type,reg->function_args[i].identifier);
  }
#endif
  aux = NULL;
  return;
}

function_arg new_function_arg(Node* param){
  function_arg arg;
  int type = get_lexeme_type(param->n_var_decl.type);
  if(type == NO_TYPE)
    printf("Erro na captura do tipo do parametro de funcao\n");
  else{
    arg.type = type;
    arg.is_const = param->n_var_decl.is_const;
    arg.identifier = strdup(param->n_var_decl.identifier->token_value.v_string);
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
}

ST_LINE* create_literal(Lexeme* node, int nature){
  ST_LINE* reg = (ST_LINE*) malloc(sizeof(ST_LINE));

  switch(nature){
    case NATUREZA_LITERAL_INT:
      break;
    case NATUREZA_LITERAL_FLOAT:
      break;
    case NATUREZA_LITERAL_CHAR:
      break;
    case NATUREZA_LITERAL_STRING:
      break;
    case NATUREZA_LITERAL_BOOL:
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
    reg->token_size         = strlen(reg->id);
    reg->is_static          = node->n_var_decl.is_static;
    reg->is_const           = node->n_var_decl.is_const;
    reg->lexeme             = node->n_var_decl.identifier;
    reg->num_function_args  = 0;
    reg->function_args      = NULL;
    // TODO: PARAMS

    return reg;
}
