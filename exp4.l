%option noyywrap
%{
#include <stdio.h>
#include <ctype.h>
FILE *fp;
%}

%%
"int"|"float"|"char"|"if"|"else"|"return" { printf("Keyword: %s\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]* { printf("Identifier: %s\n", yytext); }
[0-9]+ { printf("Number: %s\n", yytext); }
"#"[a-zA-Z]* {printf("perprocessor=%s",yytext);}
"+"|"-"|"*"|"/"|"=" { printf("Operator: %s\n", yytext); }
";"|","|"\("|"\)"|"\{"|"\}" { printf("Punctuation: %s\n", yytext); }
[ \t\n] { ; } // ignore whitespace
. { printf("Unknown: %s\n", yytext); }
%%

int main() {
    fp = fopen("input.txt", "r");
    if (!fp) {
        printf("Error: Cannot open file!\n");
        return 1;
    }
    yyin = fp; // read from file
    yylex(); // start lexical analysis
    fclose(fp);
    return 0;
}

