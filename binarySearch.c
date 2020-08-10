#include <stdio.h>

void printArr(int* arr, int arrSize) {
    for(int i = 0; i < arrSize; i++) {
        printf(i == 0 ? "%d" : ", %d", arr[i]);
    }
    printf("\n");
}

int binaryBelongs(int* arr, int arrSize, int val) {
    printArr(arr, arrSize);
    int first = (arrSize-1) / 2;
    printf("pivot: %d\n", first);
    if(val == arr[first]) return 1;
    if(arrSize == 1) return 0;
    if(val > arr[first]) return binaryBelongs(&arr[first + 1], arrSize - first - 1, val);
    else return binaryBelongs(arr, arrSize - first - 1, val);
}

int main() {
    int seq[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    printf("1 belongs? %s\n", binaryBelongs(seq, 9, 1) ? "true" : "false");
    printf("9 belongs? %s\n", binaryBelongs(seq, 9, 9) ? "true" : "false");
    printf("6 belongs? %s\n", binaryBelongs(seq, 9, 6) ? "true" : "false");
    return 0;
}