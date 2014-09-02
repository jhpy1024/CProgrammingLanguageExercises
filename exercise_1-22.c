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

        /* If on the penultimate character. */ 
        if (char_position == FOLD_COLUMN - 1)
        {
            /* If whitespace, simply start a newline and continue from there. */
            if (is_whitespace(current_char))
            {
                putchar('\n');
                char_position = 0;
                position_in_word = NOT_IN_WORD;
            }
            else
            {
                /*
                 * Not whitespace so in a word. If position_in_word == NOT_IN_WORD then
                 * this is the first character in the word and so we set it to 1.
                 */
                if (position_in_word == NOT_IN_WORD)
                {
                    position_in_word = 1;
                }
                else
                {
                    ++position_in_word;
                }

                /*
                 * If we are on the first character in the word, don't hyphenate.
                 * Instead start the word on a newline.
                 */
                if (position_in_word == 1)
                {
                    printf("\n%c", current_char);
                }
                /* Otherwise hyphenating is fine. */
                else
                {
                    printf("-\n%c", current_char);
                }

                /* In any case we have started a newline so reset char_position to zero. */
                char_position = 0;
            }
        }
        else
        {
            /* If we encounter whitespace we are no longer in a word. */
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
