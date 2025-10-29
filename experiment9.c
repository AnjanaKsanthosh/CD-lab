#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isKeyword(char *word) {
    char *kw[] = {"auto","break","case","char","const","continue","default",
    "do","double","else","enum","extern","float","for","goto","if","int",
    "long","register","return","short","signed","sizeof","static","struct",
    "switch","typedef","union","unsigned","void","volatile","while"};
    for (int i = 0; i < 32; i++)
        if (strcmp(kw[i], word) == 0)
            return 1;
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <input file name>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (!f) {
        printf("Error: Cannot open file %s\n", argv[1]);
        return 1;
    }

    char ch, word[100];
    int i = 0;

    while ((ch = fgetc(f)) != EOF) {
        // Skip spaces and newlines
        if (isspace(ch)) continue;

        // Identifiers or keywords
        if (isalpha(ch) || ch == '_') {
            i = 0;
            word[i++] = ch;
            while (isalnum(ch = fgetc(f)) || ch == '_')
                word[i++] = ch;
            word[i] = '\0';
            fseek(f, -1, SEEK_CUR);
            if (isKeyword(word))
                printf("%s is a keyword\n", word);
            else
                printf("%s is an identifier\n", word);
        }

        // Numbers
        else if (isdigit(ch)) {
            i = 0;
            word[i++] = ch;
            while (isdigit(ch = fgetc(f)))
                word[i++] = ch;
            word[i] = '\0';
            fseek(f, -1, SEEK_CUR);
            printf("%s is an integer\n", word);
        }

        // Strings
        else if (ch == '\"') {
            i = 0;
            word[i++] = ch;
            while ((ch = fgetc(f)) != '\"' && ch != EOF)
                word[i++] = ch;
            word[i++] = '\"';
            word[i] = '\0';
            printf("%s is a string literal\n", word);
        }

        // Comments
        else if (ch == '/') {
            char next = fgetc(f);
            if (next == '/') {
                while ((ch = fgetc(f)) != '\n' && ch != EOF);
                printf("Single line comment ignored\n");
            } else if (next == '*') {
                char prev = 0;
                while ((ch = fgetc(f)) != EOF) {
                    if (prev == '*' && ch == '/') break;
                    prev = ch;
                }
                printf("Multiline comment ignored\n");
            } else {
                fseek(f, -1, SEEK_CUR);
                printf("/ is an arithmetic operator\n");
            }
        }

        // Operators and punctuators
        else if (strchr("+-*=<>!&|%", ch)) {
            char next = fgetc(f);
            if (next == '=')
                printf("%c= is an operator\n", ch);
            else if ((ch == '&' && next == '&') || (ch == '|' && next == '|'))
                printf("%c%c is a logical operator\n", ch, next);
            else {
                fseek(f, -1, SEEK_CUR);
                printf("%c is an operator\n", ch);
            }
        }

        else if (strchr(";:,(){}[]'", ch))
            printf("%c is a punctuator\n", ch);

        else
            printf("%c is an unknown symbol\n", ch);
    }

    fclose(f);
    return 0;
}
