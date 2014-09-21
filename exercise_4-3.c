#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_TOKEN_SIZE 100
#define MAX_STACK_DEPTH 100
#define INPUT_BUFFER_SIZE 100

#define NUMBER_TYPE '0'

#define ADDITION_OPERATOR '+'
#define SUBTRACTION_OPERATOR '-'
#define MULTIPLICATION_OPERATOR '*'
#define DIVISION_OPERATOR '/'
#define MODULUS_OPERATOR '%'
#define END_OF_EXPRESSION '\n'

int stack_index = 0;
double stack[MAX_STACK_DEPTH];

char input_buffer[INPUT_BUFFER_SIZE];
int input_buffer_index = 0;

void push(double value);
double pop();

int get_token(char token[]);

int getch();
void ungetch(int c);

int main()
{
    int type;
    double tmp_operand;

    char token[MAX_TOKEN_SIZE];

    while ((type = get_token(token)) != EOF)
    {
        switch (type)
        {
            case NUMBER_TYPE:
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
                if ((tmp_operand = pop()) != 0.0)
                {
                    push(pop() / tmp_operand);
                }
                else
                {
                    printf("error: division by zero\n");
                }
                break;
            case MODULUS_OPERATOR:
                if ((tmp_operand = pop()) != 0.0)
                {
                    push((int) pop() % (int) tmp_operand);
                }
                else
                {
                    printf("error: division by zero (via modulus)\n");
                }
                break;
            case END_OF_EXPRESSION:
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknown token %s\n", token);
                break;
        }
    }

    return 0;
}

void push(double value)
{
    if (stack_index < MAX_STACK_DEPTH)
    {
        stack[stack_index++] = value;
    }
    else
    {
        printf("error: stack full, can't push %g\n", value);
    }
}

double pop()
{
    if (stack_index > 0)
    {
        return stack[--stack_index];
    }
    else
    {
        printf("error: stack empty so can't pop\n");
        return 0.0;
    }
}

int get_token(char token[])
{
    int current_char;
    int token_index = 0;

    while ((token[0] = current_char = getch()) == ' ' || current_char == '\t')
    {
        /* Skip whitespace. */
    }

    token[1] = '\0';

    if (!isdigit(current_char) && current_char != '.')
    {
        if (current_char == '-' && isdigit(current_char = getch()))
        {
            ungetch(current_char);
        }
        else
        {
            return current_char;
        }
    }

    if (isdigit(current_char))
    {
        while (isdigit(token[++token_index] = current_char = getch()))
        {
            /* Get integer part. */
        }
    }

    if (current_char == '.')
    {
        while (isdigit(token[++token_index] = current_char = getch()))
        {
            /* Get fractional part. */
        }
    }

    token[token_index] = '\0';

    if (current_char != EOF)
    {
        ungetch(current_char);
    }

    return NUMBER_TYPE;
}

int getch()
{
    return (input_buffer_index > 0 ? input_buffer[--input_buffer_index] : getchar());
}

void ungetch(int c)
{
    if (input_buffer_index >= INPUT_BUFFER_SIZE)
    {
        printf("error: cannot ungetch(%d) as the buffer is full\n", c);
    }
    else
    {
        input_buffer[input_buffer_index++] = c;
    }
}
