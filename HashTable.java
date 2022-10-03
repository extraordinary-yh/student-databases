/**
 * This class include the basic functionalities of a hashtable including
 * insert, locate, and lookup. 
 *
 * @author Mark Zeng (cs12fa19dm)
 */ 
public class HashTable extends Base {

        /* counters, flags and constants */
        private static int counter = 0;         // number of HashTables so far
        private static boolean debug;           // allocation of debug states
        protected static final short NULL = 0;  // in case you want to use NULL

        /* data fields */
        private long occupancy;         // number of items stored in table
        private int size;               // size of hash table
        private Base table[];   // the Hash Table itself ==> array of Base
        private int tableCount; // which hash table it is 

        /* initialized by Locate function */
        private int index;      // last location checked in hash table

        /* debug messages */
        private static final String DEBUG_ALLOCATE = " - Allocated]\n";
        private static final String DEBUG_INSERT = " - Insert]\n";
        private static final String DEBUG_LOCATE = " - Locate]\n";
        private static final String DEBUG_LOOKUP = " - Lookup]\n";
        private static final String FULL = " is full...aborting...]\n";
        private static final String HASH = "[Hash Table ";
        private static final String HASH_VAL = "[Hash value is: ";
        private static final String INSERT_BUMP = 
                                        "[bumping to next location...]\n";
        private static final String PROCESSING = "[Processing "; 
        private static final String TRYING = "[Trying index "; ; 

        /**
         * This class set debug state to off
         */
        public static void setDebugOff () {

                debug = false;
        }       

        /**
         * This class set debug state to on
         */
        public static void setDebugOn () {

                debug = true;
        }       
        
        /**
         * Constructer
         * Allocates and initializes the memory associated with a hash
         * table.
         *
         * @param  sz   the size of the table
         */
        public HashTable (int sz) {
                occupancy = 0;
		size = sz;
		table = new Base[size];
		counter++;
		tableCount = counter;

		/*debug messeges*/
		if(debug){
		System.err.print("Hash Table " + tableCount + DEBUG_ALLOCATE);
		}
        }

        /**
         * Performs insertion into the tabble via delegation to the
         * private insert method.
         *
         * @param   element       the element to be inserted
         * @return  true or false representing insertion success or not
         */
        public boolean insert (Base element) {
                return insert (element, false);
        }

        /**
         * Inserts the element in the hash table.
         * If the element cannot be inserted, false will be returned.  
         * If the element can be inserted, the element is inserted and true is
         * returned. Duplicate insertions will cause the existing element
         * to be deleted, and the duplicate element to take its place.
         *
         * @param   element        the element to be inserted
         * @param   recursiveCall  if we're recursively calling this function
         * @return  true or false  return true if insert is seccessful
         */
        private boolean insert (Base element, boolean recursiveCall) {
                Base tempElement;       /*used in bully algorithm*/
		if(debug){
			System.err.print(HASH + tableCount + DEBUG_INSERT);
			}
		
		/*prevent extra occupancy count when bumping*/ 
		if(recursiveCall == true){
			occupancy--;
		}

		if(locate(element) == null){
			/*full case*/
			if(occupancy == size){
				if(debug){
				System.err.print(HASH + tableCount + FULL);
				}
				return false;
			}
			/*the space is empty*/
			else if(table[index] == null){
				table[index] = element;
				occupancy++;
				return true;
			}
			/*bully algorithm*/
			else{
				if(debug){
				System.err.print(INSERT_BUMP);
				}
				tempElement = table[index];
				table[index] = element;
				insert(tempElement, true);
				occupancy++;
				return true;
			}
		}
		/*duplicate element*/
		else{
			table[index] = element;
		}
	               
	       	return true;
        }

        /**
         * Locates the index in the table where the insertion is to be performed
	 * An item is found, or an item is determined not to be there. Sets the
	 * variable index to the last location checked; it will be used by
	 * insert and lookup. Returns the item if an item with matching name is
	 * found. Otherwise, return null. Loops stops when encountering a null
	 * table location or when encountering an item that is smaller than the
	 * parameter item.
         *
         * @param   element  the element to be looked up
         * @return  element or null return the element if element is found,
	 *          otherwise return null. 
         */
        private Base locate (Base element) {
		int increment = 0;   //the increment used in algorithm
		int searchCount = 0;  //keep track of the time of search
                
		if(debug){
			System.err.print(HASH + tableCount + DEBUG_LOCATE);
			System.err.println(PROCESSING + element.getName()+ "]");
			System.err.println(HASH_VAL + element.hashCode()+"]");
		}
		
		index = element.hashCode() % size; //the initial index
		
		while(searchCount < size){
		if(debug){
			System.err.println(TRYING + index + "]");
		}
		/*if the position is null*/
		if(table[index] == null){
                	return null;
		}
		
		/*if the item found*/
		else if(table[index].equals(element)){
			return table[index];
		}
		
		/*if smaller item is in found*/
		else if (table[index].isLessThan(element)){
			return null;
		}
		/*find the next index*/
		increment = element.hashCode() % (size - 1) + 1;
		index = (index + increment) % size;
		searchCount++;
		}
                		
		return null; 
        }

        /**
         * This function looks up the element in the hash table. Returns the 
	 * element if found, null otherwise.
         *
         * @param   element  the element to be looked up
         * @return  pointer to the element or null. 
         */
        public Base lookup (Base element) {
                if(debug){
			System.err.print(HASH + tableCount + DEBUG_LOOKUP);
		}

		return  locate(element);
                
        }

        /**
         * Creates a string representation of the hash table. The method 
         * traverses the entire table, adding elements one by one
         * according to their index in the table. 
         *
         * @return  String representation of hash table
         */
        public String toString () {

                String string = "Hash Table " + tableCount + ":\n";
                string += "size is " + size + " elements, "; 
                string += "occupancy is " + occupancy + " elements.\n";

                /* go through all table elements */
                for (int index = 0; index < size; index++) {

                        if (table[index] != null) {
                                string += "at index " + index + ":  ";
                                string += "" + table[index] + "\n"; 
                        }
                }

                return string;
        }
}
