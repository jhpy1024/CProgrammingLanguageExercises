#include <stdio.h>

/* Each sub-array has 13 elements as the first element is not used. This is so indices intuitively start at 1. */
static char days_per_month[][13] = 
{
    { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
    { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 } /* Leap year. */
};

int is_leap_year(int year)
{
    return (year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0);
}

int day_of_year(int year, int month, int day)
{
    int is_leap = is_leap_year(year);

    if (day > days_per_month[is_leap][month])
    {
        printf("error: invalid day %d. there are %d days in month %d in the year %d\n", day, days_per_month[is_leap][month], month, year);
        return -1;
    }

    char* first_month = &days_per_month[is_leap][1];
    char* month_ptr;

    for (month_ptr = first_month; month_ptr < first_month + month; ++month_ptr)
    {
        day += *month_ptr;
    }

    return day;
}

void month_day(int year, int day_of_the_year, int* month, int* day)
{
    if (day_of_the_year > 365)
    {
        printf("error: invalid day of the year %d. there are 365 days in a year\n", day_of_the_year);
    }

    int is_leap = is_leap_year(year);

    char* first_month = &days_per_month[is_leap][1];
    char* month_ptr;

    for (month_ptr = first_month; day_of_the_year > *month_ptr; ++month_ptr)
    {
        day_of_the_year -= *month_ptr;
    }

    *month = month_ptr - first_month;
    *day = day_of_the_year;
}

int main()
{
    int month;
    int day;

    int year = 2014;
    int doy = 32;

    month_day(year, doy, &month, &day);

    printf("%d/365 (%d) -> %d-%d-%d\n", doy, year, year, month, day);

    return 0;
}
