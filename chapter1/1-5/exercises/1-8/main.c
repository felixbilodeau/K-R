#include <stdio.h>

main()
{
    int c, n_blanks;

    n_blanks = 0;
    while ((c = getchar()) != EOF)
        if (c == ' ' || c == '\t' || c == '\n')
            ++n_blanks;
    printf("%d\n", n_blanks);
}