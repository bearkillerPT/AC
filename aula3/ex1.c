#include <stdio.h>

int find_dups(int a[], int aSize);
int main() {

    int array[10][10] = {
      {3, 3, 3, 3, 3, 3, 3, 3, 3, 3}, {4, 3, 3, 3, 3, 3, 3, 3, 3, 3},
      {4, 5, 3, 3, 3, 3, 3, 3, 3, 3}, {4, 5, 1, 3, 3, 3, 3, 3, 3, 3},
      {4, 5, 1, 2, 6, 3, 3, 3, 3, 3}, {4, 5, 1, 2, 6, 8, 3, 3, 3, 3},
      {4, 5, 1, 2, 6, 8, 7, 9, 3, 3}, {4, 5, 1, 2, 3, 3, 3, 3, 3, 3},
      {4, 5, 1, 2, 6, 8, 7, 3, 3, 3}, {4, 5, 1, 2, 6, 8, 7, 9, 3, 0}};
    for(int i = 0; i< 10; i++){
        printf("%d -> %d\n", i, find_dups(array[i], 10));
    }
    
}

int find_dups(int a[], int aSize) {
   int repetitions = 0;
   for(int i = 1; i < aSize; i++) {
      if(a[i] == a[i-1]) repetitions++;
   }
   return repetitions;
}

