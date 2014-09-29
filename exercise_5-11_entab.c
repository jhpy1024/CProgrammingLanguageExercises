#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAB '\t'
#define SPACE ' '
#define NEWLINE '\n'
#define TAB_WIDTH 4

#define MAX_NUM_TABSTOPS 100

int count_num_spaces(int* current_char)
{
    int num_spaces = 1;

    while ((*current_char = getchar()) == SPACE)
    {
        ++num_spaces;
    }

    return num_spaces;
}

int get_tabstops(int argc, char* argv[], int tabstops[])
{
    for (int i = 1; i < argc; ++i)
    {
        tabstops[i - 1] = atoi(argv[i]);
    }

    return argc - 1;
}

int main(int argc, char* argv[])
{
    int current_char = EOF;
    int char_position = 0;

    bool has_args = argc > 1;

    int tabstops[MAX_NUM_TABSTOPS];
    int tabstop_index = 0;
    int num_tabstops = 0;

    if (has_args)
    {
        num_tabstops = get_tabstops(argc, argv, tabstops);
    }

    while ((current_char = getchar()) != EOF)
    {
        if (current_char == SPACE)
        {
            int num_spaces = count_num_spaces(&current_char);

            int tabstop;
            if (has_args)
            {
                tabstop = (tabstop_index == 0 ? tabstops[tabstop_index] : tabstops[tabstop_index] - tabstops[tabstop_index - 1]);
                ++tabstop_index;
            }
            else
            {
                tabstop = TAB_WIDTH;
            }

            while (num_spaces >= tabstop)
            {
                num_spaces -= tabstop;
                putchar(TAB);
                char_position += tabstop;
            }

            while (num_spaces > 0)
            {
                --num_spaces;
                putchar(SPACE);
                ++char_position;
            }
        }

        if (current_char == NEWLINE)
        {
            char_position = 0;
            putchar(NEWLINE);
        }

        if (current_char != NEWLINE && current_char != SPACE)
        {
            putchar(current_char);
            ++char_position;
        }
    }

    return 0;
}
