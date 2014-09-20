#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000

enum
{
    NOT_FOUND = -1
};

int strrindex(char s[], char t[])
{
    int rightmost_index = NOT_FOUND;
    int substr_index = 0;

    for (int i = 0; s[i] != '\0'; ++i)
    {
        for (int j = i, substr_index = 0; s[j] == t[substr_index]; ++j, ++substr_index)
        {
            if (substr_index == strlen(t) - 1)
            {
                rightmost_index = i;
                break;
            }
        }
    }

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

    char pattern[] = "ould";
    
    while (get_line(line, MAX_LINE_LENGTH) > 0)
    {
        if (strrindex(line, pattern) != NOT_FOUND)
        {
            puts(line);
        }
    }

    return 0;
}
