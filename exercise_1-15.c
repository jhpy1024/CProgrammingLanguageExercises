#include <stdio.h>

#define MIN_TEMPERATURE 0
#define MAX_TEMPERATURE 300
#define TEMPERATURE_STEP 20

float celsius_to_fahrenheit(float celsius)
{
    return celsius * 1.8f + 32.f;
}

int main()
{
    float celsius;
    float fahrenheit;

    for (celsius = MIN_TEMPERATURE; celsius <= MAX_TEMPERATURE; celsius += TEMPERATURE_STEP)
    {
        fahrenheit = celsius_to_fahrenheit(celsius);

        printf("%-3.0f - %3.0f\n", celsius, fahrenheit);
    }

    return 0;
}
