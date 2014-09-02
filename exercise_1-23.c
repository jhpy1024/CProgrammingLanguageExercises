#include <stdio.h>
#include <stdbool.h>

#define IN_STRING_LITERAL       0
#define IN_CHARACTER_LITERAL    1
#define NOT_IN_LITERAL          2

#define IN_SINGLE_LINE_COMMENT  3
#define IN_MULTI_LINE_COMMENT   4
#define NOT_IN_COMMENT          5

#define INPUT_BUFFER_SIZE       100000

void read_input(char* input_buffer)
{
    int index = 0;
    char current_char = EOF;

    while ((current_char = getchar()) != EOF)
    {
        if (index == INPUT_BUFFER_SIZE)
        {
            puts("This program does not support input greater than 100,000 characters in length");
            break;
        }

        input_buffer[index++] = current_char;
    }
}

int main()
{
    int literal_state = NOT_IN_LITERAL;
    int comment_state = NOT_IN_COMMENT;

    char input[INPUT_BUFFER_SIZE];
    read_input(input);

    return 0;
}
