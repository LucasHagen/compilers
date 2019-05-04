#include "printer.h"

#include <stdio.h>
#include <stdlib.h>

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
        //print_node(node->n_var_decl.size);
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

    // TODO: print param

    printf(") {\n");

    // TODO: print body

    printf("}\n");
}
