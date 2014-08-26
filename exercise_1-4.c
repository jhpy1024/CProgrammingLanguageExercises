#include <stdio.h>

main()
{
    float fahrenheit;
    float celsius;

    int min_temp = 0;
    int max_temp = 300;
    int temp_step = 20;

    celsius = min_temp;

    printf("Cel Fah\n");
    printf("--- ---\n");

    while (celsius <= max_temp)
    {
        fahrenheit = celsius / (5.f / 9.f) + 32.f;
        printf("%3.0f %3.0f\n", celsius, fahrenheit);
        celsius = celsius + temp_step;
    }
}
