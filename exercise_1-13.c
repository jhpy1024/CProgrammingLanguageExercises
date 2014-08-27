#include <stdio.h>
#include <stdbool.h>

#define MAX_WORD_LENGTH 100

/*
 * This function checks if the line for the biggest word length has already been printed.
 * This means that lots and lots of lines are not printed. For example if the input
 * to the program is this comment, the largest word is less than 100 and so there is
 * no need to keep printing until we reach 100
 */
bool biggest_word_already_processed(int word_lengths[], int current_word_length)
{
    for (int i = current_word_length; i < MAX_WORD_LENGTH; ++i)
    {
        if (word_lengths[i] != 0)
        {
            return false;
        }
    }

    return true;
}

int main()
{
    /* The integer at word_lengths[i] is the number of words of length 'i'. */
    int word_lengths[MAX_WORD_LENGTH];
    for (int i = 0; i < MAX_WORD_LENGTH; ++i)
    {
        word_lengths[i] = 0;
    }

    char current_char = EOF;
    int current_word_length = 0; 

    while ((current_char = getchar()) != EOF)
    {
        if (current_char == ' ' || current_char == '\n' || current_char == '\t')
        {
            if (current_word_length <= MAX_WORD_LENGTH)
            {
                /* We subtract one from the length because array indices begin at zero. */
                ++word_lengths[current_word_length - 1];
                current_word_length = 0;
            }
        }
        else
        {
            ++current_word_length;
        }
    }

    for (int i = 0; i < MAX_WORD_LENGTH; ++i)
    {
        if (biggest_word_already_processed(word_lengths, i))
        {
            break;
        }

        printf("%3d: ", i + 1);

        for (int j = 0; j < word_lengths[i]; ++j)
        {
            printf("*");
        }

        printf("\n");
    }

    return 0;
}
