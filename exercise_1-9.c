#include <stdio.h>

main()
{
    char current_char = EOF;
    while ((current_char = getchar()) != EOF)
    {
        if (current_char == ' ')
        {
            /* Print a single space */
            printf(" ");

            /* Fetch all spaces and ignore them */
            while ((current_char = getchar()) == ' ')
            {
               continue;
            }
        }

        printf("%c", current_char);
    }
}
