#include <stdio.h>

main()
{
    char current_char = EOF;
    while ((current_char = getchar()) != EOF)
    {
        if (current_char == ' ' || current_char == '\t' || current_char == '\n')
        {
            printf("\n");
        }
        else
        {
            printf("%c", current_char);
        }        
    }
}
