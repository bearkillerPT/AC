#include <stdio.h>

int main() {
    int ects[] = {8.0,	6.0,	6.0,	8.0,	6.0,	8.0,	8.0,	6.0,	8.0,	8.0};
    int notas[] = {17,  13,    15,     19,     12,     17,     11,     14,     16,       16};
    double media = 0;
    int ectsSum = 0;
    for(int i = 0; i < 10; i++) {
        media += ects[i] * notas[i];
        ectsSum += ects[i];
    }
    media /= ectsSum;
    printf("Media boye: %f", media);
}