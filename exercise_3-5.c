#include <stdio.h>
#include <string.h>

enum
{
    HEXADECIMAL = 16,
    BINARY = 2
};

void reverse(char str[])
{
    char tmp = '\0';

    for (int i = 0, j = strlen(str) - 1; i < j; ++i, --j)
    {
        tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
    }
}

void itob(int num, int base, char str[])
{
    int index = 0;
    int sign = num;

    if (sign < 0)
    {
        num = -num;
    }

    do
    {
        int digit = num % base;

        if (digit >= 10)
        {
            str[index++] = (digit - 10) + 'A';
        }
        else
        {
            str[index++] = digit + '0';
        }
    }
    while ((num /= base) > 0);

    if (sign < 0)
    {
        str[index++] = '-';
    }

    str[index] = '\0';

    reverse(str);
}

int main()
{
    int num = 42;
    char str[100] = { 0 };

    for (int base = 2; base <= 16; ++base)
    {
        itob(num, base, str);
        printf("%d to base %d = %s\n", num, base, str);
    }

    return 0;
}
