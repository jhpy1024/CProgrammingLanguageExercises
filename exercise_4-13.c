#include <stdio.h>
#include <string.h>

void reverse_impl(char str[], int i, int j)
{
    if (i < j)
    {
        char tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;

        reverse_impl(str, i + 1, j - 1);
    }
}

void reverse(char str[])
{
    reverse_impl(str, 0, strlen(str) - 1);
}

int main()
{
    char str[] = "This is a test!";
    reverse(str);
    puts(str);
    return 0;
}
