#ifndef CALC_H
#define CALC_H

/* DO NOT ADD CODE: This file is used in evaluation
 * Changing function signatures will result in a 25% deduction.
 * adding comments is ok.
 */

#include <iostream>
#include "Base.h"
#include "Stack.h"
#include "SymTab.h"
using namespace std;

class Calculator : public Base {
	SymTab symtab;
	Stack stack1, stack2;
public:
	Calculator (void) : symtab ("CalcTree") {}
	long Eval (void);
	long InToPost (void);
	ostream & Write_Postfix (ostream & stream) const {
		return stack1.Write (stream);
	}
	ostream & Write (ostream & stream) const {
		stack1.Write (stream << "Stack 1 is:\n");
		stack2.Write (stream << "Stack 2 is:\n");
		return symtab.Write (stream << "Symbol Table is:\n");
	}
};

#endif
