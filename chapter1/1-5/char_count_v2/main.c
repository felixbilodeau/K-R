#include <stdio.h>

/* count characters in input; 2nd version */
main()
{
    double nc;

    for (nc = 0.0f; getchar() != EOF; nc++)
        ;
    printf("%.0lf\n", nc);
}