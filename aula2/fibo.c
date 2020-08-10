#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "runtime/elapsed_time.h"

typedef unsigned long long u64;
typedef long double ld;
u64 p_1(int n);
u64 p_2(int n);
ld p_3(int n);
ld p_4(int n);
ld p_5(int n);

int main() {
    (void)elapsed_time();
    ld rec[40];
    ld iter[40];
    double results[40];
    for(int i = 0; i < 40; i++){
        p_1(i);
        rec[i] = elapsed_time() / i;
        (void)elapsed_time();
    }
    (void)elapsed_time();
    for(int i = 0; i < 40; i++){
        p_2(i);
        iter[i] = elapsed_time() / i;
        (void)elapsed_time();
        results[i] = rec[i] - iter[i];
        printf("Tempos:\n\tRecursivatime / i - Iterativatime/i: %f\n", results[i]);
    }
    
}

u64 p_1(int n){
    assert(n >= 0);
    if(n == 0) {
        return 0;
    }
    else if (n == 1) {
        return 1;
    }
    else{
        return 3*p_1(n-1) + 2*p_1(n-2);
    }
}

u64 p_2(int n) {
    assert(n >= 0);
    if(n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    u64 a = 0, b = 1, c = 1;
    for(int i = 2; i <= n; i++){
        c = 3*b + 2*a;
        a = b;
        b = c;
    }
    return c;
}

ld p_3(int n) {
    return ( powl(0.5 * (3 + sqrtl(17)),n) - powl(0.5 * (3 - sqrtl(17)),n))/sqrtl(17);
}

ld p_4(int n) {
    return roundl( (powl(0.5 * (3 + sqrtl(17)),n) )/sqrtl(17));
}

ld p_5(int n) {
    return floorl( (powl(0.5 * (3 + sqrtl(17)),n) )/sqrtl(17) + 0.5);
}

ld p_6(int n) {
    ld c1 = 0.24253562503633297352;
    ld c2 = 1.27019663313689157536;

    return roundl(c1 + exp(c2 * n));
}



