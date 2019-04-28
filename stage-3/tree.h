#ifndef TREE_H
#define TREE_H

#include "lexeme.h"

typedef struct node {
	Lexeme*       lexeme;
	int 		  children_count;
	struct node** children;
} Node;

/**
 * Creates a new node structure and allocates the nedded memory
 *
 * @param token Operation Identifier
 */
Node* new_node(Lexeme* llexeme);

/**
 * Adds a new child to a existing node
 *
 * @param node Pointer to the parent node
 * @param child Pointer to the child node
 */
void add_child(Node* node, Node* child);

/**
 * Generates a source code based on a Abstract Syntax Tree (AST)
 *
 * @param arvore AST Pointer
 */
void decompile (void *root);

/**
 * Frees memory previously allocated to the AST structure
 *
 * @param arvore AST Pointer
 */
void free_tree (void *root);


#endif // TREE_H
