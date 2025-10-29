#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 50

char operands[MAX][10]; // Operand stack
char operators[MAX];     // Operator stack
int topOpnd = -1, topOp = -1;
int tempCount = 1;

// Function to get operator precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '=') return 0;
    return -1;
}

// Function to generate intermediate code
void generateCode(char op) {
    char op2[10], op1[10];
    strcpy(op2, operands[topOpnd--]);
    strcpy(op1, operands[topOpnd--]);
    
    printf("t%d = %s %c %s\n", tempCount, op1, op, op2);
    
    sprintf(operands[++topOpnd], "t%d", tempCount++);
}

// Function to convert infix to intermediate code
void infixToICG(char expr[]) {
    for (int i = 0; expr[i] != '\0'; i++) {
        if (isalnum(expr[i])) {  // Operand
            char temp[10] = {expr[i], '\0'};
            strcpy(operands[++topOpnd], temp);
        } 
        else {  // Operator
            while (topOp >= 0 && precedence(operators[topOp]) >= precedence(expr[i]) && expr[i] != '=') {
                generateCode(operators[topOp--]);
            }
            operators[++topOp] = expr[i];
        }
    }

    // Pop remaining operators
    while (topOp >= 0) {
        char op = operators[topOp--];
        if (op != '=') {
            generateCode(op);
        } else {
            printf("%s = t%d\n", operands[0], tempCount - 1);
        }
    }
}

int main() {
    char expr[100];
    printf("Enter an expression (without spaces): ");
    scanf("%s", expr);
    infixToICG(expr);
    return 0;
}

