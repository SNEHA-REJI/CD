%{
int vowels = 0, consonants = 0;
%}
%%
[aeiouAEIOU] { vowels++; }
[a-zA-Z] { consonants++; }
.|\n { /* Ignore other characters */ }
%%
int main() {
printf("Enter input string (Press Ctrl+D to end):\n");
yylex();
printf("Vowels: %d\nConsonants: %d\n", vowels, consonants);
return 0;
}
int yywrap() { return 1; }
