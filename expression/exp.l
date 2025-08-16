%{
#include "y.tab.h"
%}
%%
[0-9]+ { yylval = atoi(yytext); return
NUMBER; }
[+\-*/\n()] return yytext[0];
[ \t] ; // ignore spaces
. { return yytext[0]; } // for error characters
%%
int yywrap() { return 1; }
