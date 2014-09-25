#include <ctype.h>
#include <stdio.h>
#include <string.h>

int get_line(char* line, int max_line_length)
{
    int length = 0;

    while ((*line = getchar()) != '\n' && length <= max_line_length)
    {
        ++length;
        ++line;
    }

    *line = '\0';

    return length;
}

void reverse(char* str)
{
    for (char* i = str, *j = str + strlen(str) - 1; i < j; ++i, --j)
    {
        char tmp = *i;
        *i = *j;
        *j = tmp;
    }
}

void itoa(int value, char* str)
{
    char* start_of_str = str;
    int sign;

    if ((sign = value) < 0)
    {
        value *= -1;
    }

    do
    {
        *str++ = value % 10 + '0';
    }
    while ((value /= 10) > 0);

    if (sign < 0)
    {
        *str++ = '-';
    }

    *str = '\0';

    reverse(start_of_str);
}

int atoi(char* str)
{
    int value = 0;
    int sign = (*str == '-' ? -1 : 1);

    if (sign == -1)
    {
        ++str;
    }

    for (; isdigit(*str); ++str)
    {
        value = value * 10 + (*str - '0');
    }

    return value * sign;
}

int main()
{
    char* a = "-123";
    char* b = "482";

    int ia = atoi(a);
    int ib = atoi(b);

    printf("%d %d\n", ia, ib);
    return 0;
}
