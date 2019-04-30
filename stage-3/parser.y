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

%token <lex_value> ','
%token <lex_value> ';'
%token <lex_value> ':'
%token <lex_value> '('
%token <lex_value> ')'
%token <lex_value> '['
%token <lex_value> ']'
%token <lex_value> '{'
%token <lex_value> '}'
%token <lex_value> '='
%token <lex_value> '&'
%token <lex_value> '$'
%token <lex_value> '.'
%token <lex_value> PLUS
%token <lex_value> MINUS
%token <lex_value> BIT_OR
%token <lex_value> QUESTION
%token <lex_value> MULT
%token <lex_value> DIV
%token <lex_value> LESS
%token <lex_value> GREATER
%token <lex_value> EXCLAMATION
%token <lex_value> R_DIV
%token <lex_value> HASHTAG
%token <lex_value> EXP

%left ','
%right QUESTION
%left TK_OC_OR
%left TK_OC_AND
%left BIT_OR
%left '&'
%left TK_OC_EQ TK_OC_NE
%left TK_OC_GE TK_OC_LE GREATER LESS
%left TK_OC_SR TK_OC_SL
%left PLUS MINUS
%left MULT DIV R_DIV
%left EXP
%right POINTER ADDRESS EXCLAMATION UPLUS UMINUS HASHTAG
%left PARENTHESIS

%type <node> literal
%type <node> type
%type <node> const
%type <node> var
%type <node> static
%type <node> global_var

%type <node> programa
%type <node> big_list
%type <node> function
%type <node> header
%type <node> function_parameters
%type <node> parameters_list
%type <node> parameter
%type <node> body
%type <node> commands_block
%type <node> commands_list
%type <node> command
%type <node> c_declare_variable
%type <node> c_declare_variable_attr
%type <node> c_declare_attr_value
%type <node> c_attr
%type <node> c_input
%type <node> c_output
%type <node> c_output_exp_list
%type <node> c_call_func
%type <node> c_call_parameters
%type <node> c_call_list_exp
%type <node> c_shift
%type <node> c_shift_symbol
%type <node> c_return
%type <node> c_continue
%type <node> c_break
%type <node> c_if
%type <node> c_else
%type <node> c_for
%type <node> c_for_command_list
%type <node> c_for_no_comma
%type <node> c_while
%type <node> expression
%type <node> simple_expression
%type <node> optional_expression
%type <node> operand
%type <node> identifier
%type <node> un_op
%type <node> bin_op

%start programa

%%

programa:
	big_list
	{
		$$ = $1;
		arvore = $$;
	};

big_list:
	big_list global_var
	{
		$$ = $1;
		add_child($$, $2);
	}|
	big_list function
	{
		$$ = $1;
		add_child($$, $2);
	}|
	function
	{
		$$ = $1;
	}|
	global_var
	{
		$$ = $1;
	};

literal:
	TK_LIT_TRUE
	{
		$$ = new_node($1);
	}|
	TK_LIT_FALSE
	{
		$$ = new_node($1);
	}|
	TK_LIT_STRING
	{
		$$ = new_node($1);
	}|
	TK_LIT_CHAR
	{
		$$ = new_node($1);
	}|
	TK_LIT_INT
	{
		$$ = new_node($1);
	}|
	TK_LIT_FLOAT
	{
		$$ = new_node($1);
	};

type:
	TK_PR_INT
	{
		$$ = new_node($1);
	}|
	TK_PR_FLOAT
	{
		$$ = new_node($1);
	}|
	TK_PR_CHAR
	{
		$$ = new_node($1);
	}|
	TK_PR_BOOL {
		$$ = new_node($1);
	}|
	TK_PR_STRING
	{
		$$ = new_node($1);
	};

global_var:
	var ';'
	{
		$$ = $1;
		add_child($$, new_node($2));
	};

var:
	identifier static type
	{
		$$ = $1;
		if($2 != NULL)
		{
			add_child($$, $2);
		}
		add_child($$, $3);
	};

static:
	TK_PR_STATIC
	{
		$$ = new_node($1);
	}|
	%empty
	{
		$$ = NULL;
	};

const:
	TK_PR_CONST
	{
		$$ = new_node($1);
	}|
	%empty
	{
		$$ = NULL;
	};

function:
	header body
	{
		$$ = $1;
		add_child($$, $2);
	};

header:
	static type TK_IDENTIFICADOR '(' function_parameters ')'
	{
		$$ = $1;

		if($$ == NULL) {
			$$ = $2;
		} else {
			add_child($$, $2);
		}

		add_child($$, new_node($3));
		add_child($$, new_node($4));
		add_child($$, $5);
		add_child($$, new_node($6));
	};

function_parameters:
	%empty
	{
		$$ = NULL;
	}|
	parameters_list
	{
		$$ = $1;
	};

