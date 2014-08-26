#include <stdio.h>

main()
{
    /*
     * When given an invalid escape sequence, gcc gives the warning "unknown escape sequence"
     * and just prints 'p'
     */
    printf("\p");
}
