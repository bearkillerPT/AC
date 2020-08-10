#include <stdio.h>

void print_array(char* s, int* a, int size);
void cum_sum(int* a, int* b, int size);

int main() {
    int a[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    print_array("a", a, 12);
    int b[12];
    cum_sum(a, b, 12);
    print_array("b", b, 12);
}

void print_array(char* s, int* a, int size) {
    printf("%s :", s);
    for(int i = 0; i < size; i++) {
        printf("%d ", a[i]);
    }
    puts("");
}

void cum_sum(int* a, int* b, int size) {
    int c = 0;
    for(int i = 0; i < size; i++) {
        c += a[i];
        b[i] = c;
    }
}