#include <stdio.h>
#include <float.h>
#include <limits.h>

int main()
{
    printf("int  : %20d -> %-20d\n", INT_MIN, INT_MAX);
    printf("uint : %20u -> %-20u\n", 0u, UINT_MAX);
    printf("char : %20d -> %-20d\n", CHAR_MIN, CHAR_MAX);
    printf("long : %20ld -> %-20ld\n", LONG_MIN, LONG_MAX);
    printf("ulong: %20lu -> %-20lu\n", 0lu, LONG_MAX);
    printf("short: %20d -> %-20d\n", SHRT_MIN, SHRT_MAX);
    printf("float: %20.0f -> %-20.0f\n", FLT_MIN, FLT_MAX);
    return 0;
}
