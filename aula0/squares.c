#include <stdio.h>
#include <math.h>

int main() {
    printf("Ate que numero?\n");
    int res = 0;
    scanf("%d", &res);
    printf( "Numero | Quadrado | Raiz\n" );
    for(int i = 0; i < res; i++){
        printf("   %d  |  %d   |   %.3f\n", i, i*i, sqrt(i));
    }
    return 0;
}