#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum
{
    NUM_LINES_TO_NEXT_PAGE = 5
};

void print_heading(char* filename, unsigned page_number)
{
    printf("[Page %u] %s\n", page_number, filename);
}

bool print_file_contents(char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        return false;
    }

    int current_char = EOF;
    while ((current_char = fgetc(file)) != EOF)
    {
        putchar(current_char);
    }

    return true;
}

void print_blank_lines()
{
    for (int i = 0; i < NUM_LINES_TO_NEXT_PAGE; ++i)
    {
        puts("");
    }
}

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        fprintf(stderr, "%s: no files specified\n", argv[0]);
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; ++i)
    {
        print_heading(argv[i], i);
        bool printed_successfully = print_file_contents(argv[i]);

        if (printed_successfully && (i != argc - 1))
        {
            print_blank_lines();
        }
    }

    return EXIT_SUCCESS;
}
