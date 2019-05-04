#include "tree.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int count = 0;
/**
 * Creates a new node structure and allocates the nedded memory
 *
 * @param token Operation Identifier
 */
Node* new_node(int type)
{
    Node* node           = (Node*) malloc(sizeof(Node));
    node->type           = type;
    node->seq            = NULL;
    return node;
}

/**
 * Adds a new child to a existing node
 *
 * @param node Pointer to the parent node
 * @param child Pointer to the child node
 */
void add_child(Node* node, Node* child)
{
  /*
    node->children_count++;
    node->children = (Node**) realloc(
            node->children,
            node->children_count * sizeof(Node**)
        );

    node->children[node->children_count - 1] = child;
  */
}

/**
 * Generates a source code based on a Abstract Syntax Tree (AST)
 *
 * @param root AST Pointer
 */
void decompile(Node* root)
{
  /*
    if(root != NULL)
    {
        print_lexeme(root->lexeme);

        for(int i = 0; i < root->children_count; i++)
        {
            Node* child = *(root->children + i);

            if(child != NULL) {
                decompile(child);
            }
        }
    }
  */
  printf("Decompile needs to be implemented\n");
}

/**
 * Frees memory previously allocated to the AST structure
 *
 * @param root AST Pointer
 */
void free_tree(Node* root)
{
    Node* aux = (Node*) malloc(sizeof(Node*));
    while(root->seq != NULL){
        aux = root->seq;
        free_node(root);
        root = aux;
    }
  free(root);
  free(aux);
  printf("Memory alocated for tree is now free!\n");
}

void free_node(Node* node){
  if(node != NULL){
    switch(node->type){
      case NODE_TYPE_TER_OP:
        free_node(node->n_if.condition);
        free_node(node->n_if.n_true);
        free_node(node->n_if.n_false);
        free(node);
      break;

      case NODE_TYPE_BIN_OP:
        free_lexeme(node->n_bin_op.op);
        free_node(node->n_bin_op.left);
        free_node(node->n_bin_op.right);
        free(node);
      break;

      case NODE_TYPE_UN_OP:
        free_lexeme(node->n_un_op.op);
        free_node(node->n_un_op.operand);
        free(node);
      break;

      case NODE_TYPE_IF:
        free_node(node->n_if.condition);
        free_node(node->n_if.n_true);
        free_node(node->n_if.n_false);
        free(node);
      break;

      case NODE_TYPE_FOR:
        free_node(node->n_for.setup);
        free_node(node->n_for.condition);
        free_node(node->n_for.increment);
        free_node(node->n_for.code);
        free(node);
      break;

      case NODE_TYPE_WHILE:
        free_node(node->n_while.condition);
        free_node(node->n_while.code);
        free(node);
      break;

      case NODE_TYPE_FUNC_CALL:
        free_lexeme(node->n_call_or_access.identifier);
        free_node(node->n_call_or_access.index_or_param);
        free(node);
      break;

      case NODE_TYPE_FUNC_DECL:
        free_lexeme(node->n_func_decl.identifier);
        free_node(node->n_func_decl.param);
        free_node(node->n_func_decl.code);
        free_lexeme(node->n_func_decl.type);
        free(node);
      break;

      case NODE_TYPE_FUNC_PARAM:
        free_lexeme(node->n_var_decl.identifier);
        free_lexeme(node->n_var_decl.type);
        free(node);
      break;

      case NODE_TYPE_VAR_ACCESS:
        free_lexeme(node->n_call_or_access.identifier);
        free_node(node->n_call_or_access.index_or_param);
        free(node);
      break;

      case NODE_TYPE_VAR_DECL:
        free_lexeme(node->n_var_decl.identifier);
        free_lexeme(node->n_var_decl.type);
        free_node(node->n_var_decl.size);
        free_node(node->n_var_decl.value);
        free(node);
      break;

      case NODE_TYPE_VAR_ATTR:
        free_lexeme(node->n_var_attr.identifier);
        free_node(node->n_var_attr.index);
        free_node(node->n_var_attr.value);
        free(node);
      break;

      case NODE_TYPE_INPUT:
        free_node(node->n_io.params);
        free(node);
      break;

      case NODE_TYPE_OUTPUT:
        free_node(node->n_io.params);
        free(node);
      break;

      case NODE_TYPE_SHIFT_LEFT:
        free(node);
      break;

      case NODE_TYPE_SHIFT_RIGHT:
        free(node);
      break;

      case NODE_TYPE_RETURN:
        free_node(node->seq);
        free(node);
      break;

      case NODE_TYPE_BREAK:
        free(node);
      break;

      case NODE_TYPE_CONTINUE:
        free(node);
      break;

      case NODE_TYPE_LITERAL:
        free_lexeme(node->n_literal.literal);
        free(node);
      break;

      default:
        free(node);
      break;
    }
  }
}