parameters_list:
	parameters_list ',' parameter
	{
		$$ = $1;
		add_child($$, new_node($2));
		add_child($$, $3);
	}|
	parameter
	{
		$$ = $1;
	};

parameter:
	const type TK_IDENTIFICADOR
	{
		$$ = $1;

		if($$ == NULL) {
			$$ = $2;
		} else {
			add_child($$, $2);
		}

		add_child($$, new_node($3));
	};

body:
	commands_block
	{
		$$ = $1;
	};

commands_block:
	'{' commands_list '}'
	{
		$$ = new_node($1);
		add_child($$, $2);
		add_child($$, new_node($3));
	};

commands_list:
	%empty
	{
		$$ = NULL;
	}|
	command ';' commands_list
	{
		$$ = $1;
		add_child($$, new_node($2));
		add_child($$, $3);
	};

command:
	commands_block
	{
		$$ = $1;
	}|
	c_declare_variable
	{
		$$ = $1;
	}|
	c_attr
	{
		$$ = $1;
	}|
	c_input
	{
		$$ = $1;
	}|
	c_output
	{
		$$ = $1;
	}|
	c_call_func
	{
		$$ = $1;
	}|
	c_shift
	{
		$$ = $1;
	}|
	c_return
	{
		$$ = $1;
	}|
	c_continue
	{
		$$ = $1;
	}|
	c_break
	{
		$$ = $1;
	}|
	c_for
	{
		$$ = $1;
	}|
	c_if
	{
		$$ = $1;
	}|
	c_while
	{
		$$ = $1;
	};

c_declare_variable:
	static const type TK_IDENTIFICADOR c_declare_variable_attr
	{
		$$ = $1;

		if($$ == NULL) {
			$$ = $2;
		} else if($2 != NULL) {
			add_child($$, $2);
		}

		if($$ == NULL) {
			$$ = $3;
		} else {
			add_child($$, $3);
		}

		add_child($$, new_node($4));

		if($5 != NULL) {
			add_child($$, $5);
		}
	};

c_declare_variable_attr:
	%empty
	{
		$$ = NULL;
	}|
	TK_OC_LE c_declare_attr_value
	{
		$$ = new_node($1);
		add_child($$, $2);
	};

c_declare_attr_value:
	literal
	{
		$$ = $1;
	}|
	TK_IDENTIFICADOR
	{
		$$ = new_node($1);
	};

c_attr:
	identifier '=' expression
	{
		$$ = $1;
		add_child($$, new_node($2));
		add_child($$, $3);
	};

c_input:
	TK_PR_INPUT expression
	{
		$$ = new_node($1);
		add_child($$, $2);
	};

c_output:
	TK_PR_OUTPUT c_output_exp_list
	{
		$$ = new_node($1);
		add_child($$, $2);
	};

c_output_exp_list:
	expression
	{
		$$ = $1;
	}|
	c_output_exp_list ',' expression
	{
		$$ = $1;
		add_child($$, new_node($2));
		add_child($$, $3);
	};

c_call_func:
	TK_IDENTIFICADOR '(' c_call_parameters ')'
	{
		$$ = new_node($1);
		add_child($$, new_node($2));
		if($4 != NULL) {
			add_child($$, $3);
		}
		add_child($$, new_node($4));
	};

c_call_parameters:
	%empty
	{
		$$ = NULL;
	}|
	c_call_list_exp
	{
		$$ = $1;
	};

c_call_list_exp:
	expression
	{
		$$ = $1;
	}|
	c_call_list_exp ',' expression
	{
		$$ = $1;
		add_child($$, new_node($2));
		add_child($$, $3);
	};

c_shift:
	identifier c_shift_symbol expression
	{
		$$ = $1;
		add_child($$, $2);
		add_child($$, $3);
	};

c_shift_symbol:
	TK_OC_SR
	{
		$$ = new_node($1);
	}|
	TK_OC_SL
	{
		$$ = new_node($1);
	};

c_return:
	TK_PR_RETURN expression
	{
		$$ = new_node($1);
		add_child($$, $2);
	};

c_continue:
	TK_PR_CONTINUE
	{
		$$ = new_node($1);
	};

c_break:
	TK_PR_BREAK
	{
		$$ = new_node($1);
	};

c_if:
	TK_PR_IF '(' expression ')' TK_PR_THEN commands_block c_else
	{
		$$ = new_node($1);
		add_child($$, new_node($2));
		add_child($$, $3);
		add_child($$, new_node($4));
		add_child($$, new_node($5));
		add_child($$, $6);
		if($7 != NULL) {
			add_child($$, $7);
		}
	};

c_else:
	%empty
	{
		$$ = NULL;
	}|
	TK_PR_ELSE commands_block
	{
		$$ = new_node($1);
		add_child($$, $2);
	};

