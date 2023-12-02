#include <stdio.h>

#define MAX_COLS 20	/* maximum number of characters per line */
#define TAB_SIZE 4	/* tab character max size */

unsigned int get_line(
	char line[], unsigned int line_length, unsigned int start_index, unsigned int max_cols
);
unsigned int shift_left(
	char line[], unsigned int line_length, unsigned int start_index
);
unsigned int get_next_whitespace(
	char line[], unsigned int line_length, unsigned int start_index
);
unsigned int get_tab_offset(unsigned int col);
unsigned int print_line(char line[], unsigned int length);


/*
 * main:
 * Wraps the input to fit within MAX_COLS columns
 */
main()
{
	char line[MAX_COLS + 1];
	unsigned int line_length, start_index;

	line_length = start_index = 0;
	while ((line_length = get_line(
		line, line_length, start_index, MAX_COLS
	)) != 0)
		start_index = print_line(line, line_length);

	return 0;
}

/*
 * get_line:
 * Stores a line from standard input into line with a
 * maximum columns of max_cols. If the maximum length
 * is reached before a new line character is reached,
 * the full buffer may be used without a null ending.
 * The length of the buffer is returned.
 */
unsigned int get_line(
	char line[], unsigned int line_length, unsigned int start_index, unsigned int max_cols
)
{
	unsigned int col, i, new_start_index;
	int c;

	new_start_index = shift_left(line, line_length, start_index);

	/* loop through and recalculate column position */
	for (i = col = 0; i < new_start_index; ++i)
		if (line[i] == '\t')
			col = col + get_tab_offset(col);
		else
			++col;

	/* load new characters until max column is reached */
	while (col < max_cols && (c = getchar()) != EOF && c != '\n') {
		line[i] = c;

		if (c == '\t')
			col = col + get_tab_offset(col);
		else
			++col;
		++i;
	}

	/* 
	 * If we exited because of newline of EOF in the middle of the loop,
	 * add a newline character to the end of the array
	 */
	if (c == '\n' || (c == EOF && i != 0)) {
		line[i] = '\n';
		++i;
	} 

	/* return length */
	return i;
}

/*
 * shift_left:
 * Shifts the characters in the line buffer left by
 * start_col. Returns the new length.
 */
unsigned int shift_left(
	char line[], unsigned int line_length, unsigned int start_index
)
{
	/* if no work needs to be done just return */
	if (!start_index) {
		return 0;
	}

	/* shifts all characters into the beginning of the array */
	unsigned int i;
	for (i = start_index; i < line_length; ++i)
		line[i - start_index] = line[i];

	return i - start_index;
}

/*
 * get_next_whitespace:
 * Get the index position of the next whitespace after
 * start_index. If no whitespace is found, returns line_length.
 */
unsigned int get_next_whitespace(
	char line[], unsigned int line_length, unsigned int start_index
)
{
	unsigned int i;
	char c;

	/* start one index after start_index  */
	/* if that would be out of bounds, panic return */
	if (start_index + 1 >= line_length)
		return line_length;

	i = start_index + 1;

	/* find if there is whitespace in the column */
	while (i < line_length && (c = line[i]) != ' ' && c != '\t' && c != '\n')
		++i;

	/* return where we found whitespace (if any) */
	return i;
}

/*
 * get_tab:
 * Returns the column offset that a tab placed at
 * the given column position would cause.
 */
unsigned int get_tab_offset(unsigned int col)
{
	return TAB_SIZE - (col % TAB_SIZE);
}

/*
 * print_line:
 * Prints the line up to max_cols or line_length.
 * Adds a new line character at the end.
 * If no whitespace is found within the line, the
 * entire line is printed and the function returns 0
 */
unsigned int print_line(char line[], unsigned int line_length)
{
	unsigned int i, end_index, next_whitespace;

	/* get the next whitespace character */
	end_index = next_whitespace = 0;
	while (next_whitespace != line_length) {
		end_index = next_whitespace;
		next_whitespace = get_next_whitespace(
			line, line_length, next_whitespace
		);
	}

	/* if we didn't find any, make sure we 
	 * print the whole line.
	 */
	if (!end_index)
		end_index = line_length - 1;

	/* print the line */
	for (i = 0; i <= end_index; ++i)
		putchar(line[i]);
	
	/* add a new line if that's not already done */
	if (line[i - 1] != '\n')
		putchar('\n');

	/* if we printed the whole line, return 0 */
	if (end_index == line_length - 1)
		return 0;

	/* otherwise, return the length of string printed */
	return i;
}