/**
 * Frees memory allocated for a Lexeme
 *
 * @param lex Lexeme Pointer
 * @return Allways 0, to override old pointer
 */
int free_lexeme(Lexeme* lex)
{
    if(lex != NULL)
    {
        // Free string value if allocated
        if(lex->token_type != SPECIAL_CHAR &&
            lex->literal_type != INT &&
            lex->literal_type != FLOAT &&
            lex->literal_type != BOOL &&
            lex->literal_type != CHAR )
        {
            free(lex->token_value.v_string);
        }

        free(lex);
    }

    return 1;
}

/**
 * Prints a Lexeme's value
 *
 * @param lex Lexeme
 */
void print_lexeme(Lexeme* lex)
{
    if(lex != NULL)
    {
        if(lex->token_type == SPECIAL_CHAR)
        {
            printf("%c ", lex->token_value.v_char);
        }
        else
        {
            switch(lex->literal_type)
            {
                case INT:
                    printf("%d ", lex->token_value.v_int);
                    break;
                case FLOAT:
                    printf("%f ", lex->token_value.v_float);
                    break;
                case BOOL:
                    printf("%s ", lex->token_value.v_bool ? "true" : "false");
                    break;
                case CHAR:
                    printf("\'");
                    print_char(lex->token_value.v_char);
                    printf("\' ");
                    break;
                case STRING:
                    print_string(lex->token_value.v_string);
                    printf(" ");
                    break;
                default:
                    printf("%s ",lex->token_value.v_string);
                    break;
            }
        }
    }
}
void print_char (char v_char){
  switch(v_char){
    case '\n':
      printf("\\n");
    break;

    case '\a':
      printf("\\a");
    break;

    case '\b':
      printf("\\b");
    break;

    case '\f':
      printf("\\f");
    break;

    case '\r':
      printf("\\r");
    break;

    case '\t':
      printf("\\t");
    break;

    case '\v':
      printf("\\v");
    break;

    case '\\':
      printf("\\\\");
    break;

    case '\'':
      printf("\\\'");
    break;

    case '\"':
      printf("\\\"");
    break;

    case '\?':
      printf("\\\?");
    break;

    default:
        printf("%c", v_char);
    break;
  }
}

void print_string(char* v_string){
    int i;
    printf("\"");
    for(i = 0; i < strlen(v_string); i++) {
        print_char(v_string[i]);
    }
    printf("\"");
}

struct node* create_node_ter_op(Node* condition, Node* ifTrue, Node* ifFalse)
{
    struct node* node = new_node(NODE_TYPE_TER_OP);

    node->n_if.condition = condition;
    node->n_if.n_true    = ifTrue;
    node->n_if.n_false   = ifFalse;

    return node;
}

struct node* create_node_bin_op(Lexeme* op, Node* left, Node* right)
{
    struct node* node = new_node(NODE_TYPE_BIN_OP);

    node->n_bin_op.op = op;
    node->n_bin_op.left = left;
    node->n_bin_op.right = right;

    return node;
}

struct node* create_node_un_op(Lexeme* op, Node* operand)
{
    struct node* node = new_node(NODE_TYPE_UN_OP);

    node->n_un_op.op = op;
    node->n_un_op.operand = operand;

    return node;
}

struct node* create_node_if(Node* condition, Node* ifTrue, Node* ifFalse)
{
    struct node* node = new_node(NODE_TYPE_IF);

