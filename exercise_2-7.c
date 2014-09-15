#include <stdio.h>

/* 
 * Write a function invert(x, p, n) that returns x with the n bits that begin at position p
 * inverted, leaving the others unchanged.
 */
unsigned invert(unsigned x, unsigned p, unsigned n)
{
    return x ^ (~(~0 << n) << p);
}

int main()
{
    unsigned x = invert(5, 0, 3);

    /* Input          : 5 */
    /* Expected output: 2 */
    printf("%u\n", x);
    return 0;
}
