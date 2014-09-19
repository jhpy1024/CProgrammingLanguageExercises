#include <stdio.h>
#include <string.h>
#include <limits.h>

void reverse(char s[])
{
    char tmp;

    for (int i = 0, j = strlen(s) - 1; i < j; ++i, --j)
    {
        tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
    }
}

void itoa(int n, char s[])
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
        s[index++] = (num % 10) + '0';
    }
    while ((num /= 10) > 0);

    if (sign < 0)
    {
        s[index++] = '-';
    }
    
    s[index] = '\0';

    reverse(s);
}

int main()
{
    int n = INT_MIN;
    char str[20] = { 0 };

    itoa(n, str);

    printf("%s\n", str);

    return 0;
}
