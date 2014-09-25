#include <stdio.h>
#include <string.h>

/*
 * Copy at most n characters of string t to s; return s.
 * Pad with '\0's if t has fewer than n characters.
 *
 * Assumes that s is large enough to contain at least n characters.
 */
char* my_strncpy(char* s, char* t, int n)
{
    char* start_of_s = s;

    int padding = (strlen(t) < n ? n - strlen(t) : 0);

    for (int i = 0; (i < n) && (*t != '\0'); ++i)
    {
        *s++ = *t++;
    }

    for (int i = 0; i < padding; ++i)
    {
        *s++ = '\0';
    }

    return start_of_s;
}

/*
 * Concatenate at most n characters of string t to string s, terminate
 * s with '\0'; return s.
 */
char* my_strncat(char* s, char* t, int n)
{
    char* start_of_s = s;

    s += strlen(s);

    for (int i = 0; (i < n) && (*t != '\0'); ++i)
    {
        *s++ = *t++;
    }

    *s = '\0';

    return start_of_s;
}

/*
 * Compare at most n characters of string s to string t;
 * return <0 if s<t, 0 if s==t, or >0 if cs>ct.
 */
int my_strncmp(char* s, char* t, int n)
{
    for (int i = 0; i < n; ++i)
    {
        if (*s < *t)
        {
            return -1;
        }
        else if (*s > *t)
        {
            return 1;
        }
    }

    return 0;
}

int main()
{
    char s[] = "____ is a test";
    char t[] = "Thisss";
    puts(my_strncpy(s, t, strlen(t)));

    char u[50] = "This is a what? ";
    char v[] = "A test.";
    puts(my_strncat(u, v, strlen(v)));

    char a[] = "this";
    char b[] = "bcd";
    printf("%d\n", my_strncmp(a, b, 3));

    return 0;
}
