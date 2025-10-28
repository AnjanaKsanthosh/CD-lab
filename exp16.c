/*
* Program to find ε–closure of all states in a given ε–NFA
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX 20

bool eps[MAX][MAX] = {false};  
int n, t;                      


void epsilonClosure(int state, bool visited[]) {
    visited[state] = true;  
    for (int i = 0; i < n; i++) {
        if (eps[state][i] && !visited[i]) {
            epsilonClosure(i, visited); 
        }
    }
}

int main() {
    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter total number of transitions: ");
    scanf("%d", &t);

    printf("Enter transitions (q<from>#q<to>), use # for ε, -1 -1 to stop:\n");

    for (int i = 0; i < t; i++) {
        int from, to;
        char symbol;
        scanf("q%d%cq%d", &from, &symbol, &to);
        if (symbol == '#') {
            eps[from][to] = true;  
        }
    }

    printf("\nε–Closure of each state:\n");
    for (int i = 0; i < n; i++) {
        bool visited[MAX] = {false};
        epsilonClosure(i, visited);  

        printf("ε–closure(q%d) = { ", i);
        for (int j = 0; j < n; j++) {
            if (visited[j]) printf("q%d ", j);
        }
        printf("}\n");
    }

    return 0;
}

