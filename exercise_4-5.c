#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

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
#define MULTI_CHAR_OPERATOR 'm'

int stack_index = 0;
double stack[MAX_STACK_DEPTH];

char input_buffer[INPUT_BUFFER_SIZE];
int input_buffer_index = 0;

const char SIN_OPERATOR[] = "sin";
const char EXP_OPERATOR[] = "exp";
const char POW_OPERATOR[] = "pow";

void push(double value);
double pop();
double peek();
void print_peek();
void duplicate_top();
void swap_top();
void clear_stack();

int get_token(char token[]);

int getch();
void ungetch(int c);

bool str_equal(const char s[], const char t[]);

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
            case MULTI_CHAR_OPERATOR:
                if (str_equal(token, SIN_OPERATOR))
                {
                    push(sin(pop()));
                }
                else if (str_equal(token, EXP_OPERATOR))
                {
                    push(exp(pop()));
                }
                else if (str_equal(token, POW_OPERATOR))
                {
                    tmp_operand = pop();
                    push(pow(pop(), tmp_operand));
                }
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
        /* If the next character is a digit then this is a negative number, not an operator. */
        if (current_char == '-' && isdigit(current_char = getch()))
        {
            ungetch(current_char);
        }
        else
        {
            while (isalpha(current_char = getch()))
            {
                token[++token_index] = current_char;
            }
            if (current_char != EOF)
            {
                ungetch(current_char);
            }
            token[++token_index] = '\0';
            return MULTI_CHAR_OPERATOR;
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

double peek()
{
    if (stack_index >= 0)
    {
        return stack[stack_index];
    }
    else
    {
        printf("error: cannot peek as stack is empty\n");
        return 0.0;
    }
}

void print_peek()
{
    printf("%.8g\n", peek());
}

void duplicate_top()
{
    push(peek());
}

void swap_top()
{
    double second = pop();
    double first = pop();

    push(second);
    push(first);
}

void clear_stack()
{
    for (int i = 0; i < MAX_STACK_DEPTH; ++i)
    {
        stack[MAX_STACK_DEPTH] = 0.0;
    }

    stack_index = 0;
}

bool str_equal(const char s[], const char t[])
{
    if (strlen(s) != strlen(t))
    {
        return false;
    }

    for (int i = 0; i < strlen(s); ++i)
    {
        if (s[i] != t[i])
        {
            return false;
        }
    }

    return true;
}
