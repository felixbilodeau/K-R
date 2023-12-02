#include <stdio.h>

#define TAB_SIZE 4      /* the column positions of tabs */
#define MAX_LINE 1000   /* the maximum line length */

unsigned int get_line(char line[], unsigned int max_line);
void detab(char line[]);

/*
 * main:
 * replaces tabs with the appropriate number of spaces
 * to reach the next tab position
 */
main()
{
    char line[BUFF_SIZE];

    while (get_line(line, BUFF_SIZE) != 0)
        detab(line);

    return 0;
}

/* get_line: returns the length of the next line and stores in it 'line' */
unsigned int get_line(char line[], unsigned int max_line)
{
    unsigned int i;
    int c;

    for (i = 0; i < max_line - 2 && (c = getchar()) != EOF && c != '\n'; ++i)
        line[i] = c;

    if (c == '\n') {
        line[i] = c;
        ++i;
    }

    line[i] = '\0';
    return i;
}

/* detab: prints the input line with tabs
 * replaced with the correct number of spaces
 */
void detab(char line[])
{
    unsigned int i, j, cols;
    char c;
    
    for (i = cols = 0; (c = line[i]) != '\0'; ++i)
        if (c == '\t') {
            for (j = TAB_SIZE - (cols % TAB_SIZE); j > 0; --j) {
                putchar(' ');
                ++cols;
            }
        } else {
            putchar(c);
            ++cols;
        }
}
