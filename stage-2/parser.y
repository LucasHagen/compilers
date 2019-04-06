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
command: c_declare_variable | c_attr;

c_declare_variable: static const type TK_IDENTIFICADOR c_declare_variable_attr;
c_declare_variable_attr: %empty | TK_OC_LE c_declare_attr_value;
c_declare_attr_value: literal | TK_IDENTIFICADOR;

c_attr: TK_IDENTIFICADOR c_attr_vector_access '=' expression;
c_attr_vector_access: %empty | '[' arithmetic_expression ']';


expression: arithmetic_expression | logic_expression;
arithmetic_expression: TK_LIT_INT | TK_LIT_FLOAT;
logic_expression: TK_LIT_FALSE | TK_LIT_TRUE;

%%
void yyerror (char const *s){
	fprintf(stderr,"ERROR: line %d\n", yylineno);
}
