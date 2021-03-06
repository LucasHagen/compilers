#include "tree.h"
#include "printer.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
	Authors:
		- Gabriel Pakulski da Silva - 00274701
		- Lucas Sonntag Hagen       - 00274698
*/

// To show debug messages, uncomment the line bellow and compile again
//#define COMP_DEBUG

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
 * Frees memory previously allocated to the AST structure
 *
 * @param root AST Pointer
 */
void free_tree(Node* root)
{
    #ifdef COMP_DEBUG
    printf("========== START FREE TREE ==========\n");
    #endif

    if(root != NULL)
    {
        free_node(root);
    }

    #ifdef COMP_DEBUG
    printf("Memory alocated for tree is now free!\n");
    #endif
}

void free_node(Node* node){
    if(node != NULL){
        int seq_type = -1;
        if(node->seq != NULL) {
            seq_type = node->seq->type;
            free_node(node->seq);
            node->seq = NULL;
        }

#ifdef COMP_DEBUG
        printf("Node entrou na free_node()\n");
        printf("- Tipo: %d\n",     node->type);
        printf("- Tipo seq: %d\n", seq_type);
#endif

        switch(node->type){
          case NODE_TYPE_COMMAND_BLOCK:
            free_node(node->n_cmd_block.command);
            free(node);
            break;

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

          case NODE_TYPE_GLOBAL_VAR_DECL:
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
            free_node(node->n_shift.count);
            free_node(node->n_shift.var);
            free(node);
          break;

          case NODE_TYPE_SHIFT_RIGHT:
            free_node(node->n_shift.count);
            free_node(node->n_shift.var);
            free(node);
          break;

          case NODE_TYPE_RETURN:
            free_node(node->n_io.params);
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
            #ifdef COMP_DEBUG
            printf(" - [ERROR] NODE TYPE NOT FOUND!\n");
            printf(" - [ERROR] NODE TYPE NOT FOUND!\n");
            printf(" - [ERROR] NODE TYPE NOT FOUND!\n");
            #endif
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
#ifdef COMP_DEBUG
    printf("- in free lexeme\n");
#endif

    if(lex != NULL)
    {
        // Free string value if allocated
        if(lex->token_type != SPECIAL_CHAR &&
            lex->literal_type != INT &&
            lex->literal_type != FLOAT &&
            lex->literal_type != BOOL &&
            lex->literal_type != CHAR )
        {
#ifdef COMP_DEBUG
            printf("- String: '%s';\n",lex->token_value.v_string);
#endif
            free(lex->token_value.v_string);
        }

        free(lex);
    }
    #ifdef COMP_DEBUG
    printf("- out free lexeme\n");
    #endif

    return 1;
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

struct node* create_node_global_var_decl(Lexeme* identifier, Node* size, Lexeme* type, int is_static, Node* value)
{
    struct node* node = new_node(NODE_TYPE_GLOBAL_VAR_DECL);

    node->n_var_decl.identifier   = identifier;
    node->n_var_decl.size         = size;
    node->n_var_decl.type         = type;
    node->n_var_decl.is_static    = is_static;
    node->n_var_decl.is_const     = 0;
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

    node->n_io.params = expression;

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

struct node* create_node_command_block(Node* first_command)
{
    struct node* node = new_node(NODE_TYPE_COMMAND_BLOCK);

    node->n_cmd_block.command = first_command;

    return node;
}
