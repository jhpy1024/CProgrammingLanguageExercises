#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define NUM_VARS 1000

char* ignored_words[] = 
{
    "auto",
    "break",
    "case",
    "char",
    "const",
    "continue",
    "default",
    "do",
    "double",
    "else",
    "enum",
    "extern",
    "float",
    "for",
    "goto",
    "if",
    "int",
    "long",
    "register",
    "return",
    "short",
    "signed",
    "sizeof",
    "static",
    "struct",
    "switch",
    "typedef",
    "union",
    "unsigned",
    "void",
    "volatile",
    "while"
};

struct key
{
    char* word;
    int count;
};

struct tree_node
{
    char* word;
    int count;
    struct tree_node* left;
    struct tree_node* right;
};

struct key* binary_search_key(char* word, struct key* table, int num_elements)
{
    int comparison;

    struct key* low = &table[0];
    struct key* high = &table[num_elements];
    struct key* mid;

    while (low < high)
    {
        mid = low + (high - low) / 2;

        if ((comparison = strcmp(word, mid->word)) < 0)
        {
            high = mid;
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

/* 
 * Ideally I would only need one binary search function but the 
 * one above is not generic enough and I don't feel like passing
 * around function pointers for custom comparators.
 */
char* binary_search_str(char* word, char** table, int num_elements)
{
    int comparison;

    char* low = table[0];
    char* high = table[num_elements];
    char* mid;

    while (low < high)
    {
        mid = low + (high - low) / 2;

        if ((comparison = strcmp(word, mid)) < 0)
        {
            high = mid;
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
    return binary_search_str(word, ignored_words, sizeof(ignored_words) / sizeof(char*)) == NULL;
}

int main()
{
    char* word = "sibasbabsd";
    printf("%s %d\n", word, is_ignored_word(word));

    return 0;
}
