#include <stdio.h>

#define MAX_WORD 15
#define HIST_HEIGHT 25

/* calculate a power of the base */
int my_pow(int base, int exponent)
{
    unsigned int i;
    int result = 1;
    for (i = 0; i < exponent; ++i)
        result = result * base;
    return result;
}

/* print a histogram of word lengths of input */
main()
{
    /* Declare our variables */
    unsigned int nlengths[MAX_WORD];
    unsigned int overflow, i, max_length;
    int c, j;
    unsigned char num_digits;
    char *verb, *word;

    /* set our initial values */
    for (i = 0; i < MAX_WORD; ++i)
        nlengths[i] = 0;
    overflow = 0;

    /* go through each character */
    i = 0;
    while ((c = getchar()) != EOF) {
        /* if it's a word-ending char */
        if (c == ' ' || c == '\n' || c == '\t' || c == '.') {
            /* if we were in a word */
            if (i > 0) {
                /* record the word length */
                if (i > MAX_WORD)
                    ++overflow;
                else
                    ++nlengths[i - 1];
                /* reset the accumulator */
                i = 0;
            }
        }
        /* we have a normal char */
        else {
            ++i;
        }
    }

    /* Check if we are still in a word at the end */
    if (i > 0)
        /* if we are, record the length */
        if (i > MAX_WORD)
            ++overflow;
        else
            ++nlengths[i - 1];

    /* determine the max length */
    max_length = 0;
    for (i = 0; i < MAX_WORD; ++i)
        if (nlengths[i] > max_length)
            max_length = nlengths[i];

    /* normalize the histogram to the height */
    for (i = 0; i < MAX_WORD; ++i)
        nlengths[i] = nlengths[i] * HIST_HEIGHT / max_length;

    putchar('\n');

    /* print the histogram bars */

    /* loop from max_length to 1 */
    for (j = HIST_HEIGHT; j > 0; --j) {
        /* for each length, check if we need to print it */
        for (i = 0; i < MAX_WORD; ++i)
            if (nlengths[i] >= j)
                printf(" # ");
            else
                printf("   ");
        putchar('\n');
    }

    /* print the labels */
    for (i = 0; i < MAX_WORD; ++i)
        printf("---");
    putchar('\n');

    /* get the number of digits in MAX_WORD */
    num_digits = 1;
    while (MAX_WORD / my_pow(10, num_digits) > 0)
        ++num_digits;

    /* print the each row of digits */
    for (j = num_digits - 1; j >= 0; --j) {
        for (i = 0; i < MAX_WORD; ++i) {
            if (((i + 1) / my_pow(10, j)) == 0)
                printf("   ");
            else
                printf(" %1d ", (i + 1) / my_pow(10, j) % 10);
        }
        putchar('\n');
    }
    putchar('\n');

    /* print if there were any overflows */
    if (overflow) {
        if (overflow == 1) {
            verb = "was";
            word = "word";
        }
        else {
            verb = "were";
            word = "words";
        }
        printf("There %s %d %s longer than %d characters.\n\n", verb, overflow, word, MAX_WORD);
    }
}