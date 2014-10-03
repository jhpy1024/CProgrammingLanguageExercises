#include <ctype.h>
#include <stdio.h>

enum
{
    GETCH_BUFFER_SIZE = 1000,
    MAX_WORD_LENGTH = 100
};

static int getch_buffer[GETCH_BUFFER_SIZE];
static int getch_index = 0;

int getch()
{
    return (getch_index > 0 ? getch_buffer[--getch_index] : getchar());
}

void ungetch(int chr)
{
    if (getch_index >= GETCH_BUFFER_SIZE)
    {
        printf("error: cannot ungetch(%c) as the buffer is full\n", chr);
    }
    else
    {
        getch_buffer[getch_index++] = chr;
    }
}

int get_word(char* word, int max_length)
{
    int current_char;
    char* word_cpy = word;

    while (isspace(current_char = getch()))
    {
        /* Skip whitespace. */
    }

    if (current_char != EOF)
    {
        *word_cpy++ = current_char;
    }

    if (!isalpha(current_char))
    {
        *word_cpy = '\0';
        return current_char;
    }

    for (; --max_length > 0; ++word_cpy)
    {
        if (!isalnum(*word_cpy = getch()))
        {
            ungetch(*word_cpy);
            break;
        }
    }

    *word_cpy = '\0';
    return word[0];
}

int main()
{
    char word[MAX_WORD_LENGTH];

    while (get_word(word, MAX_WORD_LENGTH) != EOF)
    {
        puts(word);
    }

    return 0;
}
