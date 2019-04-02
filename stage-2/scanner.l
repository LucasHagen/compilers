%{

/*
	Authors:
		- Gabriel Pakulski da Silva - 00274701
		- Lucas Sonntag Hagen       - 00274698
*/

#include "parser.tab.h"

%}
%option yylineno
%option noyywrap

%x MLINE_COMMENT

white           [ \t]+
digit           [0-9]
integer         -?{digit}+
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

int return TK_PR_INT;
float return TK_PR_FLOAT;
bool return TK_PR_BOOL;
char return TK_PR_CHAR;
string return TK_PR_STRING;
if return TK_PR_IF;
then return TK_PR_THEN;
else return TK_PR_ELSE;
while return TK_PR_WHILE;
do return TK_PR_DO;
input return TK_PR_INPUT;
output return TK_PR_OUTPUT;
return return TK_PR_RETURN;
const return TK_PR_CONST;
static return TK_PR_STATIC;
foreach return TK_PR_FOREACH;
for return TK_PR_FOR;
switch return TK_PR_SWITCH;
case return TK_PR_CASE;
break return TK_PR_BREAK;
continue return TK_PR_CONTINUE;
class return TK_PR_CLASS;
private return TK_PR_PRIVATE;
public return TK_PR_PUBLIC;
protected return TK_PR_PROTECTED;

"<="  return TK_OC_LE;
">="  return TK_OC_GE;
"=="  return TK_OC_EQ;
"!="  return TK_OC_NE;
"&&"  return TK_OC_AND;
"||"  return TK_OC_OR;
">>"  return TK_OC_SR;
"<<"  return TK_OC_SL;
"%>%" return TK_OC_FORWARD_PIPE;
"%|%" return TK_OC_BASH_PIPE;

{integer} { return TK_LIT_INT; }

{float}   { return TK_LIT_FLOAT; }

{char}    { return TK_LIT_CHAR; }

{string}  { return TK_LIT_STRING; }

true  return TK_LIT_TRUE;
false return TK_LIT_FALSE;

{especial_char} { return (int) *yytext; }

{identifier} { return TK_IDENTIFICADOR; }

{white}   { }

\n { }

[^ \n\t,;:()\[\]{}+\-|?*/<>=!&%#^.$]+ { return TOKEN_ERRO; }

%%

int get_line_number(void)
{
	return yylineno;
}
