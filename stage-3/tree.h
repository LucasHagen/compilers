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
 * @param lexeme Main Lexeme
 */
Node* new_node(Lexeme* lexeme);

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
void decompile(Node* root);

/**
 * Frees memory previously allocated to the AST structure
 *
 * @param arvore AST Pointer
 */
void free_tree(Node* root);

/**
 * Frees memory allocated for a Lexeme
 *
 * @param lex Lexeme Pointer
 * @return Allways 0, to override old pointer
 */
int free_lexeme(Lexeme* lex);

/**
 * Prints a Lexeme's value
 *
 * @param lex Lexeme
 */
void print_lexeme(Lexeme* lex);

#endif // TREE_H
