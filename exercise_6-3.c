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

    struct key* left;
    struct key* right;
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

struct key* alloc_node()
{
    return malloc(sizeof(struct key));
}

struct key* add_to_tree(struct key* node, char* word, int line_number)
{
    int comparison;

    if (node == NULL)
    {
        node = alloc_node();
        node->word = malloc(strlen(word) + 1);
        strcpy(node->word, word);
        node->num_occurences = 1;
        node->line_numbers[0] = line_number;
        node->left = NULL;
        node->right = NULL;
    }
    else if ((comparison = strcmp(word, node->word)) < 0)
    {
        node->left = add_to_tree(node->left, word, line_number);
    }
    else
    {
        node->right = add_to_tree(node->right, word, line_number);
    }

    return node;
}

struct key* get_node(struct key* root, char* word)
{
    if (root == NULL)
    {
        return NULL;
    }

    int comparison;
    if ((comparison = strcmp(word, root->word)) < 0)
    {
        return get_node(root->left, word);
    }
    else if (comparison > 0)
    {
        return get_node(root->right, word);
    }
    else
    {
        return root;
    }
}

void print_words(struct key* root)
{
    if (root != NULL)
    {
        print_words(root->left);
        for (int i = 0; i < root->num_occurences; ++i)
        {
            printf("%-3d %s\n", root->line_numbers[i], root->word);
        }
        print_words(root->right);
    }
}

int main()
{
    char word[MAX_WORD_LENGTH];

    int line_number = 1;

    struct key* node = NULL;

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
        if ((key = get_node(node, word)) == NULL)
        {
            node = add_to_tree(node, word, line_number);
        }
        else
        {
            key->line_numbers[key->num_occurences++] = line_number;
        }
    }

    print_words(node);

    return 0;
}
