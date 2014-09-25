#include <stdio.h>
#include <string.h>

/* Assumes that s is large enough. */
/* Use of prefix to avoid conflics with strcat declared in string.h. */
void my_strcat(char* s, char* t)
{
    s = s + strlen(s);

    while ((*s++ = *t++) != '\0')
    {
        ;
    }
}

int main()
{
    char s[100] = "This ";
    char t[100] = "is a test";

    printf("\"%s\" + \"%s\"\n", s, t);
    my_strcat(s, t);
    printf("= \"%s\"\n", s);

    return 0;
}
