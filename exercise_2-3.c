#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_INPUT_SIZE 1000

bool is_hex_string_valid(char string[])
{
    unsigned length;

    for (length = 0; string[length] != '\0'; ++length)
    {
        /* do nothing */
        ;
    }

    for (int i = 0; i < length; ++i)
    {
        int char_lower = tolower(string[i]);

        /* In a valid hex string an x/X can only exist at index 1. */
        if (char_lower == 'x')
        {
            if (i != 1)
            {
                return false;
            }
        }
        else if (!(isdigit(string[i]) || (char_lower >= 'a' && char_lower <= 'f')))
        {
            printf("'%c' is not a valid character, make sure you didn't enter any whitespace (tab, space, newline).", char_lower);
            return false;
        }
    }

    return true;
}

int hex_char_to_dec(int c)
{
    if (isdigit(c))
    {
        return c;
    }
    else
    {
        return 10 + (tolower(c) - 'a');
    }
}

int htoi(char string[])
{
    if (!is_hex_string_valid(string))
    {
        return -1;
    }

    /* We don't want to include the hex prefix (if it exists) so we start at index 2 to skip it. */
    int index = (tolower(string[1]) == 'x' ? 2 : 0);
    int result = 0;

    for (; string[index] != '\0'; ++index)
    {
        result = 16 * result + hex_char_to_dec(string[index]);
    }

    return result;
}

int main()
{
    puts("Enter a hexidecimal string and then press the end-of-file key (CTRL-D on UNIX)");
    char input[MAX_INPUT_SIZE];
    int current_char = EOF;
    int index = 0;

    for (index; index < MAX_INPUT_SIZE - 1 && (current_char = getchar()) != EOF; ++index)
    {
        input[index] = current_char;
    }
    input[index] = '\0';

    printf(" => %d\n", htoi(input));
    return 0;
}
