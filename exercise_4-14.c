#include <stdio.h>

#define swap(t, x, y) \
    t tmp = x; \
    x = y; \
    y = tmp;

int main()
{
    char x = 'a';
    char y = 'b';

    printf("%c %c\n", x, y);
    swap(char, x, y);
    printf("%c %c\n", x, y);

    return 0;
}
