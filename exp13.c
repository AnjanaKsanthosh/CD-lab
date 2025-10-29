#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Quad {
    char op;
    char op1[10], op2[10], res[10];
} q[20];

int n;

// check if a string is an integer
int isNumber(char *s) {
    for (int i = 0; s[i]; i++)
        if (!isdigit(s[i])) return 0;
    return 1;
}

// compute the result of two constants
int calculate(int a, int b, char op) {
    if (op == '+') return a + b;
    if (op == '-') return a - b;
    if (op == '*') return a * b;
    if (op == '/' && b != 0) return a / b;
    return 0;
}

// constant folding
int fold() {
    int changed = 0;
    for (int i = 0; i < n; i++) {
        if (isNumber(q[i].op1) && isNumber(q[i].op2)) {
            int val = calculate(atoi(q[i].op1), atoi(q[i].op2), q[i].op);
            q[i].op = '=';
            sprintf(q[i].op1, "%d", val);
            strcpy(q[i].op2, "-");
            changed = 1;
        }
    }
    return changed;
}

// find constant value of a variable if assigned
char* getConst(char *var) {
    for (int i = 0; i < n; i++)
        if (q[i].op == '=' && strcmp(q[i].res, var) == 0)
            return q[i].op1;
    return var;
}

// constant propagation
int propagate() {
    int changed = 0;
    for (int i = 0; i < n; i++) {
        char new1[10], new2[10];
        strcpy(new1, getConst(q[i].op1));
        strcpy(new2, getConst(q[i].op2));
        if (strcmp(new1, q[i].op1) != 0 || strcmp(new2, q[i].op2) != 0)
            changed = 1;
        strcpy(q[i].op1, new1);
        strcpy(q[i].op2, new2);
    }
    return changed;
}

int main() {
    printf("Enter number of instructions: ");
    scanf("%d", &n);

    printf("Enter each instruction (Example: + 2 3 a):\n");
    for (int i = 0; i < n; i++)
        scanf(" %c %s %s %s", &q[i].op, q[i].op1, q[i].op2, q[i].res);

    int changed;
    do {
        changed = 0;
        changed |= fold();
        changed |= propagate();
    } while (changed); // repeat until no more changes

    printf("\nOptimized 3-Address Code:\n");
    printf("op\top1\top2\tres\n");
    printf("=====================\n");
    for (int i = 0; i < n; i++)
        printf("%c\t%s\t%s\t%s\n", q[i].op, q[i].op1, q[i].op2, q[i].res);

    return 0;
}

