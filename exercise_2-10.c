#include <stdio.h>

int lower(int c)
{
    return (c >= 'A' && c <= 'Z' ? c + 'a' - 'A' : c);
}

int main()
{
    for (int i = 'A'; i <= 'Z'; ++i)
    {
        printf("lower(%c) -> %c\n", i, lower(i));
    }

    return 0;
}
