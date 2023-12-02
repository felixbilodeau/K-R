#include <stdio.h>

#define true 1
#define false 0
typedef unsigned char bool;

/*
 * test.c
 * Author: Felix Bilodeau-Chagnon
 * Latest Revision: 2023/11/17
 * 
 * False C program to test the uncomment program.
 * This is essentially a copy of uncomment.c but with
 * some added strings and comments at the end
 */
main()
{
	bool in_string, in_char, in_comment;
	bool last_char_slash, last_char_star;
	bool escape;
	int c;

	in_string = in_char = in_comment = false;
	last_char_slash = last_char_star = false;
	escape = false;

	while ((c = getchar()) != EOF) {
		/* render the character or not */
		if (!in_comment && c != '*') {
			if (last_char_slash)
				putchar('/');
			if (c != '/')
				putchar(c);
		}

		/* update variables */
		switch(c) {
		case '"':
			if (!in_string && !in_comment && !in_char)
				in_string = true;
			else if (in_string && !escape)
				in_string = false;
			last_char_slash = false;
			last_char_star = false;
			escape = false;
			break;

		case '\'':
			if (!in_char && !in_string && !in_comment)
				in_char = true;
			else if (in_char && !escape)
				in_char = false;
			last_char_slash = false;
			last_char_star = false;
			escape = false;
			break;

		case '\\':
			if (in_string || in_char && !escape)
				escape = true;
			else
				escape = false;
			break;

		case '/':
			if (!in_comment && !in_char && !in_string)
				last_char_slash = true;
			else if (last_char_star)
				in_comment = false;
			else if (!in_comment)
				putchar('/');
			last_char_star = false;
			escape = false;
			break;

		case '*':
			if (in_comment)
				last_char_star = true;
			else if (last_char_slash && !in_string && !in_char)
				in_comment = true;
			else
				putchar('*');
			last_char_slash = false;
			escape = false;
			break;

		default:
			last_char_slash = false;
			last_char_star = false;
			escape = false;
		}
	}

	/* This comment should not be printed */
	/* "This string should not be printed" */
	/* This character constant should not be printed: 'g' */
	const char* string = "/* This string should be printed */";
	const char ch = '/* This should be printed as well */';
	
	return 0;
}
