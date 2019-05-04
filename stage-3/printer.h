#ifndef PRINTER_H
#define PRINTER_H

#ifndef NULL
#define NULL 0
#endif  // NULL

#include "lexeme.h"
#include "tree.h"

void print_tree(Node* node);

void print_global_var_decl(Node* node);
void print_func_decl(Node* node);

#endif
