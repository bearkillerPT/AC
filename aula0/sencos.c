#include <stdio.h>
#include <math.h>

int main() {
    int min = 0, max = 0, step = 0;
    printf("Angulo inicial: \n");
    scanf("%d", &min);
    printf("Angulo Final\n");
    scanf("%d", &max);
    printf("Step: \n");
    scanf("%d", &step);
    printf( "Numero | Seno | Cossseno | Verify(1)\n" );
    double sen = 0, coss = 0;
    for(int i = min; i <= max; i += step){
        sen = sin((i * 3.14156)/180.0);
        coss = cos((i * 3.14156)/180.0);
        printf("   %d  |  %f  |  %.3f | %.3f\n", i, sen, coss, pow(sen, 2) + pow(coss, 2));
    }
    return 0;
}