#include <stdio.h>

/* 1 MB */
#define BUFFSIZE 1024*1024

/* Tokens */
struct Token {
    const char *str;
    const size_t length;
};

const struct Token LEFT_PAREN = {"(", 1};
const struct Token RIGHT_PAREN = {")", 1};

const struct Token LEFT_BRACKET ={"[", 1};
const struct Token RIGHT_BRACKET =  {"]", 1};

const struct Token LEFT_BRACE = {"{", 1};
const struct Token RIGHT_BRACE = {"}", 1};

const struct Token LEFT_COMMENT = {"/*", 2};
const struct Token RIGHT_COMMENT = {"*/", 2};

const struct Token DOUBLE_QUOTE = {"\"", 1};
const struct Token SINGLE_QUOTE = {"\'", 1};

const struct Token BACKSLASH = {"\\", 1};

int is_token(char **start, struct Token token);
int parse_parens(char **start);
int parse_brackets(char **start);
int parse_braces(char **start);
int parse_comment(char **start);
int parse_string(char **start);
int parse_char(char **start);
int parse_escape(char **start);
int parse(char **start);
void print_error_location(char file[], char *file_pointer);

/*
 * is_token:
 * checks if the string at `*start` is `token`
 * 
 * returns `1` if it is, `0` otherwise
 */
int is_token(char **start, struct Token token)
{
    if (token.length == 1) {
        return **start == *(token.str);
    }

    size_t i;

    i = 0;
    while (token.str[i] && (*start)[i] && (*start)[i] == token.str[i]) ++i;
    if (i == token.length) {
        *start = *start + token.length - 1;
        return 1;
    }
    return 0;
}

/*
 * parse_parens:
 * parses parentheses
 * 
 * returns `1` if successful, `0` otherwise
 */
int parse_parens(char **start)
{
    char *base;
    for (base = *start - LEFT_PAREN.length; **start; ++(*start)) {
        if (is_token(start, RIGHT_PAREN)) {
            return 1;
        } else if (is_token(start, LEFT_PAREN)) {
            ++(*start);
            if (!parse_parens(start)) return 0;
        } else if (is_token(start, LEFT_BRACKET)) {
            ++(*start);
            if (!parse_brackets(start)) return 0;
        } else if (is_token(start, LEFT_BRACE)) {
            ++(*start);
            if (!parse_braces(start)) return 0;
        } else if (is_token(start, LEFT_COMMENT)) {
            ++(*start);
            if (!parse_comment(start)) return 0;
        } else if (is_token(start, DOUBLE_QUOTE)) {
            ++(*start);
            if (!parse_string(start)) return 0;
        } else if (is_token(start, SINGLE_QUOTE)) {
            ++(*start);
            if (!parse_char(start)) return 0;
        } else if (
            is_token(start, RIGHT_BRACKET) ||
            is_token(start, RIGHT_BRACE)
        ) {
            puts("Syntax error: mismatched parentheses");
            *start = base;
            return 0;
        }
    }
    *start = base;
    puts("Syntax error: reached end of file while parsing");
    puts("Missing closing parenthesis");
    return 0;
}

/*
 * parse_brackets:
 * parses brackets
 * 
 * returns `1` if successful, `0` otherwise
 */
int parse_brackets(char **start)
{
    char *base;
    for (base = *start - LEFT_BRACKET.length; **start; ++(*start)) {
        if (is_token(start, RIGHT_BRACKET)) {
            return 1;
        } else if (is_token(start, LEFT_PAREN)) {
            ++(*start);
            if (!parse_parens(start)) return 0;
        } else if (is_token(start, LEFT_BRACKET)) {
            ++(*start);
            if (!parse_brackets(start)) return 0;
        } else if (is_token(start, LEFT_BRACE)) {
            ++(*start);
            if (!parse_braces(start)) return 0;
        } else if (is_token(start, LEFT_COMMENT)) {
            ++(*start);
            if (!parse_comment(start)) return 0;
        } else if (is_token(start, DOUBLE_QUOTE)) {
            ++(*start);
            if (!parse_string(start)) return 0;
        } else if (is_token(start, SINGLE_QUOTE)) {
            ++(*start);
            if (!parse_char(start)) return 0;
        } else if (
            is_token(start, RIGHT_PAREN) ||
            is_token(start, RIGHT_BRACE)
        ) {
            *start = base;
            puts("Syntax error: mismatched brackets");
            return 0;
        }
    }
    *start = base;
    puts("Syntax error: reached end of file while parsing");
    puts("Missing closing bracket");
    return 0;
}

/*
 * parse_braces:
 * parses braces
 * 
 * returns `1` if successful, `0` otherwise
 */
int parse_braces(char **start)
{
    char *base;
    for (base = *start - LEFT_BRACE.length; **start; ++(*start)) {
        if (is_token(start, RIGHT_BRACE)) {
            return 1;
        } else if (is_token(start, LEFT_PAREN)) {
            ++(*start);
            if (!parse_parens(start)) return 0;
        } else if (is_token(start, LEFT_BRACKET)) {
            ++(*start);
            if (!parse_brackets(start)) return 0;
        } else if (is_token(start, LEFT_BRACE)) {
            ++(*start);
            if (!parse_braces(start)) return 0;
        } else if (is_token(start, LEFT_COMMENT)) {
            ++(*start);
            if (!parse_comment(start)) return 0;
        } else if (is_token(start, DOUBLE_QUOTE)) {
            ++(*start);
            if (!parse_string(start)) return 0;
        } else if (is_token(start, SINGLE_QUOTE)) {
            ++(*start);
            if (!parse_char(start)) return 0;
        } else if (
            is_token(start, RIGHT_PAREN) ||
            is_token(start, RIGHT_BRACKET)
        ) {
            *start = base;
            puts("Syntax error: mismatched braces");
            return 0;
        }
    }
    *start = base;
    puts("Syntax error: reached end of file while parsing");
    puts("Missing closing brace");
    return 0;
}

