#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASH_SIZE 101

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
    struct list* node = hash_table[hash(name)];
    if (node == NULL)
    {
        return;
    }

    for (; node->next != NULL; node = node->next)
    {
        if (strcmp(name, node->next->name) == 0)
        {
            node->next = node->next->next;
        }
    }
}

int main()
{
    define("foo", "bar");
    printf("%s\n", lookup("foo") == NULL ? "not exist" : "exist");
    printf("%s\n", lookup("foo") == NULL ? "not exist" : "exist");
    undefine("foo");
    printf("%s\n", lookup("foo") == NULL ? "not exist" : "exist");
    return 0;
}
