#include <stdio.h>

enum ESCAPES
{
    NEW_LINE = '\n',
    TAB = '\t'
};

enum
{
    STRING_SIZE = 100
};

/* It is assumed that to is large enough to contain all of the characters in from. */
void escape(char to[], char from[])
{
    for (int i = 0, to_index = 0; from[i] != '\0'; ++i, ++to_index)
    {
        switch (from[i])
        {
            case NEW_LINE:
                to[to_index] = '\\';
                to[++to_index] = 'n';
                break;
            case TAB:
                to[to_index] = '\\';
                to[++to_index] = 't';
                break;
            default:
                to[to_index] = from[i];
                break;
        }
    }
}

int main()
{
    char original[STRING_SIZE] = "This\tis\ta\ttest\n";
    char escaped[STRING_SIZE]= { 0 };

    escape(escaped, original);

    printf("Original: %s\n", original);
    printf("Escaped : %s\n", escaped);
    return 0;
}
