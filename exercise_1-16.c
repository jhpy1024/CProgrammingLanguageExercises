#include <stdio.h>

#define ARRAY_EXPAND_FACTOR 2
#define INITIAL_LINE_SIZE 5

int get_array_length(char line[])
{
    return sizeof(line) / sizeof(char);
}

/* Assumes that 'to' is large enough, i.e. get_array_length(to) >= get_array_length(from) is true */
void copy_array(char from[], char to[])
{
    for (int i = 0; i < get_array_length(from); ++i)
    {
        to[i] = from[i];
    }
}

char* expand_array(char array[])
{
    /*
     * Declare this as static so that we can return a pointer to it.
     * Pointers to *local* variables cannot be returned.
     */
    static char new_array[sizeof(array) / sizeof(char) * ARRAY_EXPAND_FACTOR];

    for (int i = 0; i < get_array_length(array); ++i)
    {
        new_array[i] = array[i];
    }

    return new_array;
}

int get_line(char line[])
{
    int line_length = 0;
    char current_char = EOF;

    while ((current_char = getchar()) != '\n')
    {
        /* Increase the size of the array if necessary */
        if (get_array_length(line) < line_length)
        {
            line = expand_array(line);
        }

        line[line_length++] = current_char;
    }

    return line_length;
}

int main()
{
    int current_line_length = 0;
    int longest_line_length = 0;

    char current_line[INITIAL_LINE_SIZE];
    char longest_line[INITIAL_LINE_SIZE];

    printf("Hit RETURN at the end of each line. When finished, input an empty line.\n");

    while ((current_line_length = get_line(current_line)) > 0)
    {
        if (current_line_length > longest_line_length)
        {
            longest_line_length = current_line_length;
            copy_array(current_line, longest_line);
        }
    }

    if (longest_line_length > 0)
    {
        printf("The longest line has length %d\n", longest_line_length);
    }
    else
    {
        printf("You didn't input any lines!\n");
    }

    return 0;
}
