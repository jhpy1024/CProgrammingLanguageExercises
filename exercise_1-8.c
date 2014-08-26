#include <stdio.h>

main()
{
    int num_blanks = 0;
    int num_tabs = 0;
    int num_newlines = 0;

    char current_char = EOF;
    while ((current_char = getchar()) != EOF)
    {
        if (current_char == ' ')
        {
            ++num_blanks;
        }
        else if (current_char == '\t')
        {
            ++num_tabs;
        }
        else if (current_char == '\n')
        {
            ++num_newlines;
        }
    }

    printf("Newlines\t%5d\n", num_newlines);
    printf("Blanks  \t%5d\n", num_blanks);
    printf("Tabs    \t%5d\n", num_tabs);
}
