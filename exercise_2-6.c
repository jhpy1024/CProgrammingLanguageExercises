#include <stdio.h>

#define INITIAL 0
#define POSITION 0
#define NUM_BITS 3
#define REPLACEMENT 4
#define EXPECTED 4

/*
 * Write a function setbits(x, p, n, y) that returns x with the n bits that begin
 * at position p set to the rightmost n bits of y, leaving the other bits unchanged.
 */
unsigned setbits(unsigned x, int p, int n, int y)
{
    /* Rightmost n bits set to 1. */
    unsigned bitmask = ~(~0 << n);

    return ((bitmask & y) << p) | (~(bitmask << p) & x);
}

int main()
{
    unsigned x = INITIAL;
    printf("x = %u\n", x);
    x = setbits(x, POSITION, NUM_BITS, REPLACEMENT);
    printf("x = %u\n", x);
    if (x != EXPECTED)
    {
        puts("Error!");
    }
    return 0;
}
