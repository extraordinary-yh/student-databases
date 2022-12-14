#ifndef BASE_H
#define BASE_H

#include <iostream>
using namespace std;

struct Base {
	virtual operator const char * (void) const {
		return 0;
	}
	virtual long operator == (const Base & bbb) const {// isequal function
		return 0;
	}
	virtual long operator > (const Base & bbb) const {// greater than
		return 0;
	}
	Base (void) {}				// new_element
	virtual ~Base (void) {}			// delete_element
	virtual ostream & Write (ostream &) const = 0;// write_element
};

#endif
