#ifndef PRINTER_H
#define PRINTER_H

/*
	Authors:
		- Gabriel Pakulski da Silva - 00274701
		- Lucas Sonntag Hagen       - 00274698
*/

#ifndef NULL
#define NULL 0
#endif  // NULL

#include "lexeme.h"
#include "tree.h"

void print_tree(Node* node);
void print_node(Node* node, char* separator);
void print_ter_op(Node* node);
void print_bin_op(Node* node);
void print_un_op(Node* node);
void print_io(char* cmd, Node* node);
void print_shift(char* direction, Node* node);
void print_var_access(Node* node);
void print_var_attr(Node* node);
void print_var_decl(Node* node);
void print_func_call(Node* node);
void print_if(Node* node);
void print_while(Node* node);
void print_for(Node* node);
void print_block(Node* node);

void print_global_var_decl(Node* node);
void print_func_decl(Node* node);
void print_func_decl_param(Node* node);

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

#endif
