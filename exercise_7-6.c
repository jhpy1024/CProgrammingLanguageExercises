#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum 
{
    MAX_LINE_LENGTH = 1000
};

void print_load_error(char* filename)
{
    fprintf(stderr, "error occured when loading file \"%s\". Terminating.\n", filename);
    exit(EXIT_FAILURE);
}

void check_if_loaded(FILE* file, char* filename)
{
    if (file == NULL)
    {
        print_load_error(filename);
    }
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf("usage: %s file1 file2\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE* file1 = fopen(argv[1], "r");
    FILE* file2 = fopen(argv[2], "r");
    check_if_loaded(file1, argv[1]);
    check_if_loaded(file2, argv[2]);

    char file1_str[MAX_LINE_LENGTH] = { 0 };
    char file2_str[MAX_LINE_LENGTH] = { 0 };

    unsigned line_number = 0;

    while (fgets(file1_str, MAX_LINE_LENGTH, file1) != NULL && fgets(file2_str, MAX_LINE_LENGTH, file2) != NULL)
    {
        ++line_number;

        if (strcmp(file1_str, file2_str) != 0)
        {
            printf("%s (%u): %s", argv[1], line_number, file1_str);
            printf("%s (%u): %s", argv[2], line_number, file2_str);
            break;
        }
    }

    return EXIT_SUCCESS;
}
