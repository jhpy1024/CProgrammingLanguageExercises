#include <math.h>
#include <stdio.h>

void itoa_impl(int number, char str[], int index)
{
    if (number < 0)
    {
        str[0] = '-';
        number = -number;

        /* Increase the index so we don't overwrite the negative sign. */
        ++index;
    }

    if (number / 10 != 0)
    {
        itoa_impl(number / 10, str, index - 1);
    }

    str[index] = number % 10 + '0';
}

void itoa(int number, char str[])
{
    /* Ensure that the argument to log10 >= 0. */
    itoa_impl(number, str, (int) log10(number > 0 ? number : -number));
}

int main()
{
    int number = -913;
    char str[10] = { 0 };

    itoa(number, str);

    puts(str);

    return 0;
}
