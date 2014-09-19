#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000

int strrindex(char s[], char t[])
{
    int rightmost_index = -1;
    int substr_index;

    for (int i = 0; s[i] != '\0'; ++i)
    {
        for (int j = i, substr_index = 0; t[substr_index] != '\0' && s[j] == t[substr_index]; ++j, ++substr_index)
        {
            ;
        }

        if ((substr_index > 0) && (t[substr_index] == '\0') && (i > rightmost_index))
        {
            rightmost_index = i;
        }
    }

    printf("%d\n", rightmost_index);

    return rightmost_index;
}

int get_line(char str[], int max_line_length)
{
    int current_char = EOF;
    int index = 0;

    while (--max_line_length > 0 && (current_char = getchar()) != EOF && current_char != '\n')
    {
        str[index++] = current_char;
    }

    if (current_char == '\n')
    {
        str[index++] = current_char;
    }

    str[index] = '\0';

    return index;
}

int main()
{
    char line[MAX_LINE_LENGTH] = { 0 };

    char input[] = 
        "Ah Love! could you and I with Fate conspire\nTo grasp this sorry Scheme of Things entire,\n"
        "Would not we shatter it to bits -- and then\nRe-mould it nearer to the Heart's Desire!";
    char pattern[] = "ould";
    
    while (get_line(line, MAX_LINE_LENGTH) > 0)
    {
        if (strrindex(line, pattern) >= 0)
        {
            puts(line);
        }
    }

    return 0;
}
