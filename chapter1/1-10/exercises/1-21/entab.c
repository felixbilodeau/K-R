#include <stdio.h>

#define TAB_SIZE 4      /* the column positions of tabs */
#define MAX_LINE 1000   /* the maximum line length */

unsigned int get_line(char line[], unsigned int max_line);
unsigned int tab_at(unsigned int index, unsigned int tab_size);
void entab(char line[]);

/*
 * main:
 * replaces spaces in the input with the appropriate
 * mixture of tabs and spaces, prioritizing tabs
 * whenever possible
 */
main()
{
    char line[BUFF_SIZE];

    while (get_line(line, BUFF_SIZE) != 0)
        entab(line);

    return 0;
}

/* 
 * get_line:
 * stores the current line in 'line'
 * and returns its length
 */
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

/*
 * tab_at:
 * returns the number of columns advaced when adding a tab
 * character at the given index
 */
unsigned int tab_at(unsigned int index, unsigned int tab_size)
{
    return tab_size - (index % tab_size);
}

/*
 * entab:
 * prints 'line' while replacing spaces with the
 * appropriate number of spaces and tabs, prioritizing
 * tabs whenever possible
 */
void entab(char line[])
{
    unsigned int i, j, start, cols;
    char c;

    for (i = j = start = cols = 0; (c = line[i]) != '\0'; ++i) {
        if (c == ' ') {
            if (j == 0)
                start = cols;
            ++j;
            ++cols;
        } else if (c == '\t') {
            if (j == 0)
                start = cols;
            j = j + tab_at(cols, TAB_SIZE);
            cols = cols + tab_at(cols, TAB_SIZE);
        } else if (j > 0) {
            if (j < TAB_SIZE)
                if (tab_at(start, TAB_SIZE) == j) {
                    putchar('\t');
                    j = 0;
                } else
                    while (j > 0) {
                        putchar(' ');
                        --j;
                    }
            else {
                putchar('\t');
                j = j - tab_at(start, TAB_SIZE);
                while (j > 0)
                    if (j >= TAB_SIZE) {
                        putchar('\t');
                        j = j - TAB_SIZE;
                    } else {
                        putchar(' ');
                        --j;
                    }
            }
            putchar(c);
            ++cols;
        } else {
            putchar(c);
            ++cols;
        }
    }
}
