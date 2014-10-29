#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define TO_UPPER "upper"
#define TO_LOWER "lower"

/*
 * If the program name contains TO_UPPER, convert all input to uppercase.
 * If the program name contains TO_LOWER, convert all input to lowercase.
 */
int main(int argc, char* argv[])
{
    char* prog_name = argv[0];

    int (*conversion_func)(int);

    if (strstr(prog_name, TO_UPPER) != NULL)
    {
        conversion_func = toupper;
    }
    else if (strstr(prog_name, TO_LOWER) != NULL)
    {
        conversion_func = tolower;
    }
    else
    {
        fprintf(stderr, "program name must contain \"%s\" or \"%s\"\n", TO_UPPER, TO_LOWER);
        exit(EXIT_FAILURE);
    }

    int current_char = EOF;
    while ((current_char = getchar()) != EOF)
    {
        putchar(conversion_func(current_char));
    }

    return EXIT_SUCCESS;
}
