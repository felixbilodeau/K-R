#include <stdio.h>

#define MAX_LINE 200

unsigned int get_line(char line[], unsigned int max_line);
void print_stripped(char line[], unsigned int length);

main()
{
    char line[BUFF_SIZE];
    unsigned int length;

    while ((length = get_line(line, BUFF_SIZE)) != 0) {
        if (length > 1)
            print_stripped(line, length);
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

void print_stripped(char line[], unsigned int length)
{
    unsigned int i;

    i = length - 2;
    while ((line[i] == ' ' || line[i] == '\t') && i > 0)
        --i;
    
    if (i > 0) {
        line[i + 1] = '\n';
        line[i + 2] = '\0';
        printf("%s", line);
    }
}
