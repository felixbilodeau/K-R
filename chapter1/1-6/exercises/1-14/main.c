#include <stdio.h>

#define HIST_HEIGHT 25
#define CHARACTERS " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890.,\n"

/* determines if a character is contained in a string, and 
   returns the index of its first occurence in the string 
   if the character is not found, the function returns -1 */
char_in_string(char c, char *str, unsigned int len)
{
	char current;
	unsigned int i;

	i = 0;
	current = str[i];

	for (i = 0; i < len; ++i)
		if (c == str[i])
			return i;

	return -1;
}

/* calculates the length of a string */
get_str_len(char* str)
{
	unsigned int len;
	char c;

	len = 0;
	while ((c = str[len]) != '\0')
		++len;
	return len;
}

/* print a histogram of the data
   normalized to max_height */
print_histogram(unsigned int *nc, unsigned int len, unsigned int max_height)
{
	unsigned int i, j, max_count, nc_norm[len];
	/* get the max count */
	max_count = 0;
	for (i = 0; i < len; ++i)
		if (nc[i] > max_count)
			max_count = nc[i];

	/* normalize the count data */
	for (i = 0; i < len; ++i)
		nc_norm[i] = nc[i] * max_height / max_count;

	/* print the histogram */
	putchar('\n');
	for (j = max_height; j > 0; --j) {
		for (i = 0; i < len; ++i)
			if (nc_norm[i] >= j)
				printf("*");
			else
				printf(" ");
		putchar('\n');
	}
	
	for (i = 0; i < len; ++i)
		putchar('-');
	putchar('\n');

	/* print the labels */
	printf(CHARACTERS);
	putchar('\n');
	putchar('\n');
}

/* print a histogram of frequencies of characters in the input */
main()
{
	/* define our variables */
	int c;
	unsigned int len, i, j, others;
	len = get_str_len(CHARACTERS);
	unsigned int nc[len];

	/* set the initial counts to 0 */
	for (i = 0; i < len; ++i)
		nc[i] = 0;

	/* count the characters */
	others = 0;
	while ((c = getchar()) != EOF)
		if ((i = char_in_string(c, CHARACTERS, len)) != -1)
			++nc[i];
		else
			++others;

	/* print the histogram */
	print_histogram(nc, len, HIST_HEIGHT);
	if (others)
		printf("There were %d other characters in the input\n\n", others);
}
