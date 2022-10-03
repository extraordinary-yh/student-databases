#include <iostream>
#include "Base.h"
#include "Stack.h"
using namespace std;

/* DO NOT CHANGE:  This file is used in evaluation */

Base * Stack :: Pop (void) {
	return Remove ();
}

long Stack :: Push (Base * element) {
	return Insert (element);
}

Base * Stack :: Top (void) const {
	return View ();
}
