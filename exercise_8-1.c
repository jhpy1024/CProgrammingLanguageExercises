#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void copy(int from, int to)
{
    char current_char;

    while ((read(from, &current_char, 1)) == 1)
    {
        write(to, &current_char, 1);
    }
}

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        /* Copy input to output. */
        copy(0, 1);
    }
    else
    {
        int file_descriptor;

        while (--argc > 0)
        {
            if ((file_descriptor = open(*++argv, O_RDONLY, 0)) == -1)
            {
                printf("cat: can't open %s\n", *argv);
                return EXIT_FAILURE;
            }
            else
            {
                /* Copy file to output. */
                copy(file_descriptor, 1);
                close(file_descriptor);
            }
        }
    }

    return EXIT_SUCCESS;
}
