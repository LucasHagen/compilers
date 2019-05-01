#ifndef TREE_H
#define TREE_H

#include "lexeme.h"

#define NODE_TYPE_TER_OP
#define NODE_TYPE_BIN_OP
#define NODE_TYPE_UN_OP
#define NODE_TYPE_IF
#define NODE_TYPE_FOR
#define NODE_TYPE_WHILE
#define NODE_TYPE_FUNC_CALL
#define NODE_TYPE_FUNC_DECL
#define NODE_TYPE_VAR_ACCESS
#define NODE_TYPE_VAR_DECL
#define NODE_TYPE_VAR_ATTR
#define NODE_TYPE_INPUT
#define NODE_TYPE_OUTPUT
#define NODE_TYPE_SHIFT_LEFT
#define NODE_TYPE_SHIFT_RIGHT
#define NODE_TYPE_RETURN
#define NODE_TYPE_BREAK
#define NODE_TYPE_CONTINUE
#define NODE_TYPE_LITERAL

#define LITERAL_TYPE_INT;
#define LITERAL_TYPE_FLOAT;
#define LITERAL_TYPE_CHAR
#define LITERAL_TYPE_BOOL;
#define LITERAL_TYPE_STRING;

typedef struct node {
	int			  type;
	struct node*  seq;

	union {
		struct node_if*				n_if;
		struct node_bin_op*			n_bin_op;
		struct node_un_op*			n_un_op;
		struct node_for*			n_for;
		struct node_while*			n_while;
		struct node_call_access*	n_call_or_access;
		struct node_func_decl*		n_func_decl;
		struct node_var_decl*		n_var_decl;
		struct node_var_attr*		n_var_attr;
		struct node_io*				n_io;
		struct node_shift*			n_shift;
		struct node_literal*		n_literal;
	};
} Node;

struct node_if {
	struct node* condition;
	struct node* true_value;
	struct node* false_value;
};

struct node_bin_op {
	int 		 op;
	struct node* left;
	struct node* right;
};

struct node_un_op {
	int 		 op;
	struct node* operand;
};

struct node_for {
	struct node* setup;
	struct node* condition;
	struct node* increment;
	struct node* code;
};

struct node_while {
	struct node* condition;
	struct node* code;
};

struct node_call_access {
	struct lexeme* identifier;
	struct node*   index_or_param;
};

struct node_func_decl {
	struct lexeme* identifier;
	struct node*   param;
	struct node*   code;
	int 		   type;
	int 		   is_static;
};

struct node_var_decl {
	struct lexeme* identifier;
	struct node*   size;
	int 		   type;
	int 		   is_static;
	int 		   is_const;
	struct node*   value;
};

struct node_var_attr {
	struct lexeme* identifier;
	struct node*   index;
	struct node*   value;
};

struct node_io {
	struct node* params;
};

struct node_shift {
	struct node* var;
	struct node* count;
};

struct node_literal {
	struct lexeme* literal;
};

/**
 * Creates a new node structure and allocates the nedded memory
 *
 * @param lexeme Main Lexeme
 */
Node* new_node(int type);

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

/**
 * Prints a char value
 * If it is a scaped character, a string will be printed.
 *
 * @param char v_char
 */
void print_char (char v_char);

/**
 * Prints a string considering the scaped characters
 * In case of ocurrance, the corresponding string will be printed
 *
 * @param char* v_string
 */
void print_string(char* v_string);

//  ===== CREATE SPECIFIC NODES FOR EACH THING =====

void create_node_ter_op(Node* condition, Node* ifTrue, Node* ifFalse);

void create_node_bin_op(int op, Node* left, Node* right);

void create_node_un_op(int op, Node* operand);

void crete_node_if(Node* condition, Node* ifTrue, Node* ifFalse);

void create_node_for(Node* setup, Node* condition, Node* increment, Node* code);

void create_node_while(Node* condition, Node* code);

void create_node_func_call(Lexeme* identifier, Node* parameters);

void create_node_func_decl(Lexeme* identifier, int type, int is_static, Node* parameters, Node* code);

void create_node_func_param(Lexeme* identifier, int type, int is_const);

void create_node_var_access(Lexeme* identifier, Node* index);

void create_node_var_decl(Node* identifier, int type, int is_static, int is_const, Node* value);

void create_node_var_attr(Lexeme* identifier, int index, Node* value);

void create_node_input(Node* input);

void create_node_output(Node* output);

void create_node_shift_left();

void create_node_shift_right();

void create_node_return(Node* expression);

void create_node_break();

void create_node_continue();

void create_node_literal(Lexeme* value);




#endif // TREE_H
