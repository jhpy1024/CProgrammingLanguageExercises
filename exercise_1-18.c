#include <stdio.h>
#include <stdbool.h>

#define EXPANSION_FACTOR 2
#define INITIAL_BUFFER_SIZE 1024

int get_line_length(char line[])
{
    return sizeof(line) / sizeof(char);
}

char* expand_array(char array[])
{
    static char new_array[sizeof(array) / sizeof(char) * EXPANSION_FACTOR];

    for (int i = 0; i < get_line_length(array); ++i)
    {
        new_array[i] = array[i];
    }

    return new_array;
}

int get_line(char line[])
{
    char current_char = EOF;
    int index = 0;

    while ((current_char = getchar()) != '\n')
    {
        line[index++] = current_char;
    }

    line[index] = '\0';

    return index;
}

/*
 * Checks if there exists characters that are not whitespace in the
 * substring from char_index until the end of the string (i.e. '\0')
 */
bool has_more_non_whitespace_chars(char line[], int char_index)
{
    for (; line[char_index] != '\0'; ++char_index)
    {
        if (line[char_index] != ' ' && line[char_index] != '\t')
        {
            return true;
        }
    }

    return false;
}

void remove_trailing_whitespace(char line[])
{
    for (int i = 0; line[i] != '\0'; ++i)
    {
        if (!has_more_non_whitespace_chars(line, i))
        {
            line[i] = '\0';
            return;
        }
    }
}

void print_showing_whitespace(char string[])
{
    for (int i = 0; string[i] != '\0'; ++i)
    {
        if (string[i] == ' ')
        {
            printf("<space>");
        }
        else if (string[i] == '\t')
        {
            printf("<tab>");
        }
        else
        {
            printf("%c", string[i]);
        }
    }

    printf("\n");
}

int main()
{
    char line[INITIAL_BUFFER_SIZE];

    while (get_line(line) > 0)
    {
        printf("Original: ");
        print_showing_whitespace(line);

        remove_trailing_whitespace(line);

        printf("Trimmed: ");
        print_showing_whitespace(line);
    }

    return 0;
}
