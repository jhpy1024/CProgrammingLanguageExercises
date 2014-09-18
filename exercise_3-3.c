#include <stdio.h>
#include <stdbool.h>

enum
{
    NO_OPERAND = '\0',
    OPERATOR = '-'
};

enum state
{
    NONE,
    IN_EXPANSION
};

bool is_operand_valid(char c)
{
    return (c >= '0' && c <= '9')
        || (c >= 'a' && c <= 'z')
        || (c >= 'A' && c <= 'Z');
}

/* Assumes that expanded is large enough. */
void expand(char shorthand[], char expanded[])
{
    char left_operand = NO_OPERAND;
    char right_operand = NO_OPERAND;

    int state = NONE;

    int expanded_index = 0;

    for (int i = 0; shorthand[i] != '\0'; ++i)
    {
        char current_char = shorthand[i];

        switch (state)
        {
            case NONE:
                if (is_operand_valid(current_char))
                {
                    left_operand = current_char;
                }
                else if (current_char == OPERATOR)
                {
                    if (left_operand != NO_OPERAND)
                    {
                        state = IN_EXPANSION;
                    }
                    else
                    {
                        expanded[expanded_index++] = current_char;
                    }
                }
                break;
            case IN_EXPANSION:
                if (is_operand_valid(current_char))
                {
                    right_operand = current_char;
                    state = NONE;

                    for (char c = left_operand; c <= right_operand; ++c)
                    {
                        expanded[expanded_index++] = c;
                    }

                    left_operand = NO_OPERAND;
                    right_operand = NO_OPERAND;
                }
                break;
            default:
                break;
        }
    }
    
    expanded[expanded_index] = '\0';
}

int main()
{
    char shorthand[] = "-a-z0-9-";
    char expanded[1000] = { 0 };

    expand(shorthand, expanded);

    printf("%s\n", expanded);
    return 0;
}
