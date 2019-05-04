#ifndef TREE_H
#define TREE_H

#include "lexeme.h"

#define NODE_TYPE_TER_OP 		0
#define NODE_TYPE_BIN_OP		1
#define NODE_TYPE_UN_OP			2
#define NODE_TYPE_IF			3
#define NODE_TYPE_FOR			4
#define NODE_TYPE_WHILE			5
#define NODE_TYPE_FUNC_CALL		6
#define NODE_TYPE_FUNC_DECL		7
#define NODE_TYPE_VAR_ACCESS	8
#define NODE_TYPE_VAR_DECL		9
#define NODE_TYPE_VAR_ATTR		10
#define NODE_TYPE_INPUT			11
#define NODE_TYPE_OUTPUT		12
#define NODE_TYPE_SHIFT_LEFT	13
#define NODE_TYPE_SHIFT_RIGHT	14
#define NODE_TYPE_RETURN		15
#define NODE_TYPE_BREAK			16
#define NODE_TYPE_CONTINUE		17
#define NODE_TYPE_LITERAL		18
#define NODE_TYPE_FUNC_PARAM    19

#define LITERAL_TYPE_INT		101
#define LITERAL_TYPE_FLOAT		102
#define LITERAL_TYPE_CHAR		103
#define LITERAL_TYPE_BOOL		104
#define LITERAL_TYPE_STRING		105

#define OP_PLUS 				200
#define OP_MINUS				201
#define OP_MULT					202
#define OP_DIV					203
#define OP_R_DIV				204
#define OP_BIT_OR				205
#define OP_BIT_AND				206
#define OP_EXP					207
#define OP_GREATER				208
#define OP_LESS					209
#define OP_LE					210
#define OP_GE					211
#define OP_EQ					212
#define OP_NE					213
#define OP_AND					214
#define OP_OR					215
#define OP_EXCLAMATION			216
#define OP_HASHTAG				217
#define OP_QUESTION				218

struct node_if {
	struct node* condition;
	struct node* n_true;
	struct node* n_false;
};

struct node_bin_op {
	struct lexeme* op;
	struct node*   left;
	struct node*   right;
};

struct node_un_op {
	struct lexeme* op;
	struct node*   operand;
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
	struct lexeme* type;
	int 		   is_static;
};


struct node_var_decl {
	struct lexeme* identifier;
	struct node*   size;
	struct lexeme* type;
	int 		   is_static;
	int 		   is_const;
	struct node*   value;
};

struct node_var_attr {
	struct node* identifier;
	struct node* value;
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

typedef struct node {
	int			  type;
	struct node*  seq;

	union {
		struct node_if				n_if;
		struct node_bin_op			n_bin_op;
		struct node_un_op			n_un_op;
		struct node_for				n_for;
		struct node_while			n_while;
		struct node_call_access		n_call_or_access;
		struct node_func_decl		n_func_decl;
		struct node_var_decl		n_var_decl;
		struct node_var_attr		n_var_attr;
		struct node_io				n_io;
		struct node_shift			n_shift;
		struct node_literal			n_literal;
	};
} Node;

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

struct node* create_node_ter_op(Node* condition, Node* ifTrue, Node* ifFalse);
struct node* create_node_bin_op(Lexeme* op, Node* left, Node* right);
struct node* create_node_un_op(Lexeme* op, Node* operand);
struct node* create_node_if(Node* condition, Node* ifTrue, Node* ifFalse);
struct node* create_node_for(Node* setup, Node* condition, Node* increment, Node* code);
struct node* create_node_while(Node* condition, Node* code);
struct node* create_node_func_call(Lexeme* identifier, Node* parameters);
struct node* create_node_func_decl(Lexeme* identifier, Lexeme* type, int is_static, Node* parameters, Node* code);
struct node* create_node_func_param(Lexeme* identifier, Lexeme* type, int is_const);
struct node* create_node_var_access(Lexeme* identifier, Node* index);
struct node* create_node_var_decl(Node* identifier, Lexeme* type, int is_static, int is_const, Node* value);
struct node* create_node_var_attr(Node* identifier, Node* value);
struct node* create_node_input(Node* input);
struct node* create_node_output(Node* output);
struct node* create_node_shift_left();
struct node* create_node_shift_right();
struct node* create_node_return(Node* expression);
struct node* create_node_break();
struct node* create_node_continue();
struct node* create_node_literal(Lexeme* value);




#endif // TREE_H
