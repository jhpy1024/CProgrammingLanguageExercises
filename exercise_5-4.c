#include <stdio.h>
#include <string.h>

enum result
{
    NOT_FOUND = 0,
    FOUND = 1
};

int strend(char* s, char* t)
{
    /* If the size of s is less than the size of t then t cannot occur at the end of s. */
    if (strlen(s) < strlen(t))
    {
        return NOT_FOUND;
    }

    /* If s is equal to t then we say that t occurs at the end of s. */
    if (strcmp(s, t) == 0)
    {
        return FOUND;
    }

    char* start_of_t = t;

    s += strlen(s) - 1;
    t += strlen(t) - 1;

    for (; t >= start_of_t; --s, --t)
    {
        if (*s != *t)
        {
            return NOT_FOUND;
        }
    }

    return FOUND;
}

int main()
{
    char* s = "This";
    char* t = "is";

    printf("%d\n", strend(s, t));

    return 0;
}
