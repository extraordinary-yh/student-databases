#include <cctype>
#include <iostream>
#include <string>
using namespace std;

#include "Namein.h"

char * namein (char * variable_name) {

        char character;         // input from user
        long index = 0;         // index into buffer

        while (isalnum (character = cin.get ()) || character == '_')
                variable_name[index++] = character;
        
        variable_name[index] = 0;       // terminate string

        /* put non-digit back into stdin */
        cin.putback (character);

        return variable_name;
}
