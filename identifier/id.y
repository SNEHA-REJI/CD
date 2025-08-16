%{
#include <stdio.h>
#include <stdlib.h>
int yylex(void);
void yyerror(const char *s);
%}
%token IDENTIFIER
%%
input:
input IDENTIFIER { printf("Valid
identifier\n"); }
| input '\n' { printf("Invalid input\n"); }
| /* empty */
;
%%
void yyerror(const char *s) {
// silent
}
int main() {
printf("Enter one identifier per line (Ctrl+D
to stop):\n");
yyparse();
return 0;
}
