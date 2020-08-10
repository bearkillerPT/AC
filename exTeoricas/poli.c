#include <stdio.h>
int poli(int *a, int aSize, int x);
int poliRec(int *a, int aSize, int x);
int power(int base, int exponent);
int poliMults;
int poliRecMults;
int main() {
    int a[6][6] = {{1,1,1,1,1,1},
                   {1,1,1,1,1,1},
                   {1,1,1,1,1,1},
                   {1,1,1,1,1,1},
                   {1,1,1,1,1,1},
                   {1,1,1,1,1,1}};
    int x = 2;
    int polires = 0;
    int poliRecres = 0;
    for(int i = 0; i < 6; i++) {
        poliMults = 0;
        poliRecMults = 0;
        polires = poli(a[i], i+1, x);
        poliRecres = poliRec(a[i], i+1, x);
        printf("Din: %d - %d |Rec: %d - %d\n", polires, poliMults, poliRecres, poliRecMults);
    }
}

int poli(int *a, int aSize, int x) {
    int result = 0;
    int exponent = 1;
    for(int i = 0; i < aSize; i++) {
        result += a[i] * exponent; //*power(x, i);
        exponent *= x;
        poliMults += 2;
    }
    return result;
}


int poliRec(int *a, int aSize, int x) {
    if(aSize == 1) return 1;
    poliRecMults++;
    int res = *a;
    a++;
    aSize--;
    return res += x * poliRec(a, aSize, x);
}

int power(int base, int exponent) {
    if(exponent == 0) return 1;
    else if(exponent == 1) return base;
    int res = base;
    for(int i = 1; i < exponent; i++) {
        res *= base;
        poliMults++;
    }
    return res;
}