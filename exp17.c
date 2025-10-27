/*
* Program to convert NFA with ε (epsilon) transitions
* to an equivalent NFA without ε transitions
*/

#include <stdio.h>
#include <string.h>

#define MAX 20   

int n, m;                            
char sym[MAX];                      
int trans[MAX][MAX][MAX];            
int eps[MAX][MAX];                   
int eclose[MAX][MAX];                


void findClosure(int s, int x) {
    for (int i = 0; i < n; i++) {
        if (eps[x][i] && !eclose[s][i]) {   
            eclose[s][i] = 1;               
            findClosure(s, i);              
        }
    }
}

int main() {
    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of input symbols (excluding ε): ");
    scanf("%d", &m);

    printf("Enter symbols: ");
    for (int i = 0; i < m; i++)
        scanf(" %c", &sym[i]);

    
    memset(trans, 0, sizeof(trans));
    memset(eps, 0, sizeof(eps));
    memset(eclose, 0, sizeof(eclose));

    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int num, s;
            printf("\nFrom q%d with %c, number of next states: ", i, sym[j]);
            scanf("%d", &num);
            if (num > 0)
                printf("Enter next states: ");
            for (int k = 0; k < num; k++) {
                scanf("%d", &s);
                trans[i][j][s] = 1;
            }
        }
    }

    
    printf("\nEnter ε transitions (a b means q_a→q_b, -1 -1 to stop):\n");
    while (1) {
        int a, b;
        scanf("%d %d", &a, &b);
        if (a == -1 && b == -1)
            break;
        eps[a][b] = 1;
    }

    
    for (int i = 0; i < n; i++) {
        eclose[i][i] = 1;       
        findClosure(i, i);
    }

    
    printf("\nEquivalent NFA without ε-moves:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int result[MAX] = {0};

            
            for (int k = 0; k < n; k++) {
                if (eclose[i][k]) {
                    
                    for (int l = 0; l < n; l++) {
                        if (trans[k][j][l]) {
                            
                            for (int p = 0; p < n; p++) {
                                if (eclose[l][p])
                                    result[p] = 1;
                            }
                        }
                    }
                }
            }

            
            printf("From q%d with %c -> { ", i, sym[j]);
            int found = 0;
            for (int x = 0; x < n; x++) {
                if (result[x]) {
                    printf("q%d ", x);
                    found = 1;
                }
            }
            if (!found) printf("∅");
            printf("}\n");
        }
    }

    return 0;
}

