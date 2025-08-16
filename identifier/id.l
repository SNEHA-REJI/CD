%{
#include "y.tab.h"
%}
%%
[a-zA-Z][a-zA-Z0-9]*\n return IDENTIFIER;
.*\n return '\n';
%%
int yywrap() { return 1; }
