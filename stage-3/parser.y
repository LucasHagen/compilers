%{

#include <stdio.h>
#include "lexeme.h"
#include "tree.h"
#include "printer.h"

/*
	Authors:
		- Gabriel Pakulski da Silva - 00274701
		- Lucas Sonntag Hagen       - 00274698
*/

extern int yylineno;
extern void* arvore;

int yylex(void);
void yyerror (char const *s);
Lexeme* create_lexeme(char c);

%}

%union {
	struct lexeme* lex_value;
	struct node*   node;
	int 		   int_val;
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
%right EXCLAMATION HASHTAG
%left UOP


%type <int_val> const
%type <int_val> static

%type <lex_value> type

%type <node> var
%type <node> global_var
%type <node> literal
%type <node> programa
%type <node> big_list
%type <node> function
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
%type <node> operand
%type <node> identifier
%type <node> un_op
%type <node> optional_vector_index

%start programa

%%

programa:
	big_list
	{
		$$ = $1;
		arvore = $$;
	}|
	%empty
	{
		$$ = NULL;
	};

big_list:
	big_list global_var
	{
		$$ = $2;
		$$->seq = $1;
	}|
	big_list function
	{
		$$ = $2;
		$$->seq = $1;
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
		$$ = create_node_literal($1);
	}|
	TK_LIT_FALSE
	{
		$$ = create_node_literal($1);
	}|
	TK_LIT_STRING
	{
		$$ = create_node_literal($1);
	}|
	TK_LIT_CHAR
	{
		$$ = create_node_literal($1);
	}|
	TK_LIT_INT
	{
		$$ = create_node_literal($1);
	}|
	TK_LIT_FLOAT
	{
		$$ = create_node_literal($1);
	};

type:
	TK_PR_INT
	{
		$$ = $1;
	}|
	TK_PR_FLOAT
	{
		$$ = $1;
	}|
	TK_PR_CHAR
	{
		$$ = $1;
	}|
	TK_PR_BOOL
	{
		$$ = $1;
	}|
	TK_PR_STRING
	{
		$$ = $1;
	};

global_var:
	var ';'
	{
		$$ = $1;
	};

var:
	TK_IDENTIFICADOR optional_vector_index static type
	{
		$$ = create_node_global_var_decl($1, $2, $4, $3, 0, NULL);
	};

static:
	TK_PR_STATIC
	{
		$$ = 1;
	}|
	%empty
	{
		$$ = 0;
	};

const:
	TK_PR_CONST
	{
		$$ = 1;
	}|
	%empty
	{
		$$ = 0;
	};

function:
	static type TK_IDENTIFICADOR '(' function_parameters ')' body
	{
		$$ = create_node_func_decl(
			$3,
			$2,
			$1,
			$5,
			$7
		);
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
		$$ = $3;
		$$->seq = $1;
	}|
	parameter
	{
		$$ = $1;
	};

parameter:
	const type TK_IDENTIFICADOR
	{
		$$ = create_node_func_param($3, $2, $1);
	};

body:
	commands_block
	{
		$$ = $1;
	};

commands_block:
	'{' commands_list '}'
	{
		$$ = create_node_command_block($2);
	} |
	'{' '}'
	{
		$$ = create_node_command_block(NULL);
	};

commands_list:
	command ';'
	{
		$$ = $1;
	}|
	commands_list command ';'
	{
		$$ = $2;
		$$->seq = $1;
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
		$$ = create_node_var_decl(
			$4,
			NULL,
			$3,
			$1,
			$2,
			$5
		);
	};

c_declare_variable_attr:
	%empty
	{
		$$ = NULL;
	}|
	TK_OC_LE c_declare_attr_value
	{
		$$ = $2;
	};

c_declare_attr_value:
	literal
	{
		$$ = $1;
	}|
	TK_IDENTIFICADOR
	{
		$$ = create_node_var_access($1, NULL);
	};

c_attr:
	TK_IDENTIFICADOR optional_vector_index '=' expression
	{
		$$ = create_node_var_attr($1, $2, $4);
	};

c_input:
	TK_PR_INPUT expression
	{
		$$ = create_node_input($2);
	};

c_output:
	TK_PR_OUTPUT c_output_exp_list
	{
		$$ = create_node_output($2);
	};

c_output_exp_list:
	expression
	{
		$$ = $1;
	}|
	c_output_exp_list ',' expression
	{
		$$ = $3;
		$$->seq = $1;
	};

c_call_func:
	TK_IDENTIFICADOR '(' c_call_parameters ')'
	{
		$$ = create_node_func_call($1, $3);
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
		$$ = $3;
		$$->seq = $1;
	};

c_shift:
	identifier c_shift_symbol expression
	{
		$$ = $2;
		$$->n_shift.var = $1;
		$$->n_shift.count = $3;
	};

c_shift_symbol:
	TK_OC_SR
	{
		$$ = create_node_shift_right();
	}|
	TK_OC_SL
	{
		$$ = create_node_shift_left();
	};

c_return:
	TK_PR_RETURN expression
	{
		$$ = create_node_return($2);
	};

c_continue:
	TK_PR_CONTINUE
	{
		$$ = create_node_continue();
	};

c_break:
	TK_PR_BREAK
	{
		$$ = create_node_break();
	};

c_if:
	TK_PR_IF '(' expression ')' TK_PR_THEN commands_block c_else
	{
		$$ = create_node_if($3, $6, $7);
	};

c_else:
	%empty
	{
		$$ = NULL;
	}|
	TK_PR_ELSE commands_block
	{
		$$ = $2;
	};

c_for:
	TK_PR_FOR '(' c_for_command_list ':' expression ':' c_for_command_list ')' commands_block
	{
		$$ = create_node_for($3, $5, $7, $9);
	};

c_for_command_list:
 	c_for_no_comma
	{
		$$ = $1;
	}|
	c_for_command_list ',' c_for_no_comma
	{
		$$ = $3;
		$$->seq = $1;
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
		$$ = create_node_while($3,$6);
	};

expression:
	operand
	{
		$$ = $1;
	}|
	expression PLUS expression
	{
		$$ = create_node_bin_op($2, $1, $3);
	}|
	expression MINUS expression
	{
		$$ = create_node_bin_op($2, $1, $3);
	}|
	expression MULT expression
	{
		$$ = create_node_bin_op($2, $1, $3);
	}|
	expression DIV expression
	{
		$$ = create_node_bin_op($2, $1, $3);
	}|
	expression R_DIV expression
	{
		$$ = create_node_bin_op($2, $1, $3);
	}|
	expression BIT_OR expression
	{
		$$ = create_node_bin_op($2, $1, $3);
	}|
	expression EXP expression
	{
		$$ = create_node_bin_op($2, $1, $3);
	}|
	expression GREATER expression
	{
		$$ = create_node_bin_op($2, $1, $3);
	}|
	expression LESS expression
	{
		$$ = create_node_bin_op($2, $1, $3);
	}|
	expression TK_OC_LE expression
	{
		$$ = create_node_bin_op($2, $1, $3);
	}|
	expression TK_OC_GE expression
	{
		$$ = create_node_bin_op($2, $1, $3);
	}|
	expression TK_OC_EQ expression
	{
		$$ = create_node_bin_op($2, $1, $3);
	}|
	expression TK_OC_NE expression
	{
		$$ = create_node_bin_op($2, $1, $3);
	}|
	expression TK_OC_AND expression
	{
		$$ = create_node_bin_op($2, $1, $3);
	}|
	expression TK_OC_OR expression
	{
		$$ = create_node_bin_op($2, $1, $3);
	}|
	expression '&' expression
	{
		$$ = create_node_bin_op($2, $1, $3);
	}|
	un_op expression %prec UOP
	{
		$$ = $1;
		$$->n_un_op.operand = $2;
	}|
	expression QUESTION expression ':' expression %prec QUESTION
	{
		$$ = create_node_ter_op($1, $3, $5);
	}|
	'(' expression ')'
	{
		$$ = $2;
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
		$$ = create_node_var_access($1, NULL);
	}|
	TK_IDENTIFICADOR '[' expression ']'
	{
		$$ = create_node_var_access($1, $3);
	};

optional_vector_index:
	%empty
	{
		$$ = NULL;
	}|
	'[' expression ']'
	{
		$$ = $2;
	};

un_op:
	PLUS
	{
		$$ = create_node_un_op($1, NULL);
	}|
	MINUS
	{
		$$ = create_node_un_op($1, NULL);
	}|
	EXCLAMATION
	{
		$$ = create_node_un_op($1, NULL);
	}|
	'&'
	{
		$$ = create_node_un_op($1, NULL);
	}|
 	MULT
	{
		$$ = create_node_un_op($1, NULL);
	}|
	HASHTAG
	{
		$$ = create_node_un_op($1, NULL);
	}|
	QUESTION
	{
		$$ = create_node_un_op($1, NULL);
	};

%%

/**
 * Prints an error, when it occurs
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
	print_tree((Node*) arvore);
}

/**
 * Frees memory previously allocated to the AST structure
 *
 * @param arvore AST Pointer
 */
void libera (void *tree) {
	free_tree((Node*) tree);
}

Lexeme* create_lexeme(char c) {
	Lexeme* lex = (Lexeme*) malloc(sizeof(Lexeme));
	lex->line_number = -1;
	lex->literal_type = NOT_LITERAL;
	lex->token_value.v_char = c;
	lex->token_type = SPECIAL_CHAR;
	return lex;
}
