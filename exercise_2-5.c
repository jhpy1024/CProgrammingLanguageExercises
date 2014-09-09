#include <stdio.h>
#include <stdbool.h>

#define NO_COMMON_CHARACTER -1

bool string_has_char(char str[], char c)
{
    for (int i = 0; str[i] != '\0'; ++i)
    {
        if (str[i] == c)
        {
            return true;
        }
    }
    
    return false;
}

int any(char str1[], char str2[])
{
    for (int i = 0; str1[i] != '\0'; ++i)
    {
        if (string_has_char(str2, str1[i]))
        {
            return i;
        }
    }

    return NO_COMMON_CHARACTER;
}

int main()
{
    /* Should return 3. */
    printf("any(\"baloon\", \"dog\") -> %d\n", any("baloon", "dog"));
    return 0;
}
