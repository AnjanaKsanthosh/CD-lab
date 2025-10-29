%option noyywrap
%{
#include <stdio.h>
FILE *fp;
%}

%%
abc     { printf("ABC"); }     // Replace abc → ABC
.       { printf("%s", yytext); }   // Print other characters as they are
\n      { printf("\n"); }      // Print newlines properly
%%

int main() {
    fp = fopen("input.txt", "r");
    if (!fp) {
        printf("Error: Cannot open file!\n");
        return 1;
    }

    yyin = fp;   // read input from file
    yylex();     // run lexical analysis

    fclose(fp);
    return 0;
}

