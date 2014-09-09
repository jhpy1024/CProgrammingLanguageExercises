#include <stdio.h>
#include <stdbool.h>

bool string_contains_char(char str[], char c)
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

/* Deletes each character in str1 that matches any character in str2. */
void squeeze(char str1[], char str2[])
{
    int overwrite_index = 0;

    for (int i = 0; str1[i] != '\0'; ++i)
    {
        if (!string_contains_char(str2, str1[i]))
        {
            str1[overwrite_index++] = str1[i];
        }
    }

    str1[overwrite_index] = '\0';
}

int main()
{
    char test_str[] = "This is a test lol!";
    char to_remove[] = "aeiou";
    
    printf("Before: %s\n", test_str);

    squeeze(test_str, to_remove);

    printf("After : %s\n", test_str);
    return 0;
}
