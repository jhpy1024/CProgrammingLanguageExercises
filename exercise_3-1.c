#include <stdio.h>

/* Time taken to find an element in an array of size 30: 0.001s */
int binary_search_1(int x, int v[], int n)
{
    int low;
    int high;
    int mid;

    low = 0;
    high = n - 1;

    while (low <= high)
    {
        mid = (low + high) / 2;

        if (x < v[mid])
        {
            high = mid - 1;
        }
        else if (x > v[mid])
        {
            low = mid + 1;
        }
        else
        {
            return mid;
        }
    }

    return -1;
}

/* Time taken to find an element in an array of size 30: 0.002s */
int binary_search_2(int x, int v[], int n)
{
    int low;
    int high;
    int mid;

    low = 0;
    high = n - 1;

    while (low <= high)
    {
        mid = (low + high) / 2;

        if (x < v[mid])
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    return (v[mid] == x ? mid : -1);
}

int main()
{
    int v[] = { 3, 4, 5, 14, 22, 35, 36, 39, 41, 43, 44, 45, 48, 50, 51, 56, 60, 63, 71, 74, 77, 81, 83, 84, 89, 91, 93, 98, 99, 100 };

    printf("%d\n", binary_search_2(43, v, 30));

    return 0;
}
