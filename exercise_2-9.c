#include <stdio.h>

unsigned bitcount(unsigned x)
{
    unsigned num = (x == 0 ? 0 : 1);

    while ((x &= (x - 1)) != 0)
    {
        ++num;
    }

    return num;
}

int main()
{
    unsigned test = 13;
    unsigned result = bitcount(test);
    printf("bitcount(%u) -> %u\n", test, result);

    return 0;
}
