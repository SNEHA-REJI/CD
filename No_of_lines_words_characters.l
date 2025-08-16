%{
int lines = 0, words = 0, characters = 0;
%}
%%
\n { lines++; }
[ \t]+ { /* skip spaces and tabs for character count */ }
[a-zA-Z0-9]+ { words++; characters += yyleng; } // Count word characters
. { characters++; } // Count punctuation/symbols
%%
int main() {
printf("Enter input (Ctrl+D to finish):\n");
yylex();
printf("\nLines: %d\nWords: %d\nCharacters (excluding spaces/newlines): %d\n", lines,
words, characters);
return 0;
}
int yywrap() { return 1; }
