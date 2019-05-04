#include "printer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_tree(Node* node)
{
    if(node->seq != NULL) {
        print_tree(node->seq);
    }
    switch(node->type)
    {
        case NODE_TYPE_VAR_DECL:
            print_global_var_decl(node);
            break;
        case NODE_TYPE_FUNC_DECL:
            print_func_decl(node);
            break;
    }
}

void print_global_var_decl(Node* node)
{
    printf("%s", node->n_var_decl.identifier->token_value.v_string);

    if(node->n_var_decl.size != NULL) {
        printf("[");
        print_node(node->n_var_decl.size);
        printf("]");
    }

    if(node->n_var_decl.is_static) {
        printf(" static");
    }

    printf(" %s;\n", node->n_var_decl.type->token_value.v_string);
}

void print_func_decl(Node* node)
{
    if(node->n_func_decl.is_static) {
        printf("static ");
    }
    printf("%s %s(", node->n_func_decl.type->token_value.v_string,
        node->n_func_decl.identifier->token_value.v_string);

    print_func_decl_param(node->n_func_decl.param);
    printf(") {\n");
    print_node(node->n_func_decl.code);
    printf("}\n");
}

void print_func_decl_param(Node* node)
{
    if(node != NULL) {
        if(node->seq != NULL) {
            print_func_decl_param(node->seq);
            printf(", ");
        }
        if(node->n_var_decl.is_const) {
            printf("const ");
        }
        printf("%s %s",
            node->n_var_decl.type->token_value.v_string,
            node->n_var_decl.identifier->token_value.v_string);
    }
}

void print_node(Node* node) {
    if(node == NULL)
        return;

    if(node->seq != NULL) {
        print_node(node->seq);
    }

    switch(node->type) {
        case NODE_TYPE_LITERAL:
            print_lexeme(node->n_literal.literal);
            break;
        case NODE_TYPE_BIN_OP:
            print_bin_op(node);
            break;
        case NODE_TYPE_UN_OP:
            print_un_op(node);
            break;
        case NODE_TYPE_BREAK:
            printf("break;\n");
            break;
        case NODE_TYPE_CONTINUE:
            printf("continue;\n");
            break;
        case NODE_TYPE_RETURN:
            print_return(node);
    }

}

void print_return(Node* node) {
    printf("return ");
    print_node(node->n_io.params);
    printf(";\n");
}

void print_bin_op(Node* node) {
    printf("(");
    print_node(node->n_bin_op.left);
    printf(" ");
    print_lexeme(node->n_bin_op.op);
    printf(" ");
    print_node(node->n_bin_op.right);
    printf(")");
}

void print_un_op(Node* node) {
    print_lexeme(node->n_un_op.op);
    print_node(node->n_un_op.operand);
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
            printf("%c", lex->token_value.v_char);
        }
        else
        {
            switch(lex->literal_type)
            {
                case INT:
                    printf("%d", lex->token_value.v_int);
                    break;
                case FLOAT:
                    printf("%f", lex->token_value.v_float);
                    break;
                case BOOL:
                    printf("%s", lex->token_value.v_bool ? "true" : "false");
                    break;
                case CHAR:
                    printf("\'");
                    print_char(lex->token_value.v_char);
                    printf("\'");
                    break;
                case STRING:
                    print_string(lex->token_value.v_string);
                    break;
                default:
                    printf("%s",lex->token_value.v_string);
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
