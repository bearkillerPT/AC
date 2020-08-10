#include <stdio.h>
#include <assert.h>

int progR1(int a[], int aSize);
int main() {
    int a[10][10] = {
        {1, 3, 4, 5, 5, 6, 7, 7, 8, 9}, {1, 2, 4, 5, 5, 6, 7, 8, 8, 9},
        {1, 2, 3, 6, 8, 8, 8, 9, 9, 9}, {1, 2, 3, 4, 6, 7, 7, 8, 8, 9},
        {1, 2, 3, 4, 5, 7, 7, 8, 8, 9}, {1, 2, 3, 4, 5, 6, 8, 8, 9, 9},
        {1, 2, 3, 4, 5, 6, 7, 9, 9, 9}, {1, 2, 3, 4, 5, 6, 7, 8, 8, 9},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 9}, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
    };

    for(int i = 0; i < 10; i++) {
        printf("%d %d\n", i, progR1(a[i], 10));
    }

}

int progR1(int a[], int aSize) {
    assert(aSize > 1);
    for(int i = 1; i < aSize; i++) {
        if(a[i] - a[i-1] != 1) return 0;
    }
    return 1;
}






