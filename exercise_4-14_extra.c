#include <stdio.h>

#define SWAP(x, y) \
    char tmp = x; \
    x = y; \
    y = tmp;

void swap(char* x, char* y)
{
    char tmp = *x;
    *x = *y;
    *y = tmp;
}

/*
 * Comparing performance between a macro and a function for swapping two variables.
 * Why? Because I was curious to see whether there would be any performance difference.
 * Turns out there isn't (any measurable difference).
 * --------------------------------------------------------------------------------
 * Macro   : 0.002s
 * Function: 0.002s
 */
int main()
{
    char x = 'a';
    char y = 'b';

    printf("%c %c\n", x, y);
    SWAP(x, y);
    printf("%c %c\n", x, y);

    return 0;
}
