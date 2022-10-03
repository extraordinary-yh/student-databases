#ifndef LIST_H
#define LIST_H

/* DO NOT CHANGE:  This file is used in evaluation 
 * Changing function signatures will result in a 25% deduction.
 * */

#include <iostream>
#include "Base.h"
using namespace std;

#ifndef NULL
#define NULL 0
#endif

struct Node;

class List : public Base {
	Node * current;
	long occupancy;
public:
	List (void) : current (NULL), occupancy (0) {}
	~List (void);
	void Advance_Next (void);
	void Advance_Pre (void);
	long Insert (Base *);
	Base * Remove (void);
	Base * View (void) const;
	long IsEmpty (void) const {
		return ! NumElements ();
	}
	long NumElements (void) const {
		return occupancy;
	}
	ostream & Write (ostream &) const;
};

#endif
