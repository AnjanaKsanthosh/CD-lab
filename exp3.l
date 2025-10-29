/**Write a LEX program to find the total number of vowels and consonants
from a given input string (file input)**/
%option noyywrap
%{
	#include <stdio.h>
	FILE *fb;
	int vovel=0; int con=0;
%}
%%
[aeiouAEIOU] {vovel++;}
[a-zA-Z] {con++;}
. {;}
%%
int main()
{
	fb=fopen("input.txt","r");
	yyin=fb;
	yylex();
	printf("vovel=%d",vovel);
	printf("Consonent=%d",con);
	fclose(fb);
	return 0;
}
