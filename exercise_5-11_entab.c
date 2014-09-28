#include <stdio.h>
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

int main()
{
    int current_char = EOF;
    int char_position = 0;

    while ((current_char = getchar()) != EOF)
    {
        if (current_char == SPACE)
        {
            int num_spaces = count_num_spaces(&current_char);

            while (num_spaces >= TAB_WIDTH)
            {
                num_spaces -= TAB_WIDTH;
                putchar(TAB);
                char_position += TAB_WIDTH;
            }

            while (num_spaces > 0)
            {
                --num_spaces;
                putchar(SPACE);
                ++char_position;
            }
        }

        /*
         * We don't use an else if statement here because when counting the number
         * of spaces above, we change current_char. If we used an else if statement and current_char
         * had been changed to a newline, the code to handle that newline would not be executed.
         */
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
