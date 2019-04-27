%{

#include <stdio.h>
#include "lexeme.h"
#include "tree.h"

/*
	Authors:
		- Gabriel Pakulski da Silva - 00274701
		- Lucas Sonntag Hagen       - 00274698
*/

extern int yylineno;
extern void* arvore;

int yylex(void);
void yyerror (char const *s);

%}

%union {
	struct lexeme* lex_value;
	struct node* node;
}

%define parse.error verbose

%token <lex_value> TK_PR_INT
%token <lex_value> TK_PR_FLOAT
%token <lex_value> TK_PR_BOOL
%token <lex_value> TK_PR_CHAR
%token <lex_value> TK_PR_STRING
%token <lex_value> TK_PR_IF
%token <lex_value> TK_PR_THEN
%token <lex_value> TK_PR_ELSE
%token <lex_value> TK_PR_WHILE
%token <lex_value> TK_PR_DO
%token <lex_value> TK_PR_INPUT
%token <lex_value> TK_PR_OUTPUT
%token <lex_value> TK_PR_RETURN
%token <lex_value> TK_PR_CONST
%token <lex_value> TK_PR_STATIC
%token <lex_value> TK_PR_FOREACH
%token <lex_value> TK_PR_FOR
%token <lex_value> TK_PR_SWITCH
%token <lex_value> TK_PR_CASE
%token <lex_value> TK_PR_BREAK
%token <lex_value> TK_PR_CONTINUE
%token <lex_value> TK_PR_CLASS
%token <lex_value> TK_PR_PRIVATE
%token <lex_value> TK_PR_PUBLIC
%token <lex_value> TK_PR_PROTECTED
%token <lex_value> TK_OC_LE
%token <lex_value> TK_OC_GE
%token <lex_value> TK_OC_EQ
%token <lex_value> TK_OC_NE
%token <lex_value> TK_OC_AND
%token <lex_value> TK_OC_OR
%token <lex_value> TK_OC_SL
%token <lex_value> TK_OC_SR
%token <lex_value> TK_OC_FORWARD_PIPE
%token <lex_value> TK_OC_BASH_PIPE
%token <lex_value> TK_LIT_INT
%token <lex_value> TK_LIT_FLOAT
%token <lex_value> TK_LIT_FALSE
%token <lex_value> TK_LIT_TRUE
%token <lex_value> TK_LIT_CHAR
%token <lex_value> TK_LIT_STRING
%token <lex_value> TK_IDENTIFICADOR
%token TOKEN_ERRO

%token <valor_lexico> EXCLAMATION
%token <valor_lexico> QUESTION
%token <valor_lexico> HASHTAG


%token <valor_lexico> MINUS
%token <valor_lexico> PLUS
%token <valor_lexico> MULT
%token <valor_lexico> DIV
%token <valor_lexico> R_DIV
%token <valor_lexico> BIT_OR
%token <valor_lexico> EXP
%token <valor_lexico> GREATER
%token <valor_lexico> LESS

%left ','
%right '?'
%left TK_OC_OR
%left TK_OC_AND
%left '|'
%left '&'
%left TK_OC_EQ TK_OC_NE
%left TK_OC_GE TK_OC_LE '>' '<'
%left TK_OC_SR TK_OC_SL
%left '+' '-'
%left '*' '/' '%'
%left '^'
%right POINTER ADDRESS '!' UPLUS UMINUS '#'
%left PARENTHESIS
%start programa

%%

programa:  big_list;
big_list: global_var big_list | function big_list | %empty;
literal: TK_LIT_TRUE | TK_LIT_FALSE | TK_LIT_STRING | TK_LIT_CHAR | TK_LIT_INT | TK_LIT_FLOAT;

type: TK_PR_INT | TK_PR_FLOAT | TK_PR_CHAR | TK_PR_BOOL | TK_PR_STRING;
var: vector static type | TK_IDENTIFICADOR static type;
vector: TK_IDENTIFICADOR '[' expression ']';
static: TK_PR_STATIC | %empty;
const: TK_PR_CONST | %empty;
global_var: var ';';

