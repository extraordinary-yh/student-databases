import java.io.*;
/**
 * This class provides constructors and methods associated with object
 * UCSDStudent
 * 
 * @author: Mark Zeng (cs12fa19dm)
 */
class UCSDStudent extends Base {

        private String name;
        private long studentnum;

        /**
	 * Constructor. initialize a UCSDStudent's data fields
	 *
	 * @param nm the name of the Student
	 * @param num the number of the Student
	 */ 
        public UCSDStudent (String nm, long num) {  
                name = new String (nm);  
                studentnum = num;  
        }  

	/**
	 * Constructor. iniitialize a UCSDStudent's data fields with an
	 * existing UCSDStudent
	 *
	 * @param student the UCSDStudent being passed in
	 */
        public UCSDStudent (UCSDStudent student) {  
                name = new String (student.name);  
                studentnum = student.studentnum;  
        }  
        /**
	 * This method returns the name of UCSDStudent
	 *
	 * @return the name of the student
	 */
        public String getName () {  
                return name;  
        }  

	/**
	 * This method compares the name of a UCSDStudent with
	 * the object being passed in
	 *
	 * @param object the object being compared
	 * @return true if equals, false otherwise
	 */
        public boolean equals (Object object) {  
  
                if (this == object)  
                        return true;  
  
                if (!(object instanceof UCSDStudent))  
                        return false;  
  
                UCSDStudent otherStu = (UCSDStudent) object;  
  
                return name.equals (otherStu.getName ());  
        } 
       	/**
	 * This method compares if the name of the UCSDStudent
	 * is greater than the base object being passed in
	 *
	 * @param base the base being compared
	 * @return true if greater, false otherwise
	 */
        public boolean isGreaterThan (Base base) {  
                return (name.compareTo (base.getName ()) > 0) ? true : false;
	}

        public String toString () {
                return "name:  " + name + "  studentnum:  " + studentnum;
        }
}

public class Driver {
        private static final short NULL = 0;

        public static void main (String [] args) {
        
                /* initialize debug states */
                Tree.debugOff();

                /* check command line options */
                for (int index = 0; index < args.length; ++index) {
                        if (args[index].equals("-x"))
                                Tree.debugOn();
                }


                /* The real start of the code */
                SymTab<UCSDStudent> symtab = 
                                new SymTab<UCSDStudent>("UCSDStudentTree");
                String buffer = null;
                char command;
                long number = 0;

                System.out.println ("Initial Symbol Table:\n" + symtab);

                while (true) {
                        command = NULL; // reset command each time in loop
                        System.out.print ("Please enter a command:  " + 
                                "((a)llocate, is(e)mpty, (i)nsert, (l)ookup,"+
                                " (r)emove, (w)rite):  ");

                        try {
                        command = MyLib.getchar ();
                        MyLib.clrbuf (command); // get rid of return

                        switch (command) {
                        case 'a':
                                System.out.print
                                ("Please enter name of new Tree to " +
                                 "allocate:  ");
                                
                                buffer = MyLib.getline ();// formatted input
                                symtab = new SymTab<UCSDStudent>(buffer);
                                break;
			case 'e':
				if(symtab.isEmpty()){
					System.out.println("Tree is empty.");
				} else {
					System.out.println("Tree is "+
						"not empty.");
				}
				break;

                        case 'i':
                                System.out.print
                                ("Please enter UCSD student name to insert:  ");

                                buffer = MyLib.getline ();// formatted input

                                System.out.print
                                        ("Please enter UCSD student number:  ");

                                number = MyLib.decin ();
                                MyLib.clrbuf (command); // get rid of return

                                // create student and place in symbol table
                                symtab.insert(new UCSDStudent (buffer, number));
                                break;

                        case 'l': { 
                                UCSDStudent found;      // whether found or not

                                System.out.print
                                ("Please enter UCSD student name to lookup:  ");
                                buffer = MyLib.getline ();// formatted input

                                UCSDStudent stu = new UCSDStudent (buffer, 0);
                                found = symtab.lookup (stu);
                                
                                if (found != null) {
                                        System.out.println("Student found!");
                                        System.out.println(found);
                                }
                                else
                                        System.out.println ("student " + buffer
                                                + " not there!");
                                }
                                break;
                        
                        case 'r': { 
                                UCSDStudent removed; // data to be removed

                                System.out.print
                                ("Please enter UCSD student name to remove:  ");

                                buffer = MyLib.getline ();

                                UCSDStudent stu = new UCSDStudent (buffer, 0);

                                removed = symtab.remove(stu);

                                if (removed != null) {
                                        System.out.println("Student removed!"); 
                                        System.out.println(removed);
                                }
                                else
                                        System.out.println ("student " + buffer
                                                + " not there!");
                                }
                                break;

                        case 'w':
                                System.out.println("The Symbol Table " +
                                "contains:\n" + symtab);
                        }
                        }
                        catch (EOFException eof) {
                                break;
                        }
                }
                System.out.println("\nFinal Symbol Table:\n" + symtab);
        }
}
