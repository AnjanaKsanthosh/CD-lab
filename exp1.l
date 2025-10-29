%option noyywrap
%{
#include <stdio.h>
int lines = 0, words = 0, chars = 0;
FILE *fp;
%}

%%
\n           { lines++; chars++; }
[ \t]        { chars++; }
[a-zA-Z0-9]+ { words++; chars += yyleng; }
.            { chars++; }
%%

int main() {
    fp = fopen("input.txt", "r");   
    if (!fp) {
        printf("Error: Cannot open file!\n");
        return 1;
    }

    yyin = fp;      
    yylex();        

    printf("\nNumber of lines: %d\n", lines);
    printf("Number of words: %d\n", words);
    printf("Number of characters: %d\n", chars);

    fclose(fp);
    return 0;
}

