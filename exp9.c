#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isKeyword(char word[]) {
    char *keywords[] = {"int","float","char","if","else","for","while","return"};
    for (int i = 0; i < 8; i++)
        if (strcmp(keywords[i], word) == 0)
            return 1;
    return 0;
}

int main() {
    char ch, word[50];
    int i = 0;
    FILE *fp = fopen("input.txt", "r");   
    if (!fp) {
        printf("File not found!\n");
        return 0;
    }

    while ((ch = fgetc(fp)) != EOF) {
        if (isalnum(ch) || ch == '_') {       
            word[i++] = ch;
        } else {
            if (i != 0) {                     
                word[i] = '\0';
                if (isKeyword(word))
                    printf("%s is a keyword\n", word);
                else if (isalpha(word[0]) || word[0]=='_')
                    printf("%s is an identifier\n", word);
                else
                    printf("%s is a number\n", word);
                i = 0;
            }

           
            if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=')
                printf("%c is an operator\n", ch);
            else if (ch == ';' || ch == ',' || ch == '(' || ch == ')' || ch == '{' || ch == '}')
                printf("%c is a punctuator\n", ch);
        }
    }

    fclose(fp);
    return 0;
}

