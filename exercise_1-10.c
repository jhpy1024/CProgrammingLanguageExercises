#include <stdio.h>

main()
{
    char current_char = EOF;
    while ((current_char = getchar()) != EOF)
    {
        if (current_char == '\t')
        {
            printf("\\t");
        }
        else if (current_char == '\b')
        {
            printf("\\b");
        }
        else if (current_char == '\\')
        {
            printf("\\\\");
        }
        else
        {
            printf("%c", current_char);
        }
    }
}
