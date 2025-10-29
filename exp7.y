%{
  #include <stdio.h>
  #include <stdlib.h>
  int yylex();
  int yyerror();
%}
%token num n1
%left '+' '-'
%left '*' '/'
%%
start : E n1 { printf("result=%d\n", $1); return 0; }
;
E : E '+' E { $$ = $1 + $3; }
  | E '-' E { $$ = $1 - $3; }
  | E '*' E { $$ = $1 * $3; }
  | E '/' E { $$ = $1 / $3; }
  | num     { $$ = $1; }
  ;
%%
int main() {
  return yyparse();
}
int yyerror() {
  printf("invalid\n");
  return 0;
}

