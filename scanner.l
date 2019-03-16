%{
#define YYSTYPE double
#include "tokens.h"
%}

white [ \t]+
digit [0-9]
integer {digit}+
identifier [a-zA-Z_][a-zA-Z0-9_]*

%%

{white} { }
{identifier} { printf("ID: %s\n", yytext); return TK_IDENTIFICADOR; }

%%

int get_line_number () {
  return 0;
}
