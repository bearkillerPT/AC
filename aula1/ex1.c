#include "stdio.h"

unsigned int f1 (unsigned int n);
unsigned int f2 (unsigned int n);
unsigned int f3 (unsigned int n);
unsigned int f4 (unsigned int n);
int main(){
    for(int i= 1; i < 16; i++){
        printf("%d, 1: %d, 2: %d, 3: %d, 4: %d\n", i, f1(i), f2(i), f3(i), f4(i));
    }
    
}

unsigned int f1 (unsigned int n) {
    unsigned int i, j, r = 0;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            r += 1;
    return r;
}
unsigned int f2 (unsigned int n) {
    unsigned int i, j, r = 0;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= i; j++)
            r += 1;
    return r;
}
unsigned int f3 (unsigned int n) {
    unsigned int i, j, r = 0;
    for (i = 1; i <= n; i++)
        for (j = i; j <= n; j++)
            r += j;
    return r;
}

unsigned int f4 (unsigned int n) {
    unsigned int i, j, r = 0;
    for (i = 1; i <= n; i++)
        for (j = i; j >= 1; j /= 10)
            r += i;
    return r;
}
