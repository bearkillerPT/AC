#include <stdio.h>
#include <assert.h>

void print_array(int a[], int aSize);
int firstGreat(int a[], int aSize);

int main() {
    int a[3][10] = {
        {1, 9, 2, 8, 3, 4, 5, 3, 7, 2},
        {1, 7, 4, 6, 5, 2, 3, 2, 1, 0},
        {2, 2, 2, 2, 2, 2, 2, 2, 2, 2}};

    for(int i = 2; i < 12; i++) {
        print_array(a[0], i);
        printf(" expecting %d - ", i + (i-1) * i/2);
        printf(" - returns %d\n", firstGreat(a[0], i));
    }
    return 0;
}

int firstGreat(int a[], int aSize) {
    int comparations = 0;
    assert(aSize > 1);
    int i, j, currentCount;
    int maxCount = 0;
    int maxId = -1;
    for(i = 0; i < aSize; i++) {
        currentCount = 0;
        for(j = i-1; j >= 0; j--) {
            comparations++;
            if(a[i] > a[i-1]) {
                currentCount++;
            }
        }
        comparations++;
        if(currentCount > maxCount) {
            maxCount = currentCount;
            maxId = i;
        }
    }
    printf("%d comparations", comparations);
    return maxId;
}

void print_array(int a[], int aSize) {
    printf("{%d", a[0]);
    for(int i = 1; i < aSize; i++) {
        printf(", %d", a[i]);
    }
    printf("}");
}