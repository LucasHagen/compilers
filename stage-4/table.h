#ifndef TABLE_H
#define TABLE_H

#include "lexeme.h"
#include "nature.h"
#include "size.h"

/*
	Authors:
		- Gabriel Pakulski da Silva - 00274701
		- Lucas Sonntag Hagen       - 00274698
*/

typedef struct line {
  char* id;
  int declaration_line;
  int nature;
  int token_type;
  int token_size;
  int is_static;
  int is_const;
  //function_args* function_args;
  //int num_function_args;
  Lexeme* lexeme;
} ST_LINE;
