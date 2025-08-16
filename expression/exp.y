%{
#include <stdio.h>
#include <stdlib.h>
int yylex(void);
void yyerror(const char *s);
%}
%token NUMBER
%left '+' '-'
%left '*' '/'
%left UMINUS
%%
input:
input expr '\n' { printf("Valid
Expression\n"); }
|
;
expr:
expr '+' expr
| expr '-' expr
| expr '*' expr
| expr '/' expr
| '(' expr ')'
| '-' expr %prec UMINUS
| NUMBER
;
%%
void yyerror(const char *s) {
printf("Invalid Expression\n");
}
int main() {
printf("Enter arithmetic expressions
(Ctrl+D to stop):\n");
yyparse();
return 0;
}
