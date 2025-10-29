%option noyywrap
%{
  #include "exp7.tab.h"
  #include <stdlib.h>
%}
%%
[0-9]+ { yylval = atoi(yytext); return num; }
.      { return yytext[0]; }
\n     { return n1; }
%%
