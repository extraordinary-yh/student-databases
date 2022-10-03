#ifndef HASH_H
#define HASH_H

/* DO NOT ADD CODE: This file is used in evaluation
 * Changing function signatures will result in a 25% deduction.
 * adding comments is ok.
 */

#include <iostream>
#include "Base.h"
using namespace std;

class HashTable : public Base {
        // counters, flags, and constant
	static int counter;	   // how many tables allocated so far
	static bool debug;

	// initialized by Locate function
	int index;                 // last location checked in hash table

	// set in insert/lookup, count of location in probe sequence
        int count;

	const int table_count;     // the table number
	int * probeCount;   // where we are in the probe sequence
	long occupancy;		   // how many elements are in the Hash Table
	const int size;	   // size of Hash Table
	Base ** table;	   // the Hash Table itself ==> array of Base pointers

        
        // functions
	bool Locate (Base *);	   // locate an item

	
public:
	static void Set_Debug (int);
	HashTable (int);		       	    // constructor
	~HashTable (void);		     	    // destructor
	bool Insert (Base *, int initialCount = 1); // insert an item
	Base * Lookup (Base *);			    // lookup an item
	ostream & Write (ostream &);		    // display Hash Table
};

#endif
