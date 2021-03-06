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

    bool skipped_asterick = true;
    bool skipped_slash = true;

    char input[INPUT_BUFFER_SIZE];
    read_input(input);

    for (int i = 0; input[i] != '\0'; ++i)
    {
        char current_char = input[i];
        char next_char = (i == (INPUT_BUFFER_SIZE - 1) ? '\0' : input[i + 1]);

        if (current_char == '/' && next_char == '/' && literal_state == NOT_IN_LITERAL)
        {
            comment_state = IN_SINGLE_LINE_COMMENT;
        }
        else if (current_char == '/' && next_char == '*' && literal_state == NOT_IN_LITERAL)
        {
            comment_state = IN_MULTI_LINE_COMMENT;
        }
        else if (current_char == '*' && next_char == '/' && comment_state == IN_MULTI_LINE_COMMENT)
        {
            comment_state = NOT_IN_COMMENT;

            /* Ensure that we don't print the ending "tag" of this multi-line comment */
            skipped_asterick = false;
            skipped_slash = false;
        }
        else if (current_char == '\n' && comment_state == IN_SINGLE_LINE_COMMENT)
        {
            comment_state = NOT_IN_COMMENT;
        }
        else if (current_char == '"')
        {
            literal_state = (literal_state == NOT_IN_LITERAL ? IN_STRING_LITERAL : NOT_IN_LITERAL);
        }
        else if (current_char == '\'')
        {
            literal_state = (literal_state == NOT_IN_LITERAL ? IN_CHARACTER_LITERAL : NOT_IN_LITERAL);
        }

        if (comment_state == NOT_IN_COMMENT)
        {
            /* 
             * If this character is part of the ending of a multi-line comment then make sure
             * we don't print it.
             */
            if (current_char == '*' && !skipped_asterick)
            {
                skipped_asterick = true;
            }
            else if (current_char == '/' && !skipped_slash)
            {
                skipped_slash = true;
            }
            else
            {
                putchar(current_char);
            }
        }
    }

    return 0;
}
