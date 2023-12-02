#include <stdio.h>

int power(int m, int n);

/* test power function */
main()
{
    int i;

    for (i = 0; i < 10; ++i)
        printf("%d %d %d\n", i, power(2, i), power(-3, i));
    return 0;
}

/* power: raises base to n-th power; n >= 0; version 2 */
int power(int base, int n)
{
    int p;

    p = 1;
    for (p = 1; n > 0; --n)
        p = p * base;
    return p;
}