#include <stdio.h>

/* LCG constants */
#define LCG_A 1103515245u
#define LCG_C 12345u

static unsigned int seed;

/* LCG core */
unsigned int lcg_next(void) {
    seed = seed * LCG_A + LCG_C;
    return seed;
}

/* Random number in [0..10] */
int rand_0_10(void) {
    return (int)(lcg_next() % 11u);
}

int main(void) {
    /* Generate a fake "random" seed from address of a local variable */
    int dummy;
    seed = (unsigned int)(uintptr_t)&dummy;

    printf("%d", rand_0_10());
    return 0;
}
