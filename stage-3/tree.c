#include "tree.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Creates a new node structure and allocates the nedded memory
 *
 * @param token Operation Identifier
 */
Node* new_node(int type, Lexeme* lexeme)
{
    Node* node           = (Node*) malloc(sizeof(Node));
    node->type           = type;
    node->lexeme         = lexeme;
    node->children_count = 0;
    node->children       = (Node**) malloc(sizeof(Node**));
    node->seq           = NULL;
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
    node->children_count++;
    node->children = (Node**) realloc(
            node->children,
            node->children_count * sizeof(Node**)
        );

    node->children[node->children_count - 1] = child;
}

/**
 * Generates a source code based on a Abstract Syntax Tree (AST)
 *
 * @param root AST Pointer
 */
void decompile(Node* root)
{
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
}

/**
 * Frees memory previously allocated to the AST structure
 *
 * @param root AST Pointer
 */
void free_tree(Node* root)
{
    if(root != NULL) // NULL
    {
        if(root->lexeme != NULL)
        {
            free_lexeme(root->lexeme);
        }

        for(int i = 0; i < root->children_count; i++)
        {
            Node* child = *(root->children + i);

            if(child != NULL) {
                free_tree(child);
            }
        }

        free(root->children);
        free(root);
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
  for(i=0;i<strlen(v_string);i++){
    print_char(v_string[i]);
  }
  printf("\"");
}

struct node* create_simple_node(int type)
{
    struct node* n = malloc(sizeof(struct node));
    node->type = type;

    return n;
}


struct node* create_node_ter_op(Node* condition, Node* ifTrue, Node* ifFalse)
{
    struct node* node = create_simple_node(NODE_TYPE_TER_OP);

    node->n_if.condition = condition;
    node->n_if.n_true    = ifTrue;
    node->n_if.n_false   = ifFalse;

    return node;
}

struct node* create_node_bin_op(int op, Node* left, Node* right)
{
    struct node* node = create_simple_node(NODE_TYPE_BIN_OP);

    node->n_bin_op.op = op;
    node->n_bin_op.left = left;
    node->n_bin_op.right = right;

    return node;
}

struct node* create_node_un_op(int op, Node* operand)
{
    struct node* node = create_simple_node(NODE_TYPE_UN_OP);

    node->n_un_op.op = op;
    node->n_un_op.operand = operand;

    return node;
}

struct node* crete_node_if(Node* condition, Node* ifTrue, Node* ifFalse)
{
    struct node* node = create_simple_node(NODE_TYPE_IF);

    node->n_if.condition = condition;
    node->n_if.n_true = ifTrue;
    node->n_if.n_false = ifFalse;

    return node;
}

struct node* create_node_for(Node* setup, Node* condition, Node* increment, Node* code)
{
    struct node* node = create_simple_node(NODE_TYPE_FOR);

    node->n_for.setup       = setup;
    node->n_for.condition   = condition;
    node->n_for.increment   = increment;
    node->n_for.code        = code;

    return node;
}


struct node* create_node_while(Node* condition, Node* code)
{
    struct node* node = create_simple_node(NODE_TYPE_WHILE);

    node->n_while.condition = condition;
    node->n_while.code      = code;

    return node;
}


struct node* create_node_func_call(Lexeme* identifier, Node* parameters)
{
    struct node* node = create_simple_node(NODE_TYPE_FUNC_CALL);

    node->n_call_or_access.identifier       = identifier;
    node->n_call_or_access.index_or_param   = parameters;

    return node;
}


struct node* create_node_func_decl(Lexeme* identifier, int type, int is_static, Node* parameters, Node* code);
struct node* create_node_func_param(Lexeme* identifier, int type, int is_const);
struct node* create_node_var_access(Lexeme* identifier, Node* index);
struct node* create_node_var_decl(Node* identifier, int type, int is_static, int is_const, Node* value);
struct node* create_node_var_attr(Lexeme* identifier, int index, Node* value);
struct node* create_node_input(Node* input);
struct node* create_node_output(Node* output);
struct node* create_node_shift_left();
struct node* create_node_shift_right();
struct node* create_node_return(Node* expression);
struct node* create_node_break();
struct node* create_node_continue();
struct node* create_node_literal(Lexeme* value);
