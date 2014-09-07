#include <stdio.h>
#include <stdbool.h>

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

int literal_state;
int comment_state;
int current_char;
int next_char;

void init_input_buffer(int input[])
{
    for (int i = 0; i < MAX_INPUT_LENGTH; ++i)
    {
        input[i] = '\0';
    }
}

void read_input(int input[])
{
    int current_char = EOF;
    int index = 0;

    while ((current_char = getchar()) != EOF)
    {
        input[index++] = current_char;
    }
}

void print_error(char message[])
{
    printf("[error] %s\n", message);
}

void print_error_if(char message[], bool condition)
{
    if (condition)
    {
        print_error(message);
    }
}

void print_error_ln(int line, int char_number, char message[])
{
    printf("[error @ line %d, character %d] %s\n", line, char_number, message);
}

void print_error_ln_if(int line, int char_number, char message[], bool condition)
{
    if (condition)
    {
        print_error_ln(line, char_number, message);
    }
}

bool in_code()
{
    return literal_state == NOT_IN_LITERAL && comment_state == NOT_IN_COMMENT;
}

bool in_comment()
{
    return comment_state == NOT_IN_COMMENT;
}

bool in_single_line_comment()
{
    return comment_state == IN_SINGLE_LINE_COMMENT;
}

bool in_multi_line_comment()
{
    return comment_state == IN_MULTI_LINE_COMMENT;
}

bool in_string()
{
    return comment_state == IN_STRING;
}

bool in_character()
{
    return comment_state == IN_CHARACTER;
}

bool start_of_single_line_comment()
{
    return current_char == '/' && next_char == '/';
}

bool start_of_multi_line_comment()
{
    return current_char == '/' && next_char == '*';
}

bool end_of_multi_line_comment()
{
    return current_char == '*' && next_char == '/';
}

int main()
{
    int input[MAX_INPUT_LENGTH];
    init_input_buffer(input);
    read_input(input);

    literal_state = NOT_IN_LITERAL;
    comment_state = NOT_IN_COMMENT;
    current_char = '\0';
    next_char = '\0';

    int line_number = 1;
    int char_number = 0;

    int num_parens = 0;
    int num_brackets = 0;
    int num_braces = 0;

    for (int i = 0; input[i] != '\0' && i < MAX_INPUT_LENGTH; ++i)
    {
        current_char = input[i];
        next_char = ((i == MAX_INPUT_LENGTH - 1) ? '\0' : input[i + 1]);

        ++char_number;

        if (current_char == '\n')
        {
            ++line_number;
            char_number = 0;
            continue;
        }

        if (in_code())
        {
            if (start_of_single_line_comment())
            {
                comment_state = IN_SINGLE_LINE_COMMENT;
            }
            else if (start_of_multi_line_comment())
            {
                comment_state = IN_MULTI_LINE_COMMENT;
            }
            else if (current_char == OPEN_PARENTHESIS)
            {
                ++num_parens;
            }
            else if (current_char == CLOSE_PARENTHESIS)
            {
                --num_parens;
                print_error_ln_if(line_number, char_number, "too many closing parentheses", num_parens < 0);
            }
            else if (current_char == OPEN_BRACE)
            {
                ++num_braces;
            }
            else if (current_char == CLOSE_BRACE)
            {
                --num_braces;
                print_error_ln_if(line_number, char_number, "too many closing braces", num_braces < 0);
            }
            else if (current_char == OPEN_BRACKET)
            {
                ++num_brackets;
            }
            else if (current_char == CLOSE_BRACKET)
            {
                --num_brackets;
                print_error_ln_if(line_number, char_number, "too many closing brackets", num_brackets < 0);
            }
        }
        else if (in_single_line_comment())
        {
            if (current_char == '\n')
            {
                comment_state = NOT_IN_COMMENT;
            }
        }
        else if (in_multi_line_comment())
        {
            if (end_of_multi_line_comment())
            {
                comment_state = NOT_IN_COMMENT;
            }
        }
        else if (in_string())
        {
            /* TODO: Support escaped double-quote ("\"") */
            if (current_char == '"')
            {
                literal_state = NOT_IN_LITERAL;
            }
        }
        else if (in_character())
        {
            /* TODO: Support escaped single-quote ('\'') */
            if (current_char == '\'')
            {
                literal_state = NOT_IN_LITERAL;
            }
        }
    }

    print_error_if("parentheses are not balanced", num_parens != 0);
    print_error_if("braces are not balanced", num_braces != 0);
    print_error_if("brackets are not balanced", num_brackets != 0);

    return 0;
}
