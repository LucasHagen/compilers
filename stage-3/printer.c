#include "printer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_tree(Node* node)
{
    print_node(node, NULL);
}

void print_node(Node* node, char* separator) {
    if(node == NULL)
        return;

    if(node->seq != NULL) {
        print_node(node->seq, separator);

        if(separator != NULL) {
            printf("%s", separator);
        }
    }

    switch(node->type) {
        case NODE_TYPE_LITERAL:
            print_lexeme(node->n_literal.literal);
            break;
        case NODE_TYPE_TER_OP:
            print_ter_op(node);
            break;
        case NODE_TYPE_BIN_OP:
            print_bin_op(node);
            break;
        case NODE_TYPE_UN_OP:
            print_un_op(node);
            break;
        case NODE_TYPE_BREAK:
            printf("break");
            break;
        case NODE_TYPE_CONTINUE:
            printf("continue");
            break;
        case NODE_TYPE_RETURN:
            print_io("return", node);
            break;
        case NODE_TYPE_INPUT:
            print_io("input", node);
            break;
        case NODE_TYPE_OUTPUT:
            print_io("output", node);
            break;
        case NODE_TYPE_VAR_ACCESS:
            print_var_access(node);
            break;
        case NODE_TYPE_GLOBAL_VAR_DECL:
            print_global_var_decl(node);
            break;
        case NODE_TYPE_FUNC_DECL:
            print_func_decl(node);
            break;
        case NODE_TYPE_SHIFT_LEFT:
            print_shift("<<", node);
            break;
        case NODE_TYPE_SHIFT_RIGHT:
            print_shift(">>", node);
            break;
        case NODE_TYPE_VAR_ATTR:
            print_var_attr(node);
            break;
        case NODE_TYPE_VAR_DECL:
            print_var_decl(node);
            break;
        case NODE_TYPE_FUNC_CALL:
            print_func_call(node);
            break;
        case NODE_TYPE_IF:
            print_if(node);
            break;
        case NODE_TYPE_WHILE:
            print_while(node);
            break;
        case NODE_TYPE_FOR:
            print_for(node);
            break;
        case NODE_TYPE_COMMAND_BLOCK:
            print_block(node);
            break;
    }
}

void print_block(Node* node) {
    printf("{\n");
    if(node->n_cmd_block.command != NULL) {
        print_node(node->n_cmd_block.command, ";\n");
    }
    printf(";\n}");
}

void print_for(Node* node) {
    printf("for (");
    print_node(node->n_for.setup, ", ");
    printf(" : ");
    print_node(node->n_for.condition, NULL);
    printf(" : ");
    print_node(node->n_for.increment, ", ");
    printf(") ");
    print_node(node->n_for.code, NULL);
}

void print_while(Node* node) {
    printf("while (");
    print_node(node->n_while.condition, NULL);
    printf(") do ");
    print_node(node->n_while.code, NULL);
}

// if ( x ) then b else b
void print_if(Node* node) {
    printf("if (");
    print_node(node->n_if.condition, NULL);
    printf(") then ");
    print_node(node->n_if.n_true, NULL);
    if(node->n_if.n_false != NULL) {
        printf(" else ");
        print_node(node->n_if.n_false, NULL);
    }
}

void print_func_call(Node* node) {
    print_lexeme(node->n_call_or_access.identifier);
    printf("(");
    if(node->n_call_or_access.index_or_param != NULL) {
        print_node(node->n_call_or_access.index_or_param, ", ");
    }
    printf(")");
}

void print_var_decl(Node* node) {
    if(node->n_var_decl.is_static) {
        printf("static ");
    }
    if(node->n_var_decl.is_const) {
        printf("const ");
    }
    print_lexeme(node->n_var_decl.type);
    printf(" ");
    print_lexeme(node->n_var_decl.identifier);

    if(node->n_var_decl.value != NULL) {
        printf(" <= ");
        print_node(node->n_var_decl.value, NULL);
    }
}

void print_var_attr(Node* node) {
    print_lexeme(node->n_var_attr.identifier);
    if(node->n_var_attr.index != NULL) {
        printf("[");
        print_node(node->n_var_attr.index, NULL);
        printf("]");
    }
    printf(" = ");
    print_node(node->n_var_attr.value, NULL);
}

void print_shift(char* direction, Node* node) {
    print_node(node->n_shift.var, NULL);
    printf(" %s ", direction);
    print_node(node->n_shift.count, NULL);
}

void print_global_var_decl(Node* node)
{
    printf("%s", node->n_var_decl.identifier->token_value.v_string);

    if(node->n_var_decl.size != NULL) {
        printf("[");
        print_node(node->n_var_decl.size, NULL);
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
    printf(") ");
    print_node(node->n_func_decl.code, NULL);
    printf("\n");
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

void print_var_access(Node* node) {
    print_lexeme(node->n_call_or_access.identifier);
    if(node->n_call_or_access.index_or_param != NULL) {
        printf("[");
        print_node(node->n_call_or_access.index_or_param, NULL);
        printf("]");
    }
}

void print_io(char* cmd, Node* node) {
    printf("%s ", cmd);
    print_node(node->n_io.params, ", ");
}


void print_bin_op(Node* node) {
    printf("(");
    print_node(node->n_bin_op.left, NULL);
    printf(" ");
    print_lexeme(node->n_bin_op.op);
    printf(" ");
    print_node(node->n_bin_op.right, NULL);
    printf(")");
}

void print_ter_op(Node* node) {
    printf("((");
    print_node(node->n_if.condition, NULL);
    printf(") ? (");
    print_node(node->n_if.n_true, NULL);
    printf(") : (");
    print_node(node->n_if.n_false, NULL);
    printf("))");
}

void print_un_op(Node* node) {
    print_lexeme(node->n_un_op.op);
    print_node(node->n_un_op.operand, NULL);
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