function: header body;
header: function_type function_name '(' function_parameters ')';
function_type: static type;
function_name: TK_IDENTIFICADOR;
function_parameters: %empty | parameters_list;
parameters_list: parameters_list ',' parameter | parameter;
parameter: parameter_type TK_IDENTIFICADOR;
parameter_type: type | TK_PR_CONST type;
body: commands_block;

commands_block: '{' commands_list '}';
commands_list: %empty | commands_list command ';';
command: commands_block | c_declare_variable | c_attr |
		c_input | c_output | c_call_func | c_shift |
		c_return | c_continue | c_break |
		c_for | c_if | c_while;

c_declare_variable: static const type TK_IDENTIFICADOR c_declare_variable_attr;
c_declare_variable_attr: %empty | TK_OC_LE c_declare_attr_value;
c_declare_attr_value: literal | TK_IDENTIFICADOR;

c_attr: TK_IDENTIFICADOR vector_access '=' expression;
vector_access: %empty | '[' expression ']';

c_input: TK_PR_INPUT expression;

c_output: TK_PR_OUTPUT c_output_exp_list;
c_output_exp_list: expression | c_output_exp_list ',' expression;

c_call_func: TK_IDENTIFICADOR '(' c_call_parameters ')';
c_call_parameters: %empty | c_call_list_exp;
c_call_list_exp: expression | c_call_list_exp ',' expression;

c_shift: TK_IDENTIFICADOR vector_access c_shift_symbol expression;
c_shift_symbol: TK_OC_SR | TK_OC_SL;

c_return: TK_PR_RETURN expression;

c_continue: TK_PR_CONTINUE;

c_break: TK_PR_BREAK;

c_if: TK_PR_IF '(' expression ')' TK_PR_THEN commands_block c_else;
c_else: %empty | TK_PR_ELSE commands_block;

c_for: TK_PR_FOR '(' c_for_command_list ':' expression ':' c_for_command_list ')' commands_block;
c_for_command_list: c_for_no_comma | c_for_command_list ',' c_for_no_comma;
c_for_no_comma: c_declare_variable | c_attr |
		c_input | c_shift | c_return | c_continue | c_break |
		c_if | c_while;

c_while: TK_PR_WHILE '(' expression ')' TK_PR_DO commands_block;



expression: un_op simple_expression optional_expression | simple_expression optional_expression;

simple_expression: operand | '(' expression ')' %prec PARENTHESIS;
optional_expression: bin_op expression | '?' expression ':' expression | %empty;

operand: identifier | lit | c_call_func;

identifier: TK_IDENTIFICADOR | TK_IDENTIFICADOR '[' expression ']';

lit: num_lit | char_lit | boolean;
num_lit: TK_LIT_INT | TK_LIT_FLOAT;
char_lit: TK_LIT_CHAR | TK_LIT_STRING;
boolean: TK_LIT_TRUE | TK_LIT_FALSE;

un_op: '+' %prec UPLUS | '-' %prec UMINUS | '!' | '&' %prec ADDRESS |
 			 '*' %prec POINTER | '#' | '?';

bin_op: '+' | '-' | '*' | '/' |
 				'%' | '|' | '&' %prec '&'| '^' |
				'>' | '<' |
				TK_OC_LE |
				TK_OC_GE |
				TK_OC_EQ |
				TK_OC_NE |
				TK_OC_AND|
				TK_OC_OR;

%%

/**
 * Prints a error, when it occurs
 *
 * @param s String to the error message
 */
void yyerror (char const *s){
	fprintf(stderr,"[ERROR] %s in line %d;\n", s, yylineno);
}

/**
 * Generates a source code based on a Abstract Syntax Tree (AST)
 *
 * @param arvore AST Pointer
 */
void descompila (void *arvore) {
	// TODO
}

/**
 * Frees memory previously allocated to the AST structure
 *
 * @param arvore AST Pointer
 */
void libera (void *arvore) {
	// TODO
}
