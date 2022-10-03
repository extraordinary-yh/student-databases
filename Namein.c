#include <cctype>
#include <iostream>
#include <string.h>

/* DO NOT CHANGE:  This file is used in evaluation */

#include "Namein.h"
using namespace std;

char * namein (char * buffer) {

	char character;		// input from user
	long index = 0;		// index into buffer

	while (isalnum (character = cin.get ()) || character == '_')
		buffer[index++] = character;
	
	buffer[index] = 0;	// terminate string

	/* put non-digit back into stdin */
	cin.putback (character);

	return buffer;
}
