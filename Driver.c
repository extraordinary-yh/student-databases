#include <cstdlib>
#include <iostream>
#include <string.h>
#include "Base.h"
#include "SymTab.h"
using namespace std;

#ifdef NULL
#undef NULL
#define NULL 0
#endif
/**
 * This class provides constructors and methods associated with object
 * UCSDStudent
 * 
 * @author: Mark Zeng (cs12fa19dm)
 */
class UCSDStudent : public Base {
	char * name;
	long studentnum;
public:
	/**
	 * Constructor. initialize a UCSDStudent's data fields
	 *
	 * @param *nm pointer to the name of the Student
	 * @param num the number of the Student
	 */ 
	UCSDStudent (char * nm, long num = 0) :
		name (strdup (nm)), studentnum (num) {}
	
	/**
	 * Constructor. iniitialize a UCSDStudent's data fields with an
	 * existing UCSDStudent
	 *
	 * @param student the UCSDStudent being passed in
	 */
	UCSDStudent (const UCSDStudent & student) {
		name = strdup (student.name);
		studentnum = student.studentnum;
	}
	
	/**
	 * Destructor. deallocates UCSDStudent
	 *
	 */
	~UCSDStudent (void) {
		free (name);
	}
        
	/**
	 * overide the operator const char* to make it return student's name
	 *
	 * @return name of student 
	 */
	operator const char * (void) const {
		return name;
	}

	/**
	 * overide the operator == to make it check if the student's name equals
	 *
	 * @param a Base to be compared
	 * @return true if equals, false otherwise
	 */
	long operator == (const Base & bbb) const {
		return ! strcmp (name, bbb);
	}

	/**
	 * overide the operator > to make it check which one is bigger
	 *
	 * @param the base to be compared
	 * @return true if greater, false otherwise
	 */
	long operator > (const Base & bbb) const {
		return (strcmp (name, bbb) > 0) ? 1 : 0;
	}

	ostream & Write (ostream & stream) const {
		return stream << "name:  " << name
			<< "  studentnum:  " << studentnum;
	}
};

int main (int argc, char * const * argv) {
	char buffer[80];
	char command;
	long number;

	Tree::Set_Debug(0);

	if (argc != 1 && strcmp("-x", argv[1]) == 0) {
		Tree::Set_Debug(1);
	}
	
	SymTab * ST;
	ST = new SymTab ("UCSDStudentTree");
	ST->Write (cout << "Initial Symbol Table:\n");

	while (cin) {
		command = NULL;		// reset command each time in loop
		cout <<  "Please enter a command:  ((a)llocate, is(e)mpty," <<
			" (i)nsert, (l)ookup, (r)emove, (w)rite):  ";
		cin >> command;

		switch (command) {

		case 'a':
			cout << "Please enter name of new Tree to allocate:  ";
			cin >> buffer; 

			delete ST;
			ST = new SymTab (buffer);

			break;

		case 'e':
                        if (ST->IsEmpty ())
                                cout << "Tree is empty." << endl;
                        else
                                cout << "Tree is not empty." << endl;
                        break;
			
		case 'i':
			cout << "Please enter UCSD student name to insert:  ";
			cin >> buffer;	// formatted input

			cout << "Please enter UCSD student number:  ";
			cin >> number;

			// create student and place in symbol table
			ST->Insert (new UCSDStudent (buffer, number));
			break;

		case 'l': {
			const Base * found;	// whether found or not

			cout << "Please enter UCSD student name to lookup:  ";
			cin >> buffer;	// formatted input

			UCSDStudent stu (buffer, 0);
			found = ST->Lookup (&stu);
			
			if (found)
				found->Write (cout << "Student found!\n") << "\n";
			else
				cout << "student " << buffer << " not there!\n";
			}
			break;
		
		case 'r': {
			Base * removed;	// data to be removed

			cout << "Please enter UCSD student name to remove:  ";
			cin >> buffer;	// formatted input

			UCSDStudent stu (buffer, 0);
			removed = ST->Remove (&stu);

			if (removed)
				removed->Write (cout << "Student removed!\n") << "\n";
			else
				cout << "student " << buffer << " not there!\n";
			}
			break;


		case 'w':
			ST->Write (cout << "The Symbol Table contains:\n");
		}
	}

	ST->Write (cout << "\nFinal Symbol Table:\n");
	delete ST;
}
