#include <stdio.h>

/* Lines with length >= to this will be printed */
#define MIN_LINE_LENGTH 80
#define INITIAL_BUFFER_SIZE 1024
#define BUFFER_GROW_FACTOR 2

int get_array_size(char array[])
{
    return sizeof(array) / sizeof(char);
}

char* expand_array(char array[])
{
    static char new_array[sizeof(array) / sizeof(char) * BUFFER_GROW_FACTOR];

    for (int i = 0; i < get_array_size(array); ++i)
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
        if (get_array_size(line) < line_length)
        {
            line = expand_array(line);
        }

        line[line_length++] = current_char;
    }

    line[line_length] = '\0';

    return line_length;
}

int main()
{
    int current_line_length = 0;
    char current_line[INITIAL_BUFFER_SIZE];
    
    while ((current_line_length = get_line(current_line)) > 0)
    {
        if (current_line_length >= MIN_LINE_LENGTH)
        {
            printf("%-4d %s\n", current_line_length, current_line);
        }
    }

    return 0;
}
