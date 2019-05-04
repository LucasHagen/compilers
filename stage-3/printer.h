#ifndef PRINTER_H
#define PRINTER_H

#ifndef NULL
#define NULL 0
#endif  // NULL

#include "lexeme.h"
#include "tree.h"

void print_tree(Node* node);
void print_node(Node* node);
void print_bin_op(Node* node);
void print_un_op(Node* node);
void print_return(Node* node);

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
