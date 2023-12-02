#include <stdio.h>

#define MIN_LINE_LEN 80
#define MAX_LINE 200

unsigned int get_line(char line[], unsigned int max_line);

main()
{
    char line[BUFF_SIZE];
    unsigned int length;

    while ((length = get_line(line, BUFF_SIZE)) != 0)
        if (length > MIN_LINE_LEN)
            printf("%s", line);

    return 0;
}

unsigned int get_line(char line[], unsigned int max_line)
{
    int c;
    unsigned int i, j;

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
