#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

enum
{
    DEFAULT_NUM_LINES = 5,
    MAX_NUM_INPUT_LINES = 10000,
    MAX_LINE_LENGTH = 1000,
    BUFFER_SIZE = 10000,
    MAX_ARG_SIZE = 100
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
    int current_char;
    int index = 0;

    while (index < MAX_LINE_LENGTH && (current_char = getchar()) != EOF && current_char != '\n')
    {
        line[index++] = current_char;
    }

    if (current_char == '\n')
    {
        line[index++] = current_char;
    }

    line[index] = '\0';

    return index;
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
            line[line_length - 1] = '\0';
            strcpy(line_ptr, line);
            lines[num_lines++] = line_ptr;
        }
    }

    return num_lines;
}

void parse_args(int argc, char* argv[], int* num_lines_to_print)
{
    char arg[MAX_ARG_SIZE] = { 0 };

    for (int i = 1; i < argc; ++i)
    {
        if (argv[i][0] == '-')
        {
            if (strlen(argv[i]) >= MAX_ARG_SIZE)
            {
                printf("error: argument too large. using default value of %d\n", DEFAULT_NUM_LINES);
                *num_lines_to_print = DEFAULT_NUM_LINES;
                return;
            }

            if (!isdigit(argv[i][1]))
            {
                printf("error: non-numerical argument. using default value of %d\n", DEFAULT_NUM_LINES);
                *num_lines_to_print = DEFAULT_NUM_LINES;
                return;
            }

            int arg_index;
            for (arg_index = 1; arg_index < strlen(argv[i]); ++arg_index)
            {
                arg[arg_index - 1] = argv[i][arg_index];
            }
            arg[++arg_index] = '\0';

            break;
        }
    }

    *num_lines_to_print = atoi(arg);
}

int main(int argc, char* argv[])
{
    int num_lines_to_print;
    if (argc > 1)
    {
        parse_args(argc, argv, &num_lines_to_print);
    }
    else
    {
        num_lines_to_print = DEFAULT_NUM_LINES;
    }

    char* lines[MAX_NUM_INPUT_LINES];
    int num_lines = read_lines(lines);


    if (num_lines < num_lines_to_print)
    {
        printf("error: not enough lines to print.\n");
    }
    else
    {
        printf("num: %d\tto print: %d\n", num_lines, num_lines_to_print);
        for (int i = num_lines - num_lines_to_print; i < num_lines; ++i)
        {
            printf("(%d) %s\n", i, lines[i]);
        }
    }

    return 0;
}
