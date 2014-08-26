#include <stdio.h>

main()
{
    float fahrenheit;
    float celsius;

    int min_temperature = 0;
    int max_temperature = 300;
    int temperature_step = 20;

    fahrenheit = min_temperature;

    printf("Fah Cels\n");
    printf("--- ------\n");

    while (fahrenheit <= max_temperature)
    {
        celsius = (5.f / 9.f) * (fahrenheit - 32.f);
        printf("%3.0f %6.1f\n", fahrenheit, celsius);
        fahrenheit = fahrenheit + temperature_step;
    }
}
