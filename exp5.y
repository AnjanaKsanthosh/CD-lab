%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
int yyerror();
%}

%token id num

%left '+' '-'
%left '*' '/'
%right '^'
%left '(' ')'

%%
start : E '\n' { printf("Valid Expression\n"); return 0; }
     ;

E : E '+' E
  | E '-' E
  | E '*' E
  | E '/' E
  | E '^' E
  | '(' E ')'
  | num
  | id
  ;
%%
int main() {
    printf("Enter an expression:\n");
    yyparse();
    return 0;
}

int yyerror() {
    printf("Invalid Expression\n");
    return 0;
}

