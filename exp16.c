/*
* Program to find ε–closure of all states in a given ε–NFA
*/

#include <stdio.h>
#include <stdbool.h>

#define MAX 20

bool eps[MAX][MAX] = {false};  // ε–transition table
int n, t;                      // Number of states and transitions

// Recursive function to find ε–closure of a state
void epsilonClosure(int state, bool visited[]) {
    visited[state] = true;  // Mark current state as visited
    for (int i = 0; i < n; i++) {
        if (eps[state][i] && !visited[i]) {
            epsilonClosure(i, visited); // Follow ε–transition
        }
    }
}

int main() {
    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter total number of transitions: ");
    scanf("%d", &t);

    printf("Enter transitions in the form:\n");
    printf("From_State Symbol To_State (Example: 0 # 1)\n");

    for (int i = 0; i < t; i++) {
        int from, to;
        char symbol;
        scanf("%d %c %d", &from, &symbol, &to);
        if (symbol == '#') {
            eps[from][to] = true;  // Store ε–transition
        }
    }

    printf("\nε–Closure of each state:\n");
    for (int i = 0; i < n; i++) {
        bool visited[MAX] = {false};
        epsilonClosure(i, visited);  // Find closure of q_i

        printf("ε–closure(q%d) = { ", i);
        for (int j = 0; j < n; j++) {
            if (visited[j]) printf("q%d ", j);
        }
        printf("}\n");
    }

    return 0;
}
