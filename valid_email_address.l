%{
#include <stdio.h>
int valid = 0; // Flag: 1 if at least one valid email is found
%}
/* Valid email pattern for full lines */
VALID_EMAIL ^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$
%%
{VALID_EMAIL} { valid = 1; }
.* { /* Ignore all lines */ }
%%
int main() {
printf("Enter input text (Press Ctrl+D to end):\n");
yylex();
// Final result based on the flag
if (valid)
printf("\nValid email found.\n");
else
printf("\nNo valid email detected.\n");
return 0;
}
int yywrap() { return 1; }
