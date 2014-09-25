#include <ctype.h>
#include <stdio.h>

#define NOT_A_NUMBER 0
#define INPUT_BUFFER_SIZE 1000

int input_buffer[INPUT_BUFFER_SIZE] = { 0 };
int buffer_index = 0;

int getch()
{
    return (buffer_index > 0 ? input_buffer[--buffer_index] : getchar());
}

void ungetch(int c)
{
    if (buffer_index < INPUT_BUFFER_SIZE)
    {
        input_buffer[buffer_index++] = c;
    }
    else
    {
        printf("error: cannot ungetch('%c') as the input buffer is full\n", c);
    }
}

int get_float(float* f)
{
    int current_char;
    int sign;

    int fractional_power = 1;

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

    for (*f = 0.f; isdigit(current_char = getch());)
    {
        *f = *f * 10.f + (current_char - '0');
    }

    if (current_char == '.')
    {
        current_char = getch();
        for (; isdigit(current_char); current_char = getch())
        {
            *f = *f * 10.f + (current_char - '0');
            fractional_power *= 10;
        }
    }

    *f /= fractional_power;
    *f *= sign;

    if (current_char != EOF)
    {
        ungetch(current_char);
    }

    return current_char;
}

int main()
{
    float a;

    if (get_float(&a))
    {
        printf("%g\n", a);
    }
    else
    {
        printf("error occured when reading float\n");
    }

    return 0;
}
