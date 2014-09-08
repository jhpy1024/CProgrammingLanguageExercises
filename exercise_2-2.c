#include <stdio.h>

#define LIMIT 100

int main()
{
    char c = EOF;
    char input[LIMIT];
    int i;
    for (i = 0; i < LIMIT - 1; ++i)
    {
        if ((c = getchar()) != '\n')
        {
            if (c != EOF)
            {
                input[i] = c;
                putchar(c);
            }
            else
            {
                break;
            }
        }
    }
    input[i] = '\0';
    return 0;
}
