#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

enum
{
    MAX_LINE_LENGTH = 80,
    START_NON_GRAPHIC = 0,
    END_NON_GRAPHIC = 31,
    TAB = '\t',
    NEWLINE = '\n',
    CARRIAGE_RETURN = 13
};

/*
 * Prints non-graphic characters in hexadecimal.
 *
 * Characters with ASCII codes 0 to 31 (excluding 9 (tab), 10 (newline), and 13 (carriage return)) are
 * considered to be non-graphic characters.
 *
 * Breaks a line when its length >= MAX_LINE_LENGTH.
 */
int main()
{
    unsigned line_length = 0;

    int current_char = EOF;
    while ((current_char = getchar()) != EOF)
    {
        if (line_length >= MAX_LINE_LENGTH)
        {
            putchar('\n');
            line_length = 0;

            /* Don't print any whitespace at the start of the newline. */
            if (!isspace(current_char))
            {
                putchar(current_char);
            }
        }
        else
        {
            if (current_char >= START_NON_GRAPHIC && current_char <= END_NON_GRAPHIC
                    && current_char != TAB && current_char != NEWLINE && current_char != CARRIAGE_RETURN)
            {
                printf("0x%X", current_char);
            }
            else
            {
                putchar(current_char);
            }

            ++line_length;
        }
    }

    return EXIT_SUCCESS;
}
