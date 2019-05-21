%{

#include <stdio.h>
#include <stdlib.h>

#include "lexeme.h"
#include "tree.h"
#include "printer.h"
#include "stack.h"
#include "scope.h"

/*
	Authors:
		- Gabriel Pakulski da Silva - 00274701
		- Lucas Sonntag Hagen       - 00274698
*/

extern int yylineno;
extern void* arvore;

Stack* scope_stack = NULL;

int yylex(void);
void yyerror (char const *s);

void create_scope_stack();

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
	initialize big_list destroy
	{
		$$ = $2;
		arvore = $$;
	}|
	initialize destroy
	{
		$$ = NULL;
	};

initialize:
	%empty
	{
		create_scope_stack();
	};

destroy:
	%empty
	{

	};

push_scope:
	'{'
	{
		free_lexeme($1);

		push(scope_stack, create_empty_scope());
	};

pop_scope:
	'}'
	{
		free_lexeme($1);

		pop(scope_stack);
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
		add_register(top(scope_stack), create_literal($1,NATUREZA_LITERAL_BOOL));
	}|
	TK_LIT_FALSE
	{
		$$ = create_node_literal($1);
		add_register(top(scope_stack), create_literal($1,NATUREZA_LITERAL_BOOL));
	}|
	TK_LIT_STRING
	{
		$$ = create_node_literal($1);
		add_register(top(scope_stack), create_literal($1,NATUREZA_LITERAL_STRING));
	}|
	TK_LIT_CHAR
	{
		$$ = create_node_literal($1);
		add_register(top(scope_stack), create_literal($1,NATUREZA_LITERAL_CHAR));
	}|
	TK_LIT_INT
	{
		$$ = create_node_literal($1);
		add_register(top(scope_stack), create_literal($1,NATUREZA_LITERAL_INT));
	}|
	TK_LIT_FLOAT
	{
		$$ = create_node_literal($1);
		add_register(top(scope_stack), create_literal($1,NATUREZA_LITERAL_FLOAT));
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

		free_lexeme($2);
	};

var:
	TK_IDENTIFICADOR optional_vector_index static type
	{
		if(identifier_in_stack(scope_stack, $1->token_value.v_string))
		{
			throw_error(ERR_DECLARED, $1->line_number);
		}

		$$ = create_node_global_var_decl($1, $2, $4, $3, NULL);

		ST_LINE* line = create_var_register($$);

		if($2 != NULL)
		{
			line->nature = NATUREZA_VECTOR;
		}

		add_register(top(scope_stack), line);
	};

static:
	TK_PR_STATIC
	{
		$$ = 1;

		free_lexeme($1);
	}|
	%empty
	{
		$$ = 0;
	};

const:
	TK_PR_CONST
	{
		$$ = 1;

		free_lexeme($1);
	}|
	%empty
	{
		$$ = 0;
	};

function:
	static type TK_IDENTIFICADOR '(' function_parameters ')' body
	{
		if(identifier_in_stack(scope_stack, $3->token_value.v_string))
		{
			throw_error(ERR_DECLARED, $2->line_number);
		}

		$$ = create_node_func_decl(
			$3,
			$2,
			$1,
			$5,
			$7
		);

		free_lexeme($4);
		free_lexeme($6);

		add_register(top(scope_stack), create_function_register($$));
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

		free_lexeme($2);
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
	push_scope commands_list pop_scope
	{
		$$ = create_node_command_block($2);
	} |
	push_scope pop_scope
	{
		$$ = create_node_command_block(NULL);
	};

commands_list:
	command ';'
	{
		$$ = $1;

		free_lexeme($2);
	}|
	commands_list command ';'
	{
		$$ = $2;
		$$->seq = $1;

		free_lexeme($3);
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
		if(identifier_in_scope(top(scope_stack), $4->token_value.v_string))
		{
			throw_error(ERR_DECLARED, $4->line_number);
		}

		$$ = create_node_var_decl(
			$4,
			$3,
			$1,
			$2,
			$5
		);

		add_register(top(scope_stack), create_var_register($$));
	};

c_declare_variable_attr:
	%empty
	{
		$$ = NULL;
	}|
	TK_OC_LE c_declare_attr_value
	{
		$$ = $2;

		free_lexeme($1);
	};

c_declare_attr_value:
	literal
	{
		$$ = $1;
	}|
	TK_IDENTIFICADOR
	{
		ST_LINE* line = identifier_in_stack(scope_stack, $1->token_value.v_string);
		if(!line)
		{
			throw_error(ERR_UNDECLARED, $1->line_number);
		}
		if(line->nature == NATUREZA_FUNCAO)
		{
			throw_error(ERR_FUNCTION, $1->line_number);
		}
		if(line->nature == NATUREZA_VECTOR)
		{
			throw_error(ERR_VECTOR, $1->line_number);
		}

		$$ = create_node_var_access($1, NULL, line->token_type);
	};

c_attr:
	TK_IDENTIFICADOR optional_vector_index '=' expression
	{
		ST_LINE* line = identifier_in_stack(scope_stack, $1->token_value.v_string);
		if(!line)
		{
			throw_error(ERR_UNDECLARED, $1->line_number);
		}
		if(line->nature == NATUREZA_FUNCAO)
		{
			throw_error(ERR_FUNCTION, $1->line_number);
		}
		if(line->nature == NATUREZA_VECTOR && $2 == NULL)
		{
			throw_error(ERR_VECTOR, $1->line_number);
		}
		if(line->nature == NATUREZA_VARIAVEL && $2 != NULL)
		{
			throw_error(ERR_VARIABLE, $1->line_number);
		}

		$$ = create_node_var_attr($1, $2, $4, line->token_type);

		free_lexeme($3);
	};

c_input:
	TK_PR_INPUT expression
	{
		$$ = create_node_input($2);

		free_lexeme($1);
	};

c_output:
	TK_PR_OUTPUT c_output_exp_list
	{
		$$ = create_node_output($2);

		free_lexeme($1);
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

		free_lexeme($2);
	};

c_call_func:
	TK_IDENTIFICADOR '(' c_call_parameters ')'
	{
		ST_LINE* l = identifier_in_stack(scope_stack, $1->token_value.v_string);
		if(!l)
		{
			throw_error(ERR_UNDECLARED, $1->line_number);
		}
		if(l->nature == NATUREZA_VARIAVEL)
		{
			throw_error(ERR_VARIABLE, $1->line_number);
		}
		if(l->nature == NATUREZA_VECTOR)
		{
			throw_error(ERR_VECTOR, $1->line_number);
		}
		// TODO: verify parameters

		$$ = create_node_func_call($1, $3, l->token_type);

		free_lexeme($2);
		free_lexeme($4);
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

		free_lexeme($2);
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

		free_lexeme($1);
	}|
	TK_OC_SL
	{
		$$ = create_node_shift_left();

		free_lexeme($1);
	};

c_return:
	TK_PR_RETURN expression
	{
		$$ = create_node_return($2);

		free_lexeme($1);
	};

c_continue:
	TK_PR_CONTINUE
	{
		$$ = create_node_continue();

		free_lexeme($1);
	};

c_break:
	TK_PR_BREAK
	{
		$$ = create_node_break();

		free_lexeme($1);
	};

c_if:
	TK_PR_IF '(' expression ')' TK_PR_THEN commands_block c_else
	{
		$$ = create_node_if($3, $6, $7, $1->line_number);

		free_lexeme($1);
		free_lexeme($2);
		free_lexeme($4);
		free_lexeme($5);
	};

c_else:
	%empty
	{
		$$ = NULL;
	}|
	TK_PR_ELSE commands_block
	{
		$$ = $2;

		free_lexeme($1);
	};

c_for:
	TK_PR_FOR '(' c_for_command_list ':' expression ':' c_for_command_list ')' commands_block
	{
		$$ = create_node_for($3, $5, $7, $9, $1->line_number);

		free_lexeme($1);
		free_lexeme($2);
		free_lexeme($4);
		free_lexeme($6);
		free_lexeme($8);
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

		free_lexeme($2);
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
		$$ = create_node_while($3,$6,$1->line_number);

		free_lexeme($1);
		free_lexeme($2);
		free_lexeme($4);
		free_lexeme($5);
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

		$$->val_type = $2->val_type;
	}|
	expression QUESTION expression ':' expression %prec QUESTION
	{
		$$ = create_node_ter_op($1, $3, $5, $4->line_number);

		free_lexeme($2);
		free_lexeme($4);
	}|
	'(' expression ')'
	{
		$$ = $2;

		free_lexeme($1);
		free_lexeme($3);
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
		ST_LINE* line = identifier_in_stack(scope_stack, $1->token_value.v_string);
		if(!line)
		{
			throw_error(ERR_UNDECLARED, $1->line_number);
		}
		if(line->nature == NATUREZA_FUNCAO)
		{
			throw_error(ERR_FUNCTION, $1->line_number);
		}
		if(line->nature == NATUREZA_VECTOR)
		{
			throw_error(ERR_VECTOR, $1->line_number);
		}

		$$ = create_node_var_access($1, NULL, line->token_type);
	}|
	TK_IDENTIFICADOR '[' expression ']'
	{
		ST_LINE* line = identifier_in_stack(scope_stack, $1->token_value.v_string);
		if(!line)
		{
			throw_error(ERR_UNDECLARED, $1->line_number);
		}
		if(line->nature == NATUREZA_FUNCAO)
		{
			throw_error(ERR_FUNCTION, $1->line_number);
		}
		if(line->nature == NATUREZA_VARIAVEL)
		{
			throw_error(ERR_VARIABLE, $1->line_number);
		}

		$$ = create_node_var_access($1, $3, line->token_type);

		free_lexeme($2);
		free_lexeme($4);
	};

optional_vector_index:
	%empty
	{
		$$ = NULL;
	}|
	'[' expression ']'
	{
		$$ = $2;

		free_lexeme($1);
		free_lexeme($3);
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

/**
 * Checks if stack was created, if not, creates one
 */
void create_scope_stack() {
	if(scope_stack == NULL)
	{
		scope_stack = create_empty_stack();
		push(scope_stack, create_empty_scope());
	}
}
