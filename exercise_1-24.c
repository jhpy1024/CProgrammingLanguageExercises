#include <stdio.h>

#define OPEN_PARENTHESIS    '('
#define CLOSE_PARENTHESIS   ')'
#define OPEN_BRACKET        '['
#define CLOSE_BRACKET       ']'
#define OPEN_BRACE          '{'
#define CLOSE_BRACE         '}'

#define IN_STRING       0
#define IN_CHARACTER    1
#define NOT_IN_LITERAL  2

#define IN_SINGLE_LINE_COMMENT  0
#define IN_MULTI_LINE_COMMENT   1
#define NOT_IN_COMMENT          2

#define MAX_INPUT_LENGTH 100000

void read_input(int input[])
{
    int current_char = EOF;
    int index = 0;

    while ((current_char = getchar()) != EOF)
    {
        input[index++] = current_char;
    }
}

void print_error(int line, char message[])
{
    printf("[line %d] %s\n", line, message);
}

int main()
{
    int input[MAX_INPUT_LENGTH];
    read_input(input);

    int literal_state = NOT_IN_LITERAL;
    int comment_state = NOT_IN_COMMENT;

    int line_number = 1;

    int num_parens = 0;
    int num_brackets = 0;
    int num_braces = 0;

    for (int i = 0; input[i] != '\0' && i < MAX_INPUT_LENGTH; ++i)
    {
    }

    return 0;
}
