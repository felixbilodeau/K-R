#include <stdio.h>

/* print Celsius-Fahrenheit table
    for celsius = 0, 20, ..., 300; floating-point version */
main()
{
    float celsius, fahr;
    int lower, upper, step;

    lower = 0;      /* lower limit of temperature table */
    upper = 300;    /* upper limit */
    step = 20;      /* step size */

    printf("|-----|--------|\n");
    printf("|   C |      F |\n");
    printf("|-----|--------|\n");

    celsius = lower;
    while (celsius <= upper) {
        fahr = (9.0f / 5.0f) * celsius + 32.0f;
        printf("| %3.0f | %6.1f |\n", celsius, fahr);
        celsius = celsius + step;
    }
    printf("|-----|--------|\n");
}