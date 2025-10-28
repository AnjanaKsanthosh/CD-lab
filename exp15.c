#include<stdio.h>
#include<string.h>
#define LEN 10
#define SIZE 50

struct {
    char res[LEN];
    char op;
    char opnd1[LEN];
    char opnd2[LEN];
} tac[SIZE];  // To store three-address code

int num_instr = 0;

void read_three_address_code() {
    printf("Enter the number of instructions:\n");
    scanf("%d", &num_instr);
    printf("Enter each instruction (e.g. a = b + c):\n");

    for (int i = 0; i < num_instr; i++) {
        scanf("%s = %s %c %s", tac[i].res, tac[i].opnd1, &tac[i].op, tac[i].opnd2);
    }
}

const char* get_instr(char op) {
    switch (op) {
        case '+': return "ADD";
        case '-': return "SUB";
        case '*': return "MUL";
        case '/': return "DIV";
        default:  return "UNKNOWN";
    }
}

void generate_target_code() {
    for (int i = 0; i < num_instr; i++) {
        printf("MOV AX,%s\n", tac[i].opnd1);
        printf("%s AX,%s\n", get_instr(tac[i].op), tac[i].opnd2);
        printf("MOV %s,AX\n", tac[i].res);
    }
}

int main() {
    read_three_address_code();
    printf("\nEquivalent Assembly Code:\n");
    generate_target_code();
    return 0;
}
