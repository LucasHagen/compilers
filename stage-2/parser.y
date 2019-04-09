%{
#include <stdio.h>

extern int yylineno;
/*
	Authors:
		- Gabriel Pakulski da Silva - 00274701
		- Lucas Sonntag Hagen       - 00274698
*/

int yylex(void);
void yyerror (char const *s);
%}

%token TK_PR_INT
%token TK_PR_FLOAT
%token TK_PR_BOOL
%token TK_PR_CHAR
%token TK_PR_STRING
%token TK_PR_IF
%token TK_PR_THEN
%token TK_PR_ELSE
%token TK_PR_WHILE
%token TK_PR_DO
%token TK_PR_INPUT
%token TK_PR_OUTPUT
%token TK_PR_RETURN
%token TK_PR_CONST
%token TK_PR_STATIC
%token TK_PR_FOREACH
%token TK_PR_FOR
%token TK_PR_SWITCH
%token TK_PR_CASE
%token TK_PR_BREAK
%token TK_PR_CONTINUE
%token TK_PR_CLASS
%token TK_PR_PRIVATE
%token TK_PR_PUBLIC
%token TK_PR_PROTECTED
%token TK_OC_LE
%token TK_OC_GE
%token TK_OC_EQ
%token TK_OC_NE
%token TK_OC_AND
%token TK_OC_OR
%token TK_OC_SL
%token TK_OC_SR
%token TK_OC_FORWARD_PIPE
%token TK_OC_BASH_PIPE
%token TK_LIT_INT
%token TK_LIT_FLOAT
%token TK_LIT_FALSE
%token TK_LIT_TRUE
%token TK_LIT_CHAR
%token TK_LIT_STRING
%token TK_IDENTIFICADOR
%token TOKEN_ERRO

%token EXCLAMATION
%token QUESTION
%token HASHTAG


%token MINUS
%token PLUS
%token MULT
%token DIV
%token R_DIV
%token BIT_OR
%token EXP
%token GREATER
%token LESS
%token LEFT_P
%token RIGHT_P

%precedence TK_PR_THEN
%precedence TK_PR_ELSE

%left TK_OC_EQ TK_OC_NE
%left TK_OC_GE TK_OC_LE GREATER LESS
%left TK_OC_SR TK_OC_SL
%left PLUS MINUS
%left MULT DIV R_DIV
%left EXP
%left QUESTION
%right POINTER ADDRESS EXCLAMATION UPLUS UMINUS HASHTAG
%start programa

%%

programa: global_var_list function_list;

literal: TK_LIT_TRUE | TK_LIT_FALSE | TK_LIT_STRING | TK_LIT_CHAR | TK_LIT_INT | TK_LIT_FLOAT;

type: TK_PR_INT | TK_PR_FLOAT | TK_PR_CHAR | TK_PR_BOOL | TK_PR_STRING;
var: vector static type | TK_IDENTIFICADOR static type;
vector: TK_IDENTIFICADOR '[' arithmetic_expression ']';
static: TK_PR_STATIC | %empty;
const: TK_PR_CONST | %empty;

global_var: var ';';
global_var_list: global_var_list global_var | %empty;

function_list: function_list function | %empty;
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
commands_list: %empty | commands_list command ';' ;
command: commands_block | c_declare_variable | c_attr |
		c_input | c_output | c_call_func | c_shift |
		c_return | c_continue | c_break |
		c_if | c_for | c_while;

c_declare_variable: static const type TK_IDENTIFICADOR c_declare_variable_attr;
c_declare_variable_attr: %empty | TK_OC_LE c_declare_attr_value;
c_declare_attr_value: literal | TK_IDENTIFICADOR;

c_attr: TK_IDENTIFICADOR vector_access '=' expression;
vector_access: %empty | '[' arithmetic_expression ']';

c_input: TK_PR_INPUT expression;

c_output: TK_PR_OUTPUT c_output_exp_list;
c_output_exp_list: expression | c_output_exp_list ',' expression;

c_call_func: TK_IDENTIFICADOR '(' c_call_parameters ')';
c_call_parameters: %empty | c_call_list_exp;
c_call_list_exp: expression | c_call_list_exp ',' expression;

c_shift: TK_IDENTIFICADOR vector_access c_shift_symbol arithmetic_expression;
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

expression_list: expression ';' expression_list | %empty;
expression: arithmetic_expression | logic_expression | identifier | '(' expression ')';
arithmetic_expression: 	operator bin_op operator | un_op operator | operator question_op;
logic_expression: TK_LIT_FALSE | TK_LIT_TRUE;

operator: identifier | num_lit | c_call_func;
identifier: TK_IDENTIFICADOR | TK_IDENTIFICADOR '[' TK_LIT_INT ']';
num_lit: TK_LIT_INT | TK_LIT_FLOAT;

left_parenthesis: LEFT_P;
right_parenthesis: RIGHT_P;

un_op: PLUS %prec UPLUS | MINUS %prec UMINUS | EXCLAMATION | '&' %prec ADDRESS |
 			 MULT %prec POINTER | HASHTAG;
question_op: QUESTION;
bin_op: PLUS | MINUS | MULT | DIV |
 				R_DIV | BIT_OR | '&' | EXP |
				GREATER | LESS |
				TK_OC_LE |
				TK_OC_GE |
				TK_OC_EQ |
				TK_OC_NE |
				TK_OC_AND|
				TK_OC_OR;

ter_op: expression '?' expression ':' expression;


%%
void yyerror (char const *s){
	fprintf(stderr,"Error in line %d: '%s'\n", yylineno, s);
}
