#include <cctype>
#include <iostream>
#include "Decin.h"
using namespace std;

/* DO NOT CHANGE:  This file is used in evaluation */

#define ASCII_ZERO 0x30

long decin (void) {
	char character;		/* ASCII input from the user */
	long digit;		/* each digit as it is found */
	long sum = 0;		/* accumulated number */

	/* input terminates with a non-digit character */
	while (isdigit (character = cin.get())) {

		/* change from ASCII */
		digit = character & ~ASCII_ZERO;

		/* accumulate number */
		sum *= 10;
		sum += digit;
	}

	/* return non-digit to input stream */
	cin.putback (character);

	/* result found */
	return sum;
}
