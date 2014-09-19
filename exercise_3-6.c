#include <stdio.h>
#include <string.h>

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

void itoa(int n, char str[], int min_width)
{
    int index = 0;
    int sign = n;

    long long int num = n;

    if (sign < 0)
    {
        num = -num;
    }

    do
    {
        str[index++] = (num % 10) + '0';
    }
    while ((num /= 10) > 0);

    if (sign < 0)
    {
        str[index++] = '-';
    }

    if (strlen(str) < min_width)
    {
        for (int i = 0; i < strlen(str) - min_width; ++i)
        {
            str[index++] = '0';
        }
    }
    
    str[index] = '\0';

    reverse(str);
}

int main()
{
    char str[11] = { 0 };
    itoa(41200, str, 10);

    puts(str);
    return 0;
}
