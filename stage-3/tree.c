#include "tree.h"

#include <stdlib.h>
#include <stdio.h>

/**
 * Creates a new node structure and allocates the nedded memory
 *
 * @param token Operation Identifier
 */
Node* new_node(Lexeme* lexeme)
{
    Node* node = (Node*) malloc(sizeof(Node));

    node->lexeme = lexeme;
    node->children_count = 0;
    node->children = (Node**) malloc(sizeof(Node**));

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
    // TODO
}

/**
 * Frees memory previously allocated to the AST structure
 *
 * @param root AST Pointer
 */
void free_tree(Node* root)
{
    if(root != 0) // NULL
    {
        if(root->lexeme != 0)
        {
            free(root->lexeme);
        }

        for(int i = 0; i < root->children_count; i++)
        {
            Node* child = *(root->children + i);

            if(child != 0) {
                free_tree(child);
            }
        }

        free(root->children);
        free(root);
    }
}