/*
 * parse_comment:
 * parses a comment
 * 
 * returns `1` if successful, `0` otherwise
 */
int parse_comment(char **start)
{
    char *base;
    for (base = *start - LEFT_COMMENT.length; **start; ++(*start)) {
        if (is_token(start, RIGHT_COMMENT)) {
            return 1;
        }
    }
    *start = base;
    puts("Syntax error: reached end of file while parsing");
    puts("Comment never closed");
    return 0;
}

/*
 * parse_string:
 * parses a string literal
 * 
 * returns `1` if successful, `0` otherwise
 */
int parse_string(char **start)
{
    char *base;
    for (base = *start - DOUBLE_QUOTE.length; **start; ++(*start)) {
        if (is_token(start, BACKSLASH)) {
            ++(*start);
            if (!parse_escape(start)) return 0;
        } else if (is_token(start, DOUBLE_QUOTE)) {
            return 1;
        }
    }
    *start = base;
    puts("Syntax error: reached end of file while parsing");
    puts("String never closed");
    return 0;
}

/*
 * parse_char:
 * parses a character constant
 * 
 * returns `1` if successful, `0` otherwise
 */
int parse_char(char **start)
{
    char *base;
    for (base = *start - SINGLE_QUOTE.length; **start; ++(*start)) {
        if (is_token(start, BACKSLASH)) {
            ++(*start);
            if (!parse_escape(start)) return 0;
        } else if (is_token(start, SINGLE_QUOTE)) {
            return 1;
        }
    }
    *start = base;
    puts("Syntax error: reached end of file while parsing");
    puts("Character never closed");
    return 0;
}

/*
 * parse_escape:
 * parses an escape sequence
 * 
 * returns `1` if successful, `0` otherwise
 */
int parse_escape(char **start)
{
    char *base;
    base = *start - BACKSLASH.length;
    if (!**start) {
        *start = base;
        puts("Syntax error: reached end of file while parsing");
        return 0;
    }
    return 1;
}

/*
 * parse:
 * parses the file from `start`
 * 
 * returns `1` if successful, `0` otherwise
 */
int parse(char **start)
{
    char *base;
    for (base = *start; **start; ++(*start)) {
        base = *start;
        if (is_token(start, LEFT_PAREN)) {
            ++(*start);
            if (!parse_parens(start)) return 0;
        } else if (is_token(start, LEFT_BRACKET)) {
            ++(*start);
            if (!parse_brackets(start)) return 0;
        } else if (is_token(start, LEFT_BRACE)) {
            ++(*start);
            if (!parse_braces(start)) return 0;
        } else if (is_token(start, LEFT_COMMENT)) {
            ++(*start);
            if (!parse_comment(start)) return 0;
        } else if (is_token(start, DOUBLE_QUOTE)) {
            ++(*start);
            if (!parse_string(start)) return 0;
        } else if (is_token(start, SINGLE_QUOTE)) {
            ++(*start);
            if (!parse_char(start)) return 0;
        } else if (
            is_token(start, RIGHT_PAREN) ||
            is_token(start, RIGHT_BRACKET) ||
            is_token(start, RIGHT_BRACE)
        ) {
            *start = base;
            puts("Syntax error: mismatched delimiter");
            return 0;
        }
    }
    return 1;
}

/*
 * print_error_location:
 * prints the whole line where the error occured
 * as well as a `^` under the offending character
 */
void print_error_location(char file[], char *file_pointer)
{
    size_t current_index, line_start, line, i;

    current_index = (size_t)((void*)file_pointer - (void*)file);
    line_start = current_index;

    for (
        line_start = current_index;
        file[line_start] != '\n' && line_start > 0;
        --line_start
    );

    line = 1;
    for (i = 0; i < line_start; ++i)
        if (file[i] == '\n') ++line;
    if (file[i] == '\n') {
        ++i;
        ++line;
    }

    printf("At line %zu:\n", line);

    while (file[i] != '\n' && file[i]) {
        putchar(file[i]);
        ++i;
    }
    putchar('\n');

    for (i = ++line_start; i < current_index; ++i)
        putchar(' ');
    putchar('^');
    putchar('\n');
}

/*
 * main:
 * Detects and warns of simple syntax errors
 * Can detect mismatched parentheses, brackets,
 * braces, comments, strings, and character constants
 */
int main()
{
    char file[BUFFSIZE];
    char *file_pointer;
    size_t file_size;
    int c;

    file_size = 0;

    while ((c = getchar()) != EOF && file_size < BUFFSIZE) {
        file[file_size] = c;
        ++file_size;
    }
    if (file_size == BUFFSIZE) {
        puts("ERROR: input file is larger than 1 MB! Aborting");
        return 1;
    }
    file[file_size] = '\0';

    file_pointer = file;
    if (!parse(&file_pointer)) {
        print_error_location(file, file_pointer);
        return 1;
    }
    return 0;
}
