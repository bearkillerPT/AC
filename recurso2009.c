#include <stdio.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void rodarSeq(int* seq, int seqSize) {
    for(int i = 0; i < seqSize; i++) {
        printf("%d > %d ?\n", seq[i],i+1);
        if(seq[i] > i+1) {
            for(int j = i; j < seqSize-1; j++) {
                printf("swap(%d, %d)\n", seq[j], seq[j+1]);
                swap(&seq[j], &seq[j+1]);
            }
            i--;
        }
    }
}

int main() {
    int seq[] = {5, 6, 1, 2, 3, 4};
    int seqSize = 6;
    rodarSeq(seq, seqSize);
    for(int i = 0; i < seqSize; i++) {
        printf(i == 0 ? "%d" : ", %d", seq[i]);
    }
    printf("\n");
}