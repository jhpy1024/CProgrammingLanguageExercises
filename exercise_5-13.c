#include <stdio.h>
#include <string.h>

enum
{
    DEFAULT_NUM_LINES = 5,
    MAX_NUM_INPUT_LINES = 10000,
    MAX_LINE_LENGTH = 1000,
    BUFFER_SIZE = 10000
};

static char alloc_buffer[BUFFER_SIZE];
static char* next_free = alloc_buffer;

char* alloc(int n)
{
    if ((alloc_buffer + BUFFER_SIZE) - next_free >= n)
    {
        next_free += n;
        return next_free - n;
    }
    else
    {
        return NULL;
    }
}

int get_line(char line[])
{
    char current_char;

    int i;
    for (i = 0; (current_char = getchar()) != '\n'; ++i)
    {
        line[i] = current_char;
    }
    line[i] = '\0';

    return i;
}

int read_lines(char* lines[])
{
    char line[MAX_LINE_LENGTH] = { 0 };
    char* line_ptr;

    int line_length = 0;
    int num_lines = 0;

    while ((line_length = get_line(line)) > 0)
    {
        if (num_lines >= MAX_NUM_INPUT_LINES || (line_ptr = alloc(line_length)) == NULL)
        {
            return -1;
        }
        else
        {
            line[line_length] = '\0';
            strcpy(line_ptr, line);
            lines[num_lines++] = line_ptr;
        }
    }

    return num_lines;
}

int main(int argc, char* argv[])
{
    char* lines[MAX_NUM_INPUT_LINES];
    int num_lines = read_lines(lines);

    if (num_lines < DEFAULT_NUM_LINES)
    {
        printf("error: not enough lines to print.\n");
    }
    else
    {
        for (int i = num_lines - DEFAULT_NUM_LINES; i < DEFAULT_NUM_LINES; ++i)
        {
            printf("(%d) %s\n", i, lines[i]);
        }
    }

    return 0;
}
