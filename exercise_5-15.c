#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SORT_NUMERICALLY "-n"
#define SORT_REVERSE "-r"
#define FOLD_CASE "-f"

enum
{
    MAX_NUM_LINES = 5000,
    BUFFER_SIZE = 10000,
    MAX_LINE_LENGTH = 1000
};

static char alloc_buffer[BUFFER_SIZE];
static char* next_free = alloc_buffer;

bool sort_reverse = false;
bool fold_case = false;

char* alloc(int n)
{
    if ((alloc_buffer + BUFFER_SIZE) - next_free >= n)
    {
        next_free += n;
        return next_free - n;
    }
    else
    {
        return NULL;
    }
}

int get_line(char line[])
{
    int current_char;
    int index = 0;

    while (index < MAX_LINE_LENGTH && (current_char = getchar()) != EOF && current_char != '\n')
    {
        line[index++] = current_char;
    }

    if (current_char == '\n')
    {
        line[index++] = current_char;
    }

    line[index] = '\0';

    return index;
}

int read_lines(char* lines[])
{
    char line[MAX_LINE_LENGTH] = { 0 };
    char* line_ptr;

    int line_length = 0;
    int num_lines = 0;

    while ((line_length = get_line(line)) > 0)
    {
        if (num_lines >= MAX_NUM_LINES || (line_ptr = alloc(line_length)) == NULL)
        {
            return -1;
        }
        else
        {
            line[line_length - 1] = '\0';
            strcpy(line_ptr, line);
            lines[num_lines++] = line_ptr;
        }
    }

    return num_lines;
}

void write_lines(char* lines[], int num_lines)
{
    for (int i = 0; i < num_lines; ++i)
    {
        puts(lines[i]);
    }
}

int numeric_cmp(char* a, char* b)
{
    double a_val = atof(a);
    double b_val = atof(b);

    if (a_val < b_val)
    {
        return (sort_reverse ? 1 : -1);
    }
    else if (a_val > b_val)
    {
        return (sort_reverse ? -1 : 1);
    }
    else
    {
        return 0;
    }
}

bool lexicographically_equal(char a, char b)
{
    return (fold_case ? (tolower(a) == tolower(b)) : (a == b));
}

int lexicographic_cmp(char* a, char* b)
{
    int index;

    for (index = 0; lexicographically_equal(a[index], b[index]); ++index)
    {
        if (a[index] == '\0')
        {
            return 0;
        }
    }

    return (sort_reverse ? b[index] - a[index] : a[index] - b[index]);
}

void swap(void* v[], int i, int j)
{
    void* tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}

void quick_sort(void* v[], int left, int right, int (*cmp)(void*, void*))
{
    int index;
    int last;

    if (left >= right)
    {
        return;
    }

    swap(v, left, (left + right) / 2);
    last = left;

    for (index = left + 1; index <= right; ++index)
    {
        if ((*cmp)(v[index], v[left]) < 0)
        {
            swap(v, ++last, index);
        }
    }

    swap(v, left, last);
    quick_sort(v, left, last - 1, cmp);
    quick_sort(v, last + 1, right, cmp);
}

int main(int argc, char* argv[])
{
    int num_lines;
    char* lines[MAX_NUM_LINES];

    bool sort_numerically = false;

    if (argc > 1)
    {
        for (int i = 1; i < argc; ++i)
        {
            if (strcmp(argv[i], SORT_NUMERICALLY) == 0)
            {
                sort_numerically = true;
            }
            else if (strcmp(argv[i], SORT_REVERSE) == 0)
            {
                sort_reverse = true;
            }
            else if (strcmp(argv[i], FOLD_CASE) == 0)
            {
                fold_case = true;
            }
        }
    }

    if ((num_lines = read_lines(lines)) >= 0)
    {
        quick_sort((void**) lines, 0, num_lines - 1,
            (int(*)(void*, void*))(sort_numerically ? numeric_cmp : lexicographic_cmp));
        write_lines(lines, num_lines);
        return 0;
    }
    else
    {
        printf("error: input too large to sort\n");
        return 1;
    }
}
