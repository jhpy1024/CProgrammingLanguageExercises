#include <stdio.h>
#include <stdbool.h>

#define FOLD_COLUMN 30
#define NOT_IN_WORD -1

bool is_whitespace(int c)
{
    return c == ' ' || c == '\t' || c == '\n';
}

int main()
{
    int current_char = EOF;
    int char_position = 0;
    int position_in_word = NOT_IN_WORD;

    while ((current_char = getchar()) != EOF)
    {
        ++char_position;

        if (char_position == FOLD_COLUMN - 1)
        {
            if (is_whitespace(current_char))
            {
                putchar('\n');
                char_position = 0;
                position_in_word = NOT_IN_WORD;
            }
            else
            {
                if (position_in_word == NOT_IN_WORD)
                {
                    position_in_word = 1;
                }
                else
                {
                    ++position_in_word;
                }

                if (position_in_word == 1)
                {
                    printf("\n%c", current_char);
                }
                else
                {
                    printf("-\n%c", current_char);
                }
                char_position = 0;
            }
        }
        else
        {
            if (is_whitespace(current_char))
            {
                position_in_word = NOT_IN_WORD;
            }
            else if (position_in_word == NOT_IN_WORD)
            {
                position_in_word = 1;
            }
            else
            {
                ++position_in_word;
            }

            putchar(current_char);
        }
    }

    return 0;
}
