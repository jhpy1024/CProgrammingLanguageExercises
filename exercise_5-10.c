#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX_INPUT_SIZE 1000
#define STACK_SIZE 1000

enum type
{
    ADDITION_OPERATOR = '+',
    SUBTRACTION_OPERATOR = '-',
    MULTIPLICATION_OPERATOR = '*',
    DIVISION_OPERATOR = '/'
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

int get_token(char* input)
{
    
}

double evaluate_expression(char* input)
{

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

    double result = evaluate_expression(input);
    printf("\t%g\n", result);

    return 0;
}
