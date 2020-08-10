#include <stdio.h>
#include <math.h>

int xtonR(int x, unsigned int n);
int xtohnR(int x, unsigned int n);

int main() {
    int x = 2;
    int n = 10;
    printf("%d ^ %d = %d\n", x, n, xtohnR(x, n));
}

int xtonR(int x, unsigned int n) {
    if(n == 0) return 1;
    return x * xtonR(x, n-1);
}

int xtohnR(int x, unsigned int n) {
    if(n == 0) return 1;
    if(n == 1) return x;
    return xtohnR(x, floor(n/2)) * xtohnR(x, ceil(n-1));
}