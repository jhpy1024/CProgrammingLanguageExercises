#include <stdio.h>
#include <stdlib.h>

enum
{
    MAX_INPUT_LENGTH = 100
};

int main()
{
    float first_operand = 0.f;
    float second_operand = 0.f;
    char operator;

    while (scanf("%f %f %c", &first_operand, &second_operand, &operator) == 3)
    {
        switch (operator)
        {
            case '+':
                printf("\t%f\n", first_operand + second_operand);
                break;
            case '-':
                printf("\t%f\n", first_operand - second_operand);
                break;
            case '*':
                printf("\t%f\n", first_operand * second_operand);
                break;
            case '/':
                printf("\t%f\n", first_operand / second_operand);
                break;
            default:
                fprintf(stderr, "error: '%c' is an invalid operator\n", operator);
                break;
        }
    }

    return EXIT_SUCCESS;
}
