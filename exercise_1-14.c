#include <stdio.h>

#define NUM_CATEGORIES 4
#define LINES 0
#define TABS 1
#define SPACES 2
#define CHARS 3

void print_histogram_row(const char* name, int frequency)
{
    printf("%-10s: ", name);

    for (int i = 0; i < frequency; ++i)
    {
        printf("*");
    }

    printf("\n");
}

int main()
{
    int frequencies[NUM_CATEGORIES];
    for (int i = 0; i < NUM_CATEGORIES; ++i)
    {
        frequencies[i] = 0;
    }

    char current_char = EOF;
    while ((current_char = getchar()) != EOF)
    {
        if (current_char == '\n')
        {
            ++frequencies[LINES];
        }
        else if (current_char == '\t')
        {
            ++frequencies[TABS];
        }
        else if (current_char == ' ')
        {
            ++frequencies[SPACES];
        }

        ++frequencies[CHARS];
    }

    print_histogram_row("Lines", frequencies[LINES]);
    print_histogram_row("Tabs", frequencies[TABS]);
    print_histogram_row("Spaces", frequencies[SPACES]);
    print_histogram_row("Characters", frequencies[CHARS]);

    return 0;
}
