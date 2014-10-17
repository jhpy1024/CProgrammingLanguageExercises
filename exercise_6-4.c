#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int get_word(char* word, int max_length)
{
    int current_char;
    char* word_ptr = word;

    while (isspace(current_char = getch()))
    {
        /* Skip whitespace. */
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

struct key* add_to_tree(struct key* node, char* word)
{
    int comparison;

    if (node == NULL)
    {
        node = alloc_node();
        node->word = malloc(strlen(word) + 1);
        strcpy(node->word, word);
        node->num_occurences = 1;
        node->left = NULL;
        node->right = NULL;
    }
    else if ((comparison = strcmp(word, node->word)) < 0)
    {
        node->left = add_to_tree(node->left, word);
    }
    else
    {
        node->right = add_to_tree(node->right, word);
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

void key_swap(struct key keys[], int i, int j)
{
    struct key tmp = keys[i];
    keys[i] = keys[j];
    keys[j] = tmp;
}

void sort_array(struct key keys[], int left, int right)
{
    int last;

    if (left >= right)
    {
        return;
    }

    key_swap(keys, left, (left + right) / 2);
    last = left;
    for (int i = left + 1; i <= right; ++i)
    {
        if (keys[i].num_occurences > keys[left].num_occurences)
        {
            key_swap(keys, ++last, i);
        }
    }

    key_swap(keys, left, last);
    sort_array(keys, left, last - 1);
    sort_array(keys, last + 1, right);
}

void binary_tree_to_array(struct key keys[], struct key* root)
{
    static int index = 0;

    if (root != NULL)
    {
        binary_tree_to_array(keys, root->left);
        keys[index++] = *root;
        binary_tree_to_array(keys, root->right);
    }
}

void print_words(struct key* root, int num_words)
{
    struct key keys[MAX_NUM_WORDS];
    binary_tree_to_array(keys, root);
    sort_array(keys, 0, num_words - 1);

    for (int i = 0; i < num_words; ++i)
    {
        printf("%-3d %s\n", keys[i].num_occurences, keys[i].word);
    }
}

int main()
{
    char word[MAX_WORD_LENGTH];

    struct key* root = NULL;
    int num_words = 0;

    while (get_word(word, MAX_WORD_LENGTH) != EOF)
    {
        struct key* key;
        if ((key = get_node(root, word)) == NULL)
        {
            root = add_to_tree(root, word);
            ++num_words;
        }
        else
        {
            ++(key->num_occurences);
        }
    }

    print_words(root, num_words);

    return 0;
}
