#include <stdio.h>
#include <limits.h>

unsigned rightrot(unsigned x, unsigned n)
{
    return (x >> n) | (x << (sizeof(x) * CHAR_BIT - n));
}

int main()
{
    return 0;
}
