%{
  #include <stdio.h>
  int yylex();
  int yyerror();
%}
%token alpha num
%%
start : s '\n' {printf("valid expression"); return 0;}
s : alpha A 
  ;
A : alpha A 
  | num A 
  |
  ;
%%
int main()
{
  printf("Enter an Expression\n");
  yyparse();
  
}
int yyerror()
{
  printf("invalid\n");
}
