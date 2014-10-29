#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void minprintf(char* format, ...)
{
    va_list args;

    char* string_value;
    int int_value;
    double double_value;
    int char_value;
    void* pointer_value;

    va_start(args, format);

    char* cursor;
    for (cursor = format; *cursor; ++cursor)
    {
        if (*cursor != '%')
        {
            putchar(*cursor);
            continue;
        }

        switch (*++cursor)
        {
            case 'd':
            case 'i':
                int_value = va_arg(args, int);
                printf("%d", int_value);
                break;
            case 'c':
                char_value = va_arg(args, int);
                putchar(char_value);
                break;
            case 'p':
                pointer_value = va_arg(args, void*);
                printf("%p", pointer_value);
                break;
            case 'e':
                double_value = va_arg(args, double);
                printf("%e", double_value);
                break;
            case 'E':
                double_value = va_arg(args, double);
                printf("%E", double_value);
                break;
            case 'o':
                int_value = va_arg(args, int);
                printf("%o", int_value);
                break;
            case 'x':
                int_value = va_arg(args, int);
                printf("%x", int_value);
                break;
            case 'X':
                int_value = va_arg(args, int);
                printf("%X", int_value);
                break;
            case 'a':
                double_value = va_arg(args, double);
                printf("%a", double_value);
                break;
            case 'A':
                double_value = va_arg(args, double);
                printf("%A", double_value);
                break;
            case 'g':
                double_value = va_arg(args, double);
                printf("%g", double_value);
                break;
            case 'G':
                double_value = va_arg(args, double);
                printf("%G", double_value);
                break;
            case 'f':
                double_value = va_arg(args, double);
                printf("%f", double_value);
                break;
            case 's':
                for (string_value = va_arg(args, char*); *string_value; ++string_value)
                {
                    putchar(*string_value);
                }
                break;
            default:
                putchar(*cursor);
                break;
        }

        va_end(args);
    }
}
