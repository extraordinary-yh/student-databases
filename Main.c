#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include "Calc.h"
using namespace std;

/* DO NOT CHANGE:  This file is used in evaluation */

int main (int argc, char * const * argv) {

	Tree::Set_Debug(0);
                
        if (argc != 1 && strcmp("-x", argv[1]) == 0) {
                Tree::Set_Debug(1); 
        }	

	Calculator calc;		// Calculator to use

	while (1) {
		cout << "\nPlease enter an expression to calculate:  ";
		if (calc.InToPost () == EOF)
			break;
		
		calc.Write_Postfix
			(cout << "\nThe expression in postfix order is:  ");

		cout << "\nwhich evaluates to:  " << calc.Eval () << "\n";

		calc.Write (cerr << "Calculator is:\n");
	}

	cout << "\n";
}
