#ifndef LEXEME_H
#define LEXEME_H

#include "defines.h"
#include "iloc.h"
/*
	Authors:
		- Gabriel Pakulski da Silva - 00274701
		- Lucas Sonntag Hagen       - 00274698
*/

/*
TOKENS
Os tokens se enquadram em diferentes categorias:
  1) palavras reservadas da linguagem
  2) caracteres especiais
  3) operadores compostos
  4) identificadores
  5) literais.
*/
#define KEYWORD       1000
#define SPECIAL_CHAR  1001
#define OPERATOR      1002
#define IDENTIFIER    1003
#define LITERAL       1004

/*
TIPOS DOS LITERAIS
  1)INT
  2)FLOAT
  3)BOOL
  4)CHAR
  5)STRING
*/
#define INT     1005
#define FLOAT   1006
#define BOOL    1007
#define CHAR    1008
#define STRING  1009
#define NO_TYPE -1

#define TRUE 1
#define FALSE 0

#define NOT_LITERAL 1010

union literal_value {
    int v_int;
    float v_float;
    int v_bool;
    char v_char;
    char* v_string;
};

/*
  O  tipo do valor_lexico (e por consequência o valor que será retido) deve
  ser uma estrutura de dados que contém os seguintes campos:

    número da linha (e coluna, caso exista) onde apareceu o lexema
    tipo do token (um dentre as cinco categorias definidas na E1)
    valor do token
*/
typedef struct lexeme {
    int line_number;
    int token_type;
    int literal_type; //caso seja não literal, recebe o valor NOT_LITERAL
    union literal_value token_value;
} Lexeme;

typedef struct fuction_argument{
  int type;
  char* identifier;
  int is_const;
} function_arg;

typedef struct stack_frame {
    int dynamic_link;
    int static_link;
    int local_variables_size;
    function_arg* function_args;
    int return_value;
    int return_address;
    char machine_state[MACHINE_STATE_SIZE]; //1 byte x Machine State Size
    int temporary; // not sure if its really necessary
} ST_FRAME;

typedef struct line {
    char* id;
    int declaration_line;
    int nature;
    int token_type;
    int token_size;
    int is_static;
    int is_const;
    int offset;
    Lexeme* lexeme;
    int num_function_args;
    function_arg* function_args;

    int local_variables_size;
    ST_FRAME* frame;
    ILOC* function_label;
} ST_LINE;


#endif
