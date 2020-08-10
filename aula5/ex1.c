#include <stdio.h>
#include <assert.h>

int t1(int n);
int t2(int n);
int t3(int n);

int t1Calls;
int t2Calls;
int t3Calls;

int main() {
    int t1V, t2V, t3V;
    FILE* fp = fopen("ex1.csv", "w");
    fprintf(fp, "n,	T1(n),	Nº de Chamadas Recursivas,	T2(n),	Nº de Chamadas Recursivas,	T3(n),	Nº de Chamadas Recursivas\n");
    for(int n = 0; n < 59; n++) {
        t1Calls = 0;
        t2Calls = 0;
        t3Calls = 0;
        t1V = t1(n);
        t2V = t2(n);
        t3V = t3(n);
        fprintf(fp, "%d, %d, %d, %d, %d, %d, %d\n", n, t1V, t1Calls, t2V, t2Calls, t3V, t3Calls);
    }
    fprintf(fp, "\n");
}

int t1(int n) {
    assert(n >= 0);
    if(n==0) return 0;
    t1Calls++;
    return  t1(n/3) + n;
}

int t2(int n) {
    assert(n >= 0);
    if(n==0 || n==1 || n==2) return n;
    t2Calls += 2;
    return t2(n/3) + t2((n+2)/3) + n;
}

int t3(int n) {
    assert(n >= 0);
    if(n==0 || n==1 || n==2) return n;
    t3Calls++;
    if(n%3 == 0) return 2 * t3(n/3) + n;
    t3Calls++;
    return t3(n/3) + t3((n+2)/3) + n;
}
