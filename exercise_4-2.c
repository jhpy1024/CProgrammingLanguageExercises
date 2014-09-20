#include <math.h>
#include <ctype.h>
#include <stdio.h>

/* Assumes that the string is correctly formed. */
double atof(char s[])
{
    double value = 0.0;
    double fractional_power = 1.0;

    int sign = 1;
    int str_index = 0;

    double power_of_ten = 0.0;

    for (str_index = 0; isspace(s[str_index]); ++str_index)
    {
        /* Skip any whitespace. */
    }

    sign = (s[str_index] == '-' ? -1 : 1);

    if (s[str_index] == '-' || s[str_index] == '+')
    {
        ++str_index;
    }

    for (value = 0.0; isdigit(s[str_index]); ++str_index)
    {
        value = value * 10.0 + (s[str_index] - '0');
    }

    /* TODO: Remove duplication of this code. */
    if (s[str_index] == 'e' || s[str_index] == 'E')
    {
        ++str_index;

        int power_of_ten_sign = (s[str_index] == '-' ? -1 : 1);
        if (s[str_index] == '+' || s[str_index] == '-')
        {
            ++str_index;
        }

        for (power_of_ten = 0.0; isdigit(s[str_index]); ++str_index)
        {
            power_of_ten = power_of_ten * 10.0 + (s[str_index] - '0');
        }

        power_of_ten *= power_of_ten_sign;
    }

    if (s[str_index] == '.')
    {
        ++str_index;

        for (fractional_power = 1.0; isdigit(s[str_index]); ++str_index)
        {
            value = value * 10.0 + (s[str_index] - '0');
            fractional_power *= 10.0;
        }
    }

    if (s[str_index] == 'e' || s[str_index] == 'E')
    {
        ++str_index;

        int power_of_ten_sign = (s[str_index] == '-' ? -1 : 1);
        if (s[str_index] == '+' || s[str_index] == '-')
        {
            ++str_index;
        }

        for (power_of_ten = 0.0; isdigit(s[str_index]); ++str_index)
        {
            power_of_ten = power_of_ten * 10.0 + (s[str_index] - '0');
        }

        power_of_ten *= power_of_ten_sign;
    }

    return (sign * value / fractional_power) * pow(10.0, power_of_ten);
}

int main()
{
    printf("%f\n", atof("0.2e3"));
    printf("%f\n", atof("1.04"));
    printf("%f\n", atof("0e41"));
    printf("%f\n", atof("7e2"));
    printf("%f\n", atof("1e-1"));

    return 0;
}
