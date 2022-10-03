import java.io.*;

/* DO NOT CHANGE:  This file is used in evaluation */

public class Main {
        public static void main (String [] args) {

                /* initialize debug states */
                Tree.debugOff();

                /* check command line options */
                for (int index = 0; index < args.length; ++index) {
                        if (args[index].equals("-x"))
                                Tree.debugOn();
                }
        
                Calculator calc = new Calculator ();    // Calculator to use

                while (true) {
                        System.out.print
                          ("\nPlease enter an expression to calculate:  ");

                        try {
                                calc.convertInToPost ();
                        }

                        catch (EOFException eof) {
                                break;
                        }

                        System.out.println ("\nThe expression in postfix " +
                                "order is:  " + calc.writePostfix());

                        System.out.println ("which evaluates to:  "
                                + calc.evaluate ());

                        System.out.println("Calculator is:\n" + calc);
                }
                System.out.print ("\n");
        }
}