    node->n_if.condition = condition;
    node->n_if.n_true = ifTrue;
    node->n_if.n_false = ifFalse;

    return node;
}

struct node* create_node_for(Node* setup, Node* condition, Node* increment, Node* code)
{
    struct node* node = new_node(NODE_TYPE_FOR);

    node->n_for.setup       = setup;
    node->n_for.condition   = condition;
    node->n_for.increment   = increment;
    node->n_for.code        = code;

    return node;
}


struct node* create_node_while(Node* condition, Node* code)
{
    struct node* node = new_node(NODE_TYPE_WHILE);

    node->n_while.condition = condition;
    node->n_while.code      = code;

    return node;
}


struct node* create_node_func_call(Lexeme* identifier, Node* parameters)
{
    struct node* node = new_node(NODE_TYPE_FUNC_CALL);

    node->n_call_or_access.identifier       = identifier;
    node->n_call_or_access.index_or_param   = parameters;

    return node;
}

struct node* create_node_func_decl(Lexeme* identifier, Lexeme* type, int is_static, Node* parameters, Node* code)
{
    struct node* node = new_node(NODE_TYPE_FUNC_DECL);

    node->n_func_decl.identifier  = identifier;
    node->n_func_decl.param       = parameters;
    node->n_func_decl.code        = code;
    node->n_func_decl.type        = type;
    node->n_func_decl.is_static   = is_static;

    return node;
}

struct node* create_node_func_param(Lexeme* identifier, Lexeme* type, int is_const)
{
    struct node* node = new_node(NODE_TYPE_FUNC_PARAM);

    node->n_var_decl.identifier  = identifier;
    node->n_var_decl.size        = NULL;
    node->n_var_decl.type        = type;
    node->n_var_decl.is_static   = FALSE;
    node->n_var_decl.is_const    = is_const;
    node->n_var_decl.value       = NULL;

    return node;
}

struct node* create_node_var_access(Lexeme* identifier, Node* index)
{
    struct node* node = new_node(NODE_TYPE_VAR_ACCESS);

    node->n_call_or_access.identifier     = identifier;
    node->n_call_or_access.index_or_param = index;

    return node;
}

struct node* create_node_var_decl(Lexeme* identifier, Node* size, Lexeme* type, int is_static, int is_const, Node* value)
{
    struct node* node = new_node(NODE_TYPE_VAR_DECL);

    node->n_var_decl.identifier   = identifier;
    node->n_var_decl.size         = size;
    node->n_var_decl.type         = type;
    node->n_var_decl.is_static    = is_static;
    node->n_var_decl.is_const     = is_const;
    node->n_var_decl.value        = value;

    return node;
}

struct node* create_node_var_attr(Lexeme* identifier, Node* index, Node* value)
{
    struct node* node = new_node(NODE_TYPE_VAR_ATTR);

    node->n_var_attr.identifier = identifier;
    node->n_var_attr.index = index;
    node->n_var_attr.value = value;

    return node;
}

struct node* create_node_input(Node* input)
{
    Node* node = new_node(NODE_TYPE_INPUT);

    node->n_io.params = input;

    return node;
}

struct node* create_node_output(Node* output)
{
    struct node* node = new_node(NODE_TYPE_OUTPUT);

    node->n_io.params = output;

    return node;
}

struct node* create_node_shift_left()
{
    struct node* node = new_node(NODE_TYPE_SHIFT_LEFT);

    return node;
}

struct node* create_node_shift_right()
{
    struct node* node = new_node(NODE_TYPE_SHIFT_RIGHT);

    return node;
}


struct node* create_node_return(Node* expression)
{
    struct node* node = new_node(NODE_TYPE_RETURN);

    node->seq = expression;

    return node;
}

struct node* create_node_break()
{
    struct node* node = new_node(NODE_TYPE_BREAK);

    return node;
}

struct node* create_node_continue()
{
    struct node* node = new_node(NODE_TYPE_CONTINUE);

    return node;
}

struct node* create_node_literal(Lexeme* value)
{
    struct node* node = new_node(NODE_TYPE_LITERAL);

    node->n_literal.literal = value;

    return node;
}
