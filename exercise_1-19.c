#include <stdio.h>

void reverse_string(char string[], int string_length)
{
    int head = 0;

    /*
     * We subtract 2 from the string length because:
     * (a) array indices start at zero 
     * (b) we don't want to reverse the position of the null character
     */
    int tail = string_length - 2;

    while (head < tail)
    {
        char tmp = string[head];

        string[head] = string[tail];
        string[tail] = tmp;

        ++head;
        --tail;
    }
}

int main()
{
    char str[] = "This is a string!!";
    int string_length = sizeof(str) / sizeof(char);

    printf("Original: %s\n", str);
    reverse_string(str, string_length);
    printf("Reversed: %s\n", str);
    return 0;
}