c_for:
	TK_PR_FOR '(' c_for_command_list ':' expression ':' c_for_command_list ')' commands_block
	{
		$$ = new_node($1);
		add_child($$, new_node($2));
		add_child($$, $3);
		add_child($$, new_node($4));
		add_child($$, $5);
		add_child($$, new_node($6));
		add_child($$, $7);
		add_child($$, new_node($8));
		add_child($$, $9);
	};


c_for_command_list:
 	c_for_no_comma
	{
		$$ = $1;
	}|
	c_for_command_list ',' c_for_no_comma
	{
		$$ = $1;
		add_child($$, new_node($2));
		add_child($$, $3);
	};

c_for_no_comma:
	c_declare_variable
	{
		$$ = $1;
	}|
	c_attr
	{
		$$ = $1;
	}|
	c_input
	{
		$$ = $1;
	}|
	c_shift
	{
		$$ = $1;
	}|
	c_return
	{
		$$ = $1;
	}|
	c_continue
	{
		$$ = $1;
	}|
	c_break
	{
		$$ = $1;
	}|
	c_if
	{
		$$ = $1;
	}|
	c_while
	{
		$$ = $1;
	};

c_while:
	TK_PR_WHILE '(' expression ')' TK_PR_DO commands_block
	{
		$$ = new_node($1);
		add_child($$, new_node($2));
		add_child($$, $3);
		add_child($$, new_node($4));
		add_child($$, new_node($5));
		add_child($$, $6);
	};

expression:
	un_op simple_expression optional_expression
	{
		$$ = $1;
		add_child($$, $2);

		if($3 != NULL) {
			add_child($$, $3);
		}
	}|
	simple_expression optional_expression
	{
		$$ = $1;

		if($2 != NULL) {
			add_child($$, $2);
		}
	};

simple_expression:
	operand
	{
		$$ = $1;
	}|
	'(' expression ')' %prec PARENTHESIS
	{
		$$ = new_node($1);
		add_child($$, $2);
		add_child($$, new_node($3));
	};

optional_expression:
	bin_op expression
	{
		$$ = $1;
		add_child($$, $2);
	}|
	QUESTION expression ':' expression
	{
		$$ = new_node($1);
		add_child($$, $2);
		add_child($$, new_node($3));
		add_child($$, $4);
	}|
	%empty
	{
		$$ = NULL;
	};

operand:
	identifier
	{
		$$ = $1;
	}|
	literal
	{
		$$ = $1;
	}|
	c_call_func
	{
		$$ = $1;
	};

identifier:
	TK_IDENTIFICADOR
	{
		$$ = new_node($1);
	}|
	TK_IDENTIFICADOR '[' expression ']'
	{
		$$ = new_node($1);
		add_child($$, new_node($2));
		add_child($$, $3);
		add_child($$, new_node($4));
	};

un_op:
	PLUS %prec UPLUS
	{
		$$ = new_node($1);
	}|
	MINUS %prec UMINUS
	{
		$$ = new_node($1);
	}|
	EXCLAMATION
	{
		$$ = new_node($1);
	}|
	'&' %prec ADDRESS
	{
		$$ = new_node($1);
	}|
 	MULT %prec POINTER
	{
		$$ = new_node($1);
	}|
	HASHTAG
	{
		$$ = new_node($1);
	}|
	QUESTION
	{
		$$ = new_node($1);
	};

bin_op:
	PLUS
	{
		$$ = new_node($1);
	}|
	MINUS
	{
		$$ = new_node($1);
	}|
	MULT
	{
		$$ = new_node($1);
	}|
	DIV
	{
		$$ = new_node($1);
	}|
	R_DIV
	{
		$$ = new_node($1);
	}|
	BIT_OR
	{
		$$ = new_node($1);
	}|
	'&' %prec '&'
	{
		$$ = new_node($1);
	}|
	EXP
	{
		$$ = new_node($1);
	}|
	GREATER
	{
		$$ = new_node($1);
	}|
	LESS
	{
		$$ = new_node($1);
	}|
	TK_OC_LE
	{
		$$ = new_node($1);
	}|
	TK_OC_GE
	{
		$$ = new_node($1);
	}|
	TK_OC_EQ
	{
		$$ = new_node($1);
	}|
	TK_OC_NE
	{
		$$ = new_node($1);
	}|
	TK_OC_AND
	{
		$$ = new_node($1);
	}|
	TK_OC_OR
	{
		$$ = new_node($1);
	};

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
	decompile((Node*) arvore);
}

/**
 * Frees memory previously allocated to the AST structure
 *
 * @param arvore AST Pointer
 */
void libera (void *tree) {
	free_tree((Node*) tree);
}
