#include <stdio.h>
#define MAX_LINE 100

int get_line(char line[], int maxline);
void copy(char to[], char from[]);

/* print longest input line */
main()
{
    int len;                    /* current line length */
    int max;                    /* maximum length seen so far */
    char line[BUFF_SIZE];        /* current input line */
    char longest[BUFF_SIZE];     /* longest line saved here */

    max = 0;
    while ((len = get_line(line, BUFF_SIZE)) > 0)
        if (len > max) {
            max = len;
            copy(longest, line);
        }
    if (max > 0)    /* there was a line */
        printf("%d: %s", max, longest);
    return 0;
}

/* get_line: read a line into s, return length */
int get_line(char s[], int lim)
{
    int c, i, j;

    for (i = j = 0; (c = getchar()) != EOF && c != '\n'; ++i)
        if (i < lim - 2) {
            s[j] = c;       /* line still in boundaries */
            ++j;
        }

    s[j] = '\n';
    ++j;
    if (c == '\n') {
        ++i;
    }

    s[j] = '\0';
    return i;
}

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}
