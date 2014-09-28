#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKEN_SIZE 100
#define MAX_INPUT_SIZE 1000
#define STACK_SIZE 1000

enum type
{
    ADDITION_OPERATOR = '+',
    SUBTRACTION_OPERATOR = '-',

    /*
     * I use 'x' instead of '*' as using '*' in the bash terminal passes all the files in the
     * current directory as input to the program, which is obviously not what is wanted.
     * However this behaviour can be avoided by escaping the asterick like so: '\*'.
     */
    MULTIPLICATION_OPERATOR = 'x',
    DIVISION_OPERATOR = '/',
    NUMBER = '0',
    NO_MORE_TOKENS = EOF
};

static double stack[STACK_SIZE];
static int stack_index;

void push(double value)
{
    if (stack_index == STACK_SIZE - 1)
    {
        printf("error: unable to push %g onto the stack as the stack is full\n", value);
        return;
    }

    stack[stack_index++] = value;
}

double pop()
{
    if (stack_index == 0)
    {
        printf("error: unable to pop as the stack is empty. returning 0.\n");
        return 0.0;
    }

    return stack[--stack_index];
}

int get_token(char* input, char* token)
{
    static int input_index = 0;

    while (isspace(input[input_index]))
    {
        /* Skip whitespace. */
        ++input_index;
    }

    if (input[input_index] == '\0')
    {
        return NO_MORE_TOKENS;
    }

    if (!isdigit(input[input_index]) && input[input_index] != '.')
    {
        return input[input_index++];
    }

    if (isdigit(input[input_index]))
    {
        while (isdigit(*token++ = input[input_index++]))
        {
            /* Collect integer part. */
        }

        if (input[input_index] == '.')
        {
            while (isdigit(*token++ = input[input_index++]))
            {
                /* Collect fractional part. */
            }
        }
    }

    *token = '\0';

    if (input[input_index] != EOF)
    {
        --input_index;
    }

    return NUMBER;
}

double evaluate_expression(char* input)
{
    int type;
    char token[MAX_TOKEN_SIZE];

    double tmp_operand;

    while ((type = get_token(input, token)) != NO_MORE_TOKENS)
    {
        switch (type)
        {
            case NUMBER:
                push(atof(token));
                break;
            case ADDITION_OPERATOR:
                push(pop() + pop());
                break;
            case SUBTRACTION_OPERATOR:
                tmp_operand = pop();
                push(pop() - tmp_operand);
                break;
            case MULTIPLICATION_OPERATOR:
                push(pop() * pop());
                break;
            case DIVISION_OPERATOR:
                tmp_operand = pop();
                push(pop() / tmp_operand);
                break;
            default:
                printf("unknown token: %s\n", token);
                break;
        }
    }
}

int main(int argc, char* argv[])
{
    char input[MAX_INPUT_SIZE] = { 0 };

    if (argc == 1)
    {
        puts("usage: ./exercise_5-10.out <arg1> <arg2> ...");
        return -1;
    }

    for (int i = 1; i < argc; ++i)
    {
        if (i == MAX_INPUT_SIZE - 1)
        {
            puts("error: too much input");
            break;
        }
        else
        {
            strcat(input, (i == 1 ? "" : " "));
            strcat(input, argv[i]);
        }
    }
    
    int type;
    char token[MAX_TOKEN_SIZE];

    double result = evaluate_expression(input);
    printf("%g\n", result);

    return 0;
}
