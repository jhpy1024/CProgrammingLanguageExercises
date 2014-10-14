#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

enum
{
    GETCH_BUFFER_SIZE = 1000,
    MAX_WORD_LENGTH = 100,
    MAX_NUM_OCCURENCES = 1000,
    MAX_NUM_WORDS = 10000
};

struct key
{
    char* word;
    int line_numbers[MAX_NUM_OCCURENCES];
    int num_occurences;
};

static int getch_buffer[GETCH_BUFFER_SIZE];
static int getch_index = 0;

struct key* words[MAX_NUM_WORDS];
int num_words = 0;

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

struct key* binary_search(char* word)
{
    if (num_words == 0)
    {
        return NULL;
    }

    struct key* low = words[0];
    struct key* high = words[num_words - 1];
    struct key* mid;

    int comparison;

    while (low <= high)
    {
        mid = low + (high - low) / 2;

        if ((comparison = strcmp(word, mid->word)) < 0)
        {
            high = mid - 1;
        }
        else if (comparison > 0)
        {
            low = mid + 1;
        }
        else
        {
            return mid;
        }
    }

    return NULL;
}

bool is_ignored_word(char* word)
{
    static char* ignored_words[] = 
    {
        "and",
        "the",
        "or",
        "it",
        "is",
        "a"
    };
    static int num_ignored_words = sizeof(ignored_words) / sizeof(char*);

    /*
     * As the size of the array of ignored words is so small, a binary search
     * is not necessary.
     */
    for (int i = 0; i < num_ignored_words; ++i)
    {
        if (strcmp(word, ignored_words[i]) == 0)
        {
            return true;
        }
    }

    return false;
}

int get_word(char* word, int max_length)
{
    int current_char;
    char* word_ptr = word;

    while (isspace(current_char = getch()))
    {
        /* Skip whitespace. */
        if (current_char == '\n')
        {
            break;
        }
    }

    if (current_char != EOF)
    {
        *word_ptr++ = current_char;
    }

    if (!isalnum(current_char))
    {
        *word_ptr = '\0';
        return current_char;
    }

    for (; --max_length > 0; ++word_ptr)
    {
        if (!isalnum(*word_ptr = getch()))
        {
            ungetch(*word_ptr);
            break;
        }
    }

    *word_ptr = '\0';
    return word[0];
}

void create_key(char* word)
{
    struct key* k = malloc(sizeof(struct key));

    k->word = malloc(sizeof(word));
    strcpy(k->word, word);
    k->num_occurences = 1;

    words[num_words++] = k;
}

void cleanup()
{
    for (int i = 0; i < num_words; ++i)
    {
        free(words[i]);
    }
}

int main()
{
    char word[MAX_WORD_LENGTH];

    int line_number = 1;

    while (get_word(word, MAX_WORD_LENGTH) != EOF)
    {
        if (is_ignored_word(word))
        {
            continue;
        }

        if (strcmp(word, "\n") == 0)
        {
            ++line_number;
            continue;
        }

        struct key* key;
        if ((key = binary_search(word)) == NULL)
        {
            create_key(word);
        }
        else
        {
            key->line_numbers[key->num_occurences++] = line_number;
        }
    }

    for (int i = 0; i < num_words; ++i)
    {
        struct key* key = words[i];

        for (int j = 0; j < key->num_occurences; ++j)
        {
            printf("%-5d %s\n", key->line_numbers[j], key->word);
        }
    }

    cleanup();
    return 0;
}
