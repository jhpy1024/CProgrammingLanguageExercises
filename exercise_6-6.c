#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

enum constants
{
    GETCH_BUFFER_SIZE = 1000,
    HASH_SIZE = 101,
    MAX_LINE_LENGTH = 1000,
    MAX_NUM_LINES = 1000,
    MAX_NUM_WORDS_PER_LINE = 1000,
    MAX_WORD_LENGTH = 100,
    POSSIBLE_DEFINE = 3,
    POSSIBLE_UNDEFINE = 2,
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

struct list
{
    char* name;
    char* replacement;

    struct list* next;
};

static struct list* hash_table[HASH_SIZE];

char* str_duplicate(char* str)
{
    char* duplicate = malloc(sizeof(str) + 1);

    if (duplicate == NULL)
    {
        return NULL;
    }

    strcpy(duplicate, str);
    return duplicate;
}

unsigned hash(char* str)
{
    unsigned hash_value;

    for (hash_value = 0; *str != '\0'; ++str)
    {
        hash_value = *str + 31 * hash_value;
    }

    return hash_value % HASH_SIZE;
}

struct list* lookup(char* str)
{
    for (struct list* node = hash_table[hash(str)]; node != NULL; node = node->next)
    {
        if (strcmp(str, node->name) == 0)
        {
            return node;
        }
    }

    return NULL;
}

struct list* define(char* name, char* replacement)
{
    struct list* node;
    unsigned hash_value;

    if ((node = lookup(name)) == NULL)
    {
        node = malloc(sizeof(struct list));

        if (node == NULL || (node->name = str_duplicate(name)) == NULL)
        {
            return NULL;
        }

        hash_value = hash(name);
        node->next = hash_table[hash_value];
        hash_table[hash_value] = node;
    }
    else
    {
        free(node->replacement);
    }

    if ((node->replacement = str_duplicate(replacement)) == NULL)
    {
        return NULL;
    }

    return node;
}

void undefine(char* name)
{
    unsigned hash_value = hash(name);

    struct list* node = hash_table[hash_value];
    if (node == NULL)
    {
        return;
    }

    /*
     * The first node is the one we need to remove. The for loop below
     * won't find this so we have to do it here.
     */
    if (strcmp(name, node->name) == 0)
    {
        hash_table[hash_value] = NULL;
        return;
    }

    for (; node->next != NULL; node = node->next)
    {
        if (strcmp(name, node->next->name) == 0)
        {
            node->next = node->next->next;
            return;
        }
    }
}

int get_line(char line[])
{
    int current_char = EOF;
    int index;

    for (index = 0; index < MAX_LINE_LENGTH - 1 && (current_char = getch()) != EOF && current_char != '\n'; ++index)
    {
        line[index] = current_char;
    }

    if (current_char == '\n')
    {
        line[index++] = current_char;
    }
    line[index] = '\0';

    return index;
}

int tokenize(char line[], char* words[])
{
    int line_char_index = 0;
    int word_char_index = 0;
    int word_index = 0;
    int current_char = EOF;

    while (true)
    {
        char* word = malloc(MAX_WORD_LENGTH + 1);

        while (isspace(current_char = line[line_char_index++]))
        {
            /* Skip any leading whitespace. */
        }

        /* Essentially the same as ungetch(current_char). */
        --line_char_index;
        
        while ((current_char = line[line_char_index++]) != EOF && !isspace(current_char) && word_char_index < MAX_WORD_LENGTH)
        {
            word[word_char_index++] = current_char;
        }

        word[word_char_index] = '\0';

        /* Ignore words of zero length. */
        if (word_char_index != 0)
        {
            words[word_index++] = word;
        }

        word_char_index = 0;

        if (current_char == EOF || current_char == '\n')
        {
            break;
        }
        else
        {
            --line_char_index;
        }
    }

    /*
     * Even though this is an array index (i.e., starts at zero) we don't need to add one to this
     * as word_index is post-incremented and so when the last word has been read, word_index
     * is still incremented, thus achieving the same effect as adding one here.
     */
    return word_index;
}

bool handle_possible_define(char* words[])
{
    if (strcmp(words[0], "#define") == 0)
    {
        define(words[1], words[2]);
        return true;
    }

    return false;
}

bool handle_possible_undefine(char* words[])
{
    if (strcmp(words[0], "#undef") == 0)
    {
        undefine(words[1]);
        return true;
    }

    return false;
}

int main()
{
    char line[MAX_LINE_LENGTH] = { 0 };
    char* lines[MAX_NUM_LINES];
    char* words[MAX_NUM_WORDS_PER_LINE] = { 0 };

    int num_lines = 0;

    while (get_line(line) > 0)
    {
        lines[num_lines++] = line;

        int num_words = tokenize(line, words);

        /*
         * This is set to true when we are on a line with a #define/#undef statement.
         * If we didn't do this, the following line:
         *      #define foo bar
         * would be converted to:
         *      #define bar bar
         * which is clearly not the desired behaviour.
         */
        bool should_ignore_on_this_line = false;

        switch (num_words)
        {
            /*
             * This does not (yet) support defines with multiple words
             * following the name of the macro.
             */
            case POSSIBLE_DEFINE:
                should_ignore_on_this_line = handle_possible_define(words);
                break;
            case POSSIBLE_UNDEFINE:
                should_ignore_on_this_line = handle_possible_undefine(words);
                break;
            default:
                break;
        }

        if (!should_ignore_on_this_line)
        {
            struct list* node;
            for (int i = 0; i < num_words; ++i)
            {
                if ((node = lookup(words[i])) != NULL)
                {
                    printf("%s", node->replacement);
                }
                else
                {
                    printf("%s", words[i]);
                }
            }
        }
    }

    return 0;
}
