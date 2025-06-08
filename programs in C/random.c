#include <stdio.h>
#include <time.h>

/*
  Simple LCG (Linear Congruential Generator) to produce a “random” integer
  in [0..10] without using rand()/srand(). We seed it from the current time
  so that each run produces a different sequence.
*/

/* LCG parameters for 32-bit arithmetic */
#define LCG_A 1103515245u
#define LCG_C 12345u

static unsigned int seed;

/* Update seed: seed = (seed * A + C) mod 2^32 */
unsigned int lcg_next(void) {
    seed = seed * LCG_A + LCG_C;  /* unsigned 32-bit overflow = mod 2^32 */
    return seed;
}

/* Return a number in [0..10] */
int rand_0_10(void) {
    return (int)(lcg_next() % 11u);
}

int main(void) {
    /* Use the current time as a changing seed */
    seed = (unsigned int)time(NULL);

//    printf("Using seed = %u\n\n", seed);
//    printf("Generating 10 random numbers [0..10]:\n");
//    for (int i = 0; i < 10; i++) {
//        printf("  Number %2d: %d\n", i + 1, rand_0_10());
//    }
    printf("%d",rand_0_10());

    return 0;
}
