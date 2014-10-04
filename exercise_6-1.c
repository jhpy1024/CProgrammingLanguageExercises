#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

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

bool first_char_valid(int chr)
{
    return (isalnum(chr) || chr == '_');
}

/*
 * The book is unclear on the desired behaviour of this function when 
 * the input is a string constant. Given the context of this 
 * exercise (C keyword counting program), I assume that words inside
 * string literals should be ignored.
 */
int get_word(char* word, int max_length)
{
    static bool in_string_literal = false;

    int current_char;
    char* word_ptr = word;

    while (isspace(current_char = getch()))
    {
        /* Skip whitespace. */
    }

    if (current_char == '\"')
    {
        *word_ptr = '\0';
        in_string_literal = !in_string_literal;
        return word[0];
    }
    else if (in_string_literal)
    {
        *word_ptr = '\0';
        return word[0];
    }
    else if (current_char != EOF)
    {
        *word_ptr++ = current_char;
    }

    if (!first_char_valid(current_char))
    {
        *word_ptr = '\0';
        return current_char;
    }

    for (; --max_length > 0; ++word_ptr)
    {
        if (!(isalnum(*word_ptr = getch()) || *word_ptr == '_'))
        {
            ungetch(*word_ptr);
            break;
        }
    }

    *word_ptr = '\0';
    return word[0];
}

int main()
{
    char word[MAX_WORD_LENGTH];

    while (get_word(word, MAX_WORD_LENGTH) != EOF)
    {
        if (strlen(word) > 0)
        {
            puts(word);
        }
    }

    return 0;
}
