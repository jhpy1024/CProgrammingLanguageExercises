#include <stdio.h>

#define TAB_WIDTH 4

int get_tab_size(int char_index)
{
    while ((char_index % TAB_WIDTH) != 0)
    {
        ++char_index;
    }

    return char_index;
}

int main()
{
    char current_char = EOF;
    int char_index = 0;

    while ((current_char = getchar()) != EOF)
    {
        ++char_index;

        if (current_char == '\t')
        {
            for (; char_index < get_tab_size(char_index); ++char_index)
            {
                putchar(' ');
            }
        }
        else if (current_char == '\n')
        {
            char_index = 0;
            putchar('\n');
        }
        else
        {
            putchar(current_char);
        }
    }

    return 0;
}
