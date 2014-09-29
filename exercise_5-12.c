#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define TAB '\t'
#define SPACE ' '
#define NEWLINE '\n'
#define TAB_WIDTH 4

int count_num_spaces(int* current_char)
{
    int num_spaces = 1;

    while ((*current_char = getchar()) == SPACE)
    {
        ++num_spaces;
    }

    return num_spaces;
}

void parse_args(int argc, char* argv[], int* tab_width, int* start_col)
{
    *tab_width = 0;
    *start_col = 0;

    for (int i = 1; i < argc; ++i)
    {
        if (argv[i][0] == '+')
        {
            for (int j = 1; j < strlen(argv[i]); ++j)
            {
                *tab_width = 10 * *tab_width + (argv[i][j] - '0');
            }
        }
        else if (argv[i][0] == '-')
        {
            for (int j = 1; j < strlen(argv[i]); ++j)
            {
                *start_col = 10 * *start_col + (argv[i][j] - '0');
            }
        }
    }
}

int main(int argc, char* argv[])
{
    int current_char = EOF;
    int char_position = 0;

    int tab_width;
    int start_col;

    if (argc > 1)
    {
        parse_args(argc, argv, &tab_width, &start_col);

        printf("tab width: %d\tstart col: %d\n", tab_width, start_col);
    }
    else
    {
        tab_width = TAB_WIDTH;
        start_col = 0;
    }

    while ((current_char = getchar()) != EOF)
    {
        if (current_char == SPACE)
        {
            int num_spaces = count_num_spaces(&current_char);

            if (char_position <= start_col)
            {
                while (num_spaces >= tab_width)
                {
                    num_spaces -= tab_width;
                    putchar(TAB);
                    char_position += tab_width;
                }

                while (num_spaces > 0)
                {
                    --num_spaces;
                    putchar(SPACE);
                    ++char_position;
                }
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
