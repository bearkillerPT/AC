#include <stdio.h>
#include <assert.h>

int motzkin(unsigned int n);
int motzkinDin(unsigned int n);
int multsrec;
int multsdin;

int main() {
    FILE* fp = fopen("ex1.csv", "w");
    fprintf(fp, "n, Motzkin Recursiva,	Nº Multiplicacoes,	Motzkin Dinamica, Nº Multiplicacoes\n");
    int motzrec;
    int motzdin;
    for(int i = 0; i <= 25; i++) {
        multsdin = 0;
        multsrec = 0;
        motzdin = motzkinDin(i);
        motzrec = motzkin(i);
        printf("%d, %d, %d, %d, %d\n", i, motzrec, multsrec, motzdin, multsdin);
        fprintf(fp, "%d, %d, %d, %d, %d\n", i, motzrec, multsrec, motzdin, multsdin);
    }
    return 0; 
}

int motzkin(unsigned int n) {
    if(n <= 1) {
        return 1;
    }
    int soma = motzkin(n-1);
    for(int k = 0; k <= n-2; k++) {
        soma += motzkin(k) * motzkin(n-2-k);
        multsrec++;
    } 
    return soma;
}

int motzkinDin(unsigned int n) {
    int motz[n+1];
    motz[0] = 1;
    if(n>0) motz[1] = 1;
    if(n>1) {
        for(int i = 2; i < n+1; i++) {
            motz[i] = motz[i-1];
            for(int j = 0; j <= i-2; j++) {
                motz[i] += motz[j] * motz[i-2-j];
                multsdin++;
            }
        }
    }
    return motz[n];
}