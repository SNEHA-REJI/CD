%{
#include <stdio.h>
#include <stdlib.h>
int yylex(void);
void yyerror(const char *s);
%}
%token NUMBER
%left '+' '-'
%left '*' '/'
%right UMINUS
%%
stmt:
stmt expr '\n' { printf("Result = %d\n", $2); }
| /* empty */
;
expr:
expr '+' expr { $$ = $1 + $3; }
| expr '-' expr { $$ = $1 - $3; }
| expr '*' expr { $$ = $1 * $3; }
| expr '/' expr {

if ($3 == 0) {
yyerror("Division by zero");
YYABORT;
}
$$ = $1 / $3;
}

| '-' expr %prec UMINUS { $$ = -$2; }
| '(' expr ')' { $$ = $2; }
| NUMBER { $$ = $1; }
;
%%
void yyerror(const char *s) {

fprintf(stderr, "Error: %s\n", s);
}
int main() {
printf("Enter arithmetic expressions (Ctrl+D to exit):\n");
yyparse();
return 0;
}
