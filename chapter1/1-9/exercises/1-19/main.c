#include <stdio.h>

#define MAX_LINE 1000

unsigned int get_line(char line[], unsigned int max_line);
void reverse(char str[]);

main()
{
    char line[BUFF_SIZE];
    unsigned int length;

    while ((length = get_line(line, BUFF_SIZE)) != 0) {
        line[length - 1] = '\0';
        reverse(line);
        line[length - 1] = '\n';
        printf("%s", line);
    }

    return 0;
}

unsigned int get_line(char line[], unsigned int max_line)
{
    unsigned int i, j;
    int c;

    for (i = j = 0; (c = getchar()) != EOF && c != '\n'; ++i)
        if (i < max_line - 2) {
            line[j] = c;
            ++j;
        }

    line[j] = '\n';
    ++j;

    if (c == '\n')
        ++i;
    
    line[j] = '\0';

    return i;
}

void reverse(char str[])
{
    unsigned int len, i;
    
    len = 0;
    while (str[len] != '\0')
        ++len;

    char tmp[len];

    for (i = 0; i < len; ++i)
        tmp[i] = str[len - 1 - i];

    for (i = 0; i < len; ++i)
        str[i] = tmp[i];
}