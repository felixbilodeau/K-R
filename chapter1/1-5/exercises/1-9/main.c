#include <stdio.h>

main()
{
    int current, last;

    for (last = 0; (current = getchar()) != EOF; last = current)
        if (last != ' ' || current != ' ')
            putchar(current);
}