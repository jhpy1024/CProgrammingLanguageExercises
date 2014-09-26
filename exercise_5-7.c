#include <stdio.h>
#include <string.h>

#define MAX_NUM_LINES 5000
#define MAX_LINE_LENGTH 1000
#define ALLOC_BUFFER_SIZE 10000

char* lines[MAX_NUM_LINES];

static char alloc_buffer[ALLOC_BUFFER_SIZE];
static char* alloc_next_free = alloc_buffer;

char* alloc(int n)
{
    if (alloc_buffer + ALLOC_BUFFER_SIZE - alloc_next_free >= n)
    {
        alloc_next_free += n;
        return alloc_next_free - n;
    }
    else
    {
        return 0;
    }
}

void afree(char* p)
{
    if (p >= alloc_buffer && p < alloc_buffer + ALLOC_BUFFER_SIZE)
    {
        alloc_next_free = p;
    }
}

void swap(char* v[], int i, int j)
{
    char* tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}

void quick_sort(char* v[], int left, int right)
{
    int last;

    if (left >= right)
    {
        return;
    }

    swap(v, left, (left + right) / 2);

    last = left;

    for (int i = left + 1; i <= right; ++i)
    {
        if (strcmp(v[i], v[left]) < 0)
        {
            swap(v, ++last, i);
        }
    }

    swap(v, left, last);
    quick_sort(v, left, last - 1);
    quick_sort(v, last + 1, right);
}

int get_line(char* line, int max_line_length)
{
    int current_char;
    int length = 0;

    for (; length < max_line_length - 1 && (current_char = getchar()) != EOF && current_char != '\n'; ++length)
    {
        line[length] = current_char;
    }

    if (current_char == '\n')
    {
        line[length++] = current_char;
    }

    line[length] = '\0';

    return length;
}

int read_lines(char* plines[], int max_lines, char* buffer)
{
    int length;
    int num_lines = 0;

    char line[MAX_LINE_LENGTH];
    char* ptr = buffer + strlen(buffer);

    while ((length = get_line(line, MAX_LINE_LENGTH)) > 0)
    {
        if (num_lines >= max_lines || (strlen(buffer) + length) > ALLOC_BUFFER_SIZE)
        {
            return -1;
        }
        else
        {
            /* Delete newline. */
            line[length - 1] = '\0';

            strcpy(ptr, line);
            lines[num_lines++] = ptr;
            ptr += length;
        }
    }

    return num_lines;
}

void write_lines(char* plines[], int num_lines)
{
    for (int i = 0; i < num_lines; ++i)
    {
        printf("%s\n", plines[i]);
    }
}

/*
 * Using alloc                 : 0.002s
 * Using array supplied by main: 0.002s
 *
 * Conclusion: No measurable difference in performance (without using a more precise method).
 */
int main()
{
    int num_lines;
    char store[ALLOC_BUFFER_SIZE] = { 0 };

    if ((num_lines = read_lines(lines, MAX_NUM_LINES, store)) >= 0)
    {
        quick_sort(lines, 0, num_lines - 1);
        write_lines(lines, num_lines);

        return 0;
    }
    else
    {
        puts("error: input too big to sort");
        return 1;
    }

    return 0;
}
