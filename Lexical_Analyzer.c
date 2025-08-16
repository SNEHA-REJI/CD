#include <stdio.h>
#include <string.h>
#include <ctype.h>
void removeComments(FILE *src, FILE *dest);
void analyse(FILE *fp);
int isKeyword(const char *word);
int main() {
    FILE *source = fopen("input.c", "r");
    FILE *temp = tmpfile();
    if (!source) {
        printf("Error: input.c not found.\n");
        return 1;
    }
    removeComments(source, temp);
    rewind(temp);
    printf("Tokens:\n-----------------------\n");
    analyse(temp);
    fclose(source);
    fclose(temp);
    return 0;
}
// Remove both single-line (//) and multi-line (/* */) comments
void removeComments(FILE *src, FILE *dest) {
    char ch, next;
    while ((ch = fgetc(src)) != EOF) {
        if (ch == '/') {
            next = fgetc(src);
            if (next == '/') {
                while ((ch = fgetc(src)) != '\n' && ch != EOF);
            } else if (next == '*') {
                while (1) {
                    ch = fgetc(src);
                    if (ch == EOF) break;
                    if (ch == '*') {
                        if ((next = fgetc(src)) == '/') break;
                        else ungetc(next, src);
                    }
                }
            } else {
                fputc(ch, dest);
                fputc(next, dest);
            }
        } else {
            fputc(ch, dest);
        }
    }
}
void analyse(FILE *fp) {
    char ch, buffer[100];
    int i = 0, state = 0;

    while ((ch = fgetc(fp)) != EOF) {
       switch (state) {
    case 0:
        if (isspace(ch)) break;

        else if (ch == '+')
            state = 1;
        else if (ch == '-')
            state = 4;
        else if (ch == '*')
            state = 7;
        else if (ch == '/')
            state = 10;
        else if (ch == '>')
            state = 13;
        else if (ch == '<')
            state = 16;
        else if (ch == '=')
            state = 19;
        else if (isdigit(ch)) {
            buffer[i++] = ch;
            state = 22;
        }
        else if (isalpha(ch) || ch == '_') {
            buffer[i++] = ch;
            state = 27;
        }
        else if (ch == ';')
            printf("Semicolon (;)\n");

        else if (ch == ',')
            printf("Comma (,)\n");

        else if (ch == '{' || ch == '}' || ch == '(' || ch == ')')
            printf("Delimiter: %c\n", ch);
        break;
    // '+' or '+='
    case 1:
        ch = fgetc(fp);
        if (ch == '=')
            printf("Operator: +=\n");
        else {
            printf("Operator: +\n");
            ungetc(ch, fp);
        }
        state = 0;
        break;
    // '-' or '-='
    case 4:
        ch = fgetc(fp);
        if (ch == '=')
            printf("Operator: -=\n");
        else {
            printf("Operator: -\n");
            ungetc(ch, fp);
        }
        state = 0;
        break;
    // '*' or '*='
    case 7:
        ch = fgetc(fp);
        if (ch == '=')
            printf("Operator: *=\n");
        else {
            printf("Operator: *\n");
            ungetc(ch, fp);
        }
        state = 0;
        break;
    // '/' or '/='
    case 10:
        ch = fgetc(fp);
        if (ch == '=')
            printf("Operator: /=\n");
        else {
            printf("Operator: /\n");
            ungetc(ch, fp);
        }
        state = 0;
        break;
    // '>' or '>='
    case 13:
        ch = fgetc(fp);
        if (ch == '=')
            printf("Operator: >=\n");
        else {
            printf("Operator: >\n");
            ungetc(ch, fp);
        }
        state = 0;
        break;
    // '<' or '<='
    case 16:
        ch = fgetc(fp);
        if (ch == '=')
            printf("Operator: <=\n");
        else {
            printf("Operator: <\n");
            ungetc(ch, fp);
        }
        state = 0;
        break;
    // '=' or '=='
    case 19:
        ch = fgetc(fp);
        if (ch == '=')
            printf("Operator: ==\n");
        else {
            printf("Operator: =\n");
            ungetc(ch, fp);
        }
        state = 0;
        break;

    // Numbers
    case 22:
        if (isdigit(ch)) {
            buffer[i++] = ch;
        } else if (ch == '.') {
            buffer[i++] = ch;
            state = 23;
        } else {
            buffer[i] = '\0';
            printf("Integer: %s\n", buffer);
            i = 0;
            ungetc(ch, fp);
            state = 0;
        }
        break;

    case 23:
        if (isdigit(ch)) {
            buffer[i++] = ch;
            state = 24;
        } else {
            printf("Invalid number\n");
            i = 0;
            state = 0;
        }
        break;

    case 24:
        if (isdigit(ch)) {
            buffer[i++] = ch;
        } else {
            buffer[i] = '\0';
            printf("Float: %s\n", buffer);
            i = 0;
            ungetc(ch, fp);
            state = 0;
        }
        break;
    // Keywords and Identifiers
    case 27:
        if (isalnum(ch) || ch == '_') {
            buffer[i++] = ch;
        } else {
            buffer[i] = '\0';
            if (isKeyword(buffer))
                printf("Keyword: %s\n", buffer);
            else
                printf("Identifier: %s\n", buffer);
            i = 0;
            ungetc(ch, fp);
            state = 0;
        }
        break;
	}	
    }
}                                                                                                                                

// Check if a word is a C keyword
int isKeyword(const char *word) {
    FILE *fp = fopen("keywords.txt", "r");
    char kw[100];
    if (!fp) {
        printf("Warning: keywords.txt not found.\n");
        return 0;
    }

    while (fscanf(fp, "%s", kw) != EOF) {
        if (strcmp(word, kw) == 0) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}
