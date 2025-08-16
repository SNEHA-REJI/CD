%{
#include "y.tab.h"
%}
%%
[0-9]+ { yylval = atoi(yytext); return NUMBER; }
[ \t] ; // Ignore whitespace
\n return '\n';
[-+*/()]{1} return yytext[0]; // Single char operators
. { printf("Invalid character: %s\n", yytext); }
%%
int yywrap() { return 1; }
