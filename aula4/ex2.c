#include <stdio.h>
#include <assert.h>

void repC(int* a, int* aSize);
void swap(int* a, int* b);
void print_arr(int a[], int aSize);

int main() {
    int a[5][10] = {
        { 1, 2, 2, 2, 3, 3, 4, 5, 8, 8 },
        { 1, 2, 2, 2, 3, 3, 3, 3, 8, 8 },
        { 1, 2, 5, 4, 7, 0, 3, 9, 6, 8 },
        { 1, 1, 2, 2, 3, 3, 4, 5, 8, 8 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    int b[7] = {1, 2, 3, 2, 1, 3, 4};
    int size = 10;
    for(int i = 0; i < 5; i++) {
        repC(a[i], &size);
        printf("10 - %d\n", size);
        print_arr(a[i], size);
        size = 10;
    }
    size = 7;
    repC(b, &size);
    printf("7 - %d\n", size);
    print_arr(b, size);
}

void repC(int* a, int* aSize) {
    int comps = 0;
    int swaps = 0;
    for (int i = 0; i < *aSize - 1; i++) {
        for (int j = i + 1; j < *aSize; j++) {
            comps++;
            if (a[i] == a[j]) {
                for (int k = j; k < *aSize - 1; k++) {
                    swaps++;
                    swap(&a[k], &a[k + 1]);
                }
                j--;
                (*aSize)--;
            }
        }
    }
    printf("Comps: %d | Swaps: %d\n", comps, swaps);
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void print_arr(int a[], int aSize) {
    for(int i = 0; i < aSize; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}
