%{

/*
	Authors:
		- Gabriel Pakulski da Silva - 00274701
		- Lucas Sonntag Hagen       - 00274698
*/

#include "parser.tab.h"
#include "lexeme.h"
#include <string.h>

void keyword();
void special_char();
void operator();
void identifier();
void literal(int id);
void create_token(int value);
int  parse_bool(char* text);

%}
%option yylineno
%option noyywrap

%x MLINE_COMMENT

white           [ \t]+
digit           [0-9]
integer         {digit}+
identifier      [a-zA-Z_][a-zA-Z0-9_]*
float           {integer}[.]{digit}+([eE][+-]?{digit}+)?
line_comment    "//"[^\n]*
char            \'([^'\n]|\\.)\'
string          \"(([^"\n]|\\\")*[^\\\n])?\"
especial_char   [,;:()\[\]{}+\-|?*/<>=!&%#^.$]
%%

{line_comment} { }

"/*"                { BEGIN(MLINE_COMMENT); }
<MLINE_COMMENT>"*/" { BEGIN(INITIAL); }
<MLINE_COMMENT>\n   { }
<MLINE_COMMENT>.    { }

int {
	keyword();
	return TK_PR_INT;
}

float {
	keyword();
	return TK_PR_FLOAT;
}

bool {
	keyword();
	return TK_PR_BOOL;
}

char {
	keyword();
	return TK_PR_CHAR;
}

string {
	keyword();
	return TK_PR_STRING;
}

if {
	keyword();
	return TK_PR_IF;
}

then {
	keyword();
	return TK_PR_THEN;
}

else {
	keyword();
	return TK_PR_ELSE;
}
while {
	keyword();
	return TK_PR_WHILE;
}

do {
	keyword();
	return TK_PR_DO;
}

input {
	keyword();
	return TK_PR_INPUT;
}

output {
	keyword();
	return TK_PR_OUTPUT;
}

return {
	keyword();
	return TK_PR_RETURN;
}

const {
	keyword();
	return TK_PR_CONST;
}

static {
	keyword();
	return TK_PR_STATIC;
}

foreach {
	keyword();
	return TK_PR_FOREACH;
}

for {
	keyword();
	return TK_PR_FOR;
}

switch {
	keyword();
	return TK_PR_SWITCH;
}

case {
	keyword();
	return TK_PR_CASE;
}

break {
	keyword();
	return TK_PR_BREAK;
}

continue {
	keyword();
	return TK_PR_CONTINUE;
}

class {
	keyword();
	return TK_PR_CLASS;
}

private {
	keyword();
	return TK_PR_PRIVATE;
}

public {
	keyword();
	return TK_PR_PUBLIC;
}
protected {
	keyword();
	return TK_PR_PROTECTED;
}

"<="  {
	operator();
	return TK_OC_LE;
}

">=" {
	operator();
	return TK_OC_GE;
}

"==" {
	operator();
	return TK_OC_EQ;
}

"!=" {
	operator();
	return TK_OC_NE;
}

"&&" {
	operator();
	return TK_OC_AND;
}

"||" {
	operator();
	return TK_OC_OR;
}

">>" {
	operator();
	return TK_OC_SR;
}

"<<" {
	operator();
	return TK_OC_SL;
}

"%>%" {
	operator();
	return TK_OC_FORWARD_PIPE;
}

"%|%" {
	operator();
	return TK_OC_BASH_PIPE;
}


"!" {
	operator();
	return EXCLAMATION;
}
"?" {
	operator();
	return QUESTION;
}
"#" {
	operator();
	return HASHTAG;
}
"+" {
	operator();
	return PLUS;
}
"-" {
	operator();
	return MINUS;
}
"*" {
	operator();
	return MULT;
}
"/" {
	operator();
	return DIV;
}
"%" {
	operator();
	return R_DIV;
}
"|" {
	operator();
	return BIT_OR;
}
"^" {
	operator();
	return EXP;
}
">" {
	operator();
	return GREATER;
}
"<" {
	operator();
	return LESS;
}

{integer} {
	literal(INT);
	return TK_LIT_INT;
}

{float}   {
	literal(FLOAT);
	return TK_LIT_FLOAT;
}

{char}    {
	literal(CHAR);
	return TK_LIT_CHAR;
}

{string}  {
	literal(STRING);
	return TK_LIT_STRING;
}

true  {
	literal(BOOL);
	return TK_LIT_TRUE;
}
false {
	literal(BOOL);
	return TK_LIT_FALSE;
}
{especial_char} {
	special_char();
	return (int) *yytext;
}

{identifier} {
	identifier();
	return TK_IDENTIFICADOR;
}

{white}   { }

\n { }

[^ \n\t,;:()\[\]{}+\-|?*/<>=!&%#^.$]+ { return TOKEN_ERRO; }

%%

int get_line_number(void)
{
	return yylineno;
}

void keyword(){
	create_token(KEYWORD);
}
void special_char(){
	create_token(SPECIAL_CHAR);
}
void operator(){
	create_token(OPERATOR);
}
void identifier(){
	create_token(IDENTIFIER);
}
void literal(int id){
	create_token(LITERAL);
	switch(id){
		case INT:
			yylval.lex_value->literal_type = INT;
			yylval.lex_value->token_value.v_int = atoi(yytext);
		break;

		case FLOAT:
			yylval.lex_value->literal_type = FLOAT;
			yylval.lex_value->token_value.v_float = atof(yytext);
		break;

		case BOOL:
			yylval.lex_value->literal_type = BOOL;
			yylval.lex_value->token_value.v_bool = parse_bool(yytext);
		break;

		case CHAR:
			yylval.lex_value->literal_type = CHAR;
			yylval.lex_value->token_value.v_char = yytext[1];
		break;
		case STRING:
			yylval.lex_value->literal_type = STRING;
			yylval.lex_value->token_value.v_string = strdup(yytext);
		break;

		default:
			printf("Tipo invalido de literal !!!!!!!!");
		break;
	}
}

void create_token(int value) {
	yylval.lex_value = (struct lexeme *) malloc(sizeof(struct lexeme));
	yylval.lex_value->line_number = yylineno;
	switch(value){
		case KEYWORD:
			yylval.lex_value->literal_type = NOT_LITERAL;
	 		yylval.lex_value->token_value.v_string = strdup(yytext);
			yylval.lex_value->token_type = KEYWORD;
		break;

		case SPECIAL_CHAR:
			yylval.lex_value->literal_type = NOT_LITERAL;
	 		yylval.lex_value->token_value.v_char = yytext[0];
			yylval.lex_value->token_type = SPECIAL_CHAR;
		break;

		case OPERATOR:
			yylval.lex_value->literal_type = NOT_LITERAL;
	 		yylval.lex_value->token_value.v_string = strdup(yytext);
			yylval.lex_value->token_type = OPERATOR;
		break;

		case IDENTIFIER:
			yylval.lex_value->token_type = NOT_LITERAL;
	 		yylval.lex_value->token_value.v_string = strdup(yytext);
			yylval.lex_value->token_type = IDENTIFIER;
		break;

		case LITERAL:
			yylval.lex_value->token_type = LITERAL;
		break;

		default:
			printf("Tipo de token invalido!");
		break;
	}
}

int parse_bool (char *text){
	if(strcmp(text,"true") == 0)
		return TRUE;
	else
		return FALSE;
}
