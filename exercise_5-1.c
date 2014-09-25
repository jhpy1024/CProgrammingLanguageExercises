#include <ctype.h>
#include <stdio.h>

#define NOT_A_NUMBER 0
#define INPUT_BUFFER_SIZE 1000

int input_buffer[INPUT_BUFFER_SIZE] = { 0 };
int buffer_index = 0;

int getch()
{
    return (buffer_index > 0 ? input_buffer[buffer_index--] : getchar());
}

void ungetch(int c)
{
    if (buffer_index < INPUT_BUFFER_SIZE)
    {
        input_buffer[++buffer_index] = c;
    }
    else
    {
        printf("error: cannot ungetch('%c') as the input buffer is full\n", c);
    }
}

int get_int(int* i)
{
    int current_char;
    int sign;

    while (isspace(current_char = getch()))
    {
        /* Skip whitespace. */
    }

    if (!isdigit(current_char) && current_char != EOF && current_char != '+' && current_char != '-')
    {
        ungetch(current_char);
        return NOT_A_NUMBER;
    }

    sign = (current_char == '-' ? -1 : 1);

    if (current_char == '+' || current_char == '-')
    {
        int tmp = current_char;

        if (!isdigit(current_char = getch()))
        {
            /* This is not a sign so put it back into the input buffer. */
            ungetch(tmp);
            ungetch(current_char);
            return NOT_A_NUMBER;
        }

        ungetch(current_char);
    }

    for (*i = 0; isdigit(current_char); current_char = getch())
    {
        *i = *i * 10 + (current_char - '0');
    }

    *i *= sign;

    if (current_char != EOF)
    {
        ungetch(current_char);
    }

    return current_char;
}

int main()
{
    int a;

    if (get_int(&a))
    {
        printf("%d\n", a);
    }
    else
    {
        printf("error occured when reading integer\n");
    }
    return 0;
}
