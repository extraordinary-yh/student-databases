#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include "Calc.h"
#include "Decin.h"
#include "Namein.h"
#include "Stack.h"
using namespace std;

/* DO NOT CHANGE:  This file is used in evaluation */

#define OPERATOR 0
#define VALUE 1
#define VARIABLE 2

struct Operator : public Base {
	char ascii;		/* ascii character of operator */
	long index;		/* index in parallel arrays */
	long priority;		/* priority of operator */

	Operator (char);
	~Operator (void) {}
	ostream & Write (ostream & stream) const {
		return stream << ascii;
	}
};

struct Variable : public Base {
	char * name;		/* name of variable */
	long value;		/* value of interest */

	Variable (char * nm, long val = 0) :
		name (strdup (nm)), value (val) {}
	Variable (const Variable & variable) {
		name = strdup (variable.name);
		value = variable.value;
	}
	~Variable (void) {
		free (name);
	}
	operator const char * (void) const {
		return name;
	}
	long operator == (const Base & bbb) const {
		return ! strcmp (name, bbb);
	}

	long operator > (const Base & bbb) const {
		return (strcmp (name, bbb) > 0) ? 1 : 0;
	}

	ostream & Write (ostream & stream) const {
		return stream << name << "(" << value << ")";
	}
};

/* declare the word to place on calculator stacks */
struct Word : public Base {
	union {
		Operator * op;
		long value;
		Variable * var;
	};

	long type;

	Word (char character) : op (new Operator(character)), type (OPERATOR) {}
	Word (long val) : value (val), type (VALUE) {}
	Word (char * name, long val = 0) :
		var (new Variable (name, val)), type (VARIABLE) {}
	~Word (void) {
		if (type == OPERATOR)
			delete op;
		else if (type == VARIABLE)
			delete var;
	}
	char isoperator (void) const {
		return (type == OPERATOR);
	}
	char isvalue (void) const {
		return (type == VALUE);
	}
	char isvariable (void) const {
		return (type == VARIABLE);
	}
	ostream & Write (ostream &) const;
};

static char operators[] = "= ()+-*/^ !";

static Variable * assign (Variable *, long);

static long add (long, long);
static long div (long, long);
static long exp (long, long);
static long fact (long, long ignored);
static long mult (long, long);
static long sub (long, long);

static long (*functions[]) (long, long) =
	{ NULL, NULL, NULL, NULL, add, sub, mult, div, exp, NULL, fact };

long Calculator :: Eval (void) {
	Word * op1, * op2;		/* the operands */
	long operand1, operand2;	/* the operands as long */
	Word * operation;		/* the operation being performed */
	long result;			/* result of computation */

	/* reverse stack1 onto stack2 */
	while (!stack1.IsEmpty ())
		stack2.Push (stack1.Pop ());

	while (!stack2.IsEmpty ()) {


		/* numbers and variables go to stack1 */
		if (!((Word *) stack2.Top ())->isoperator ())
			stack1.Push (stack2.Pop ());
		
		/* operand found */
		else {
			operation = (Word *) stack2.Pop ();
			
			/* get operands */
			op1 = (Word *) stack1.Pop ();
			operand1 = (op1->isvariable ())
				? ((Variable *) symtab.Lookup (op1->var))->value
				: op1->value;

			if (operation->op->ascii != '!') {
				op2 = (Word *) stack1.Pop ();
				if (op2->isvariable ()
				&& (operation->op->ascii != '='))
					operand2 = ((Variable *)
					symtab.Lookup (op2->var))->value;
				else
					operand2 = op2->value;
			}
			else
				operand2 = operand1;

			/* evaluate expression and push to stack1 */
			if (operation->op->ascii != '=')
				result = functions[operation->op->index]
					(operand1, operand2);
			// variable assignment
			else {
				Variable * svar = assign (op2->var, operand1);
				symtab.Insert (svar);
				result = op2->var->value;
			}

			stack1.Push (new Word (result));

			/* free up memory */
			delete op1;
			if (operation->op->ascii != '!')
				delete op2;
			delete operation;
		}
	}

	op1 = (Word *) stack1.Pop ();
	result = (op1->isvariable ())
		? ((Variable *) symtab.Lookup (op1->var))->value
		: op1->value;

	/* free up memory */
	delete op1;

	return result;
}


long Calculator :: InToPost (void) {
	char character;			/* character input from the user */
	Word * word;			/* a word for the stack */
	
	while ((character = cin.get ()) != '\n') {

		/* check for termination of input */
		if (character == EOF)
			return EOF;

		/* ignore blanks */
		if (isspace (character))
			continue;
		
		if (isdigit (character) || character == '.') {

			/* for decin call */
			cin.putback (character);

			/* place any numbers onto stack1 */

			stack1.Push (new Word (decin()));
		}

		else if (isalpha (character)) {

			char variable_name[BUFSIZ];

			/* for namein call */
			cin.putback (character);

			/* place any numbers onto stack1 */

			stack1.Push (new Word (namein(variable_name)));
		}

		else if (character == '(') {

			/* open parenthesis go onto stack2 */

			stack2.Push (new Word ('('));
		
		}
		else if (character == ')') {

			/* pop stack2 to stack1 until matching parenthesis */
			while (word = (Word *) stack2.Pop (),
				word->op->ascii != '(')
					stack1.Push (word);

			/* free up memory */
			delete word;
		}

		/* operator must be encountered */
		else {
			word = new Word (character);/* to store on stack */

			/* pop stack2 to stack1 until empty or lower priority */
			while (!stack2.IsEmpty () &&
				((Word *) stack2.Top ())->op->priority
				>= word->op->priority)
					stack1.Push (stack2.Pop ());

			/* finally place operator on stack2 */
			stack2.Push (word);
		}
	}

	/* place any remaining stack2 items to stack1 ==> done */
	while (!stack2.IsEmpty ())
		stack1.Push (stack2.Pop ());
	
	return 1;
}


Operator :: Operator (char ascii_code) : ascii (ascii_code) {
	
	index = 0;	/* index of the operand in character array */

	/* compute function index */
	while (operators[index] != ascii)
		index++;

	priority = index >> 1;
}


ostream & Word :: Write (ostream & stream) const {

	switch (type) {
	case OPERATOR:
		op->Write (stream) << " ";
		break;
	case VALUE:
		stream << value << " ";
		break;
	case VARIABLE:
		var->Write (stream) << " ";
	}

	return stream;
}
	

static long add (long addendx, long addendy) {
	return addendx + addendy;
}

static Variable * assign (Variable * variable, long value) {
	
	Variable * retval;	// return value

	// give variable its value
	variable->value = value;
	retval = new Variable (*variable);

	return retval;
}

static long div (long divisor, long dividend) {
	return dividend / divisor;
}

static long exp (long power, long base) {
	long retval = 1;

	while (power > 0) {
		retval *= base;
		power--;
	}
	
	while (power < 0) {
		retval /= base;
		power++;
	}

	return retval;
}

static long fact (long xxx, long ignored) {
	return (xxx <= 1) ? 1 : xxx * fact (xxx - 1, ignored);
}

static long mult (long factorx, long factory) {
	return factorx * factory;
}

static long sub (long subtrahend, long minuend) {
	return minuend - subtrahend;
}
