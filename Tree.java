/**
 * this class implements a binary tree sturcture, with methods
 * including insert, lookup , remove and write.
 *
 * @author Mark Zeng(cs12fa19dm)
 */
public class Tree<Whatever extends Base> extends Base {

        /* data fields */
        private TNode root;
        private long occupancy; 
        private String treeName;

        /* debug flag */
        private static boolean debug;

        /* debug messages */
        private static final String ALLOCATE = " - Allocating]\n";
        private static final String AND = " and ";
        private static final String COMPARE = " - Comparing ";
        private static final String INSERT = " - Inserting ";
        private static final String TREE = "[Tree ";

        /**
	 * Constructer
	 * Allocates and initializes the memory associated with
	 * the Tree object.
	 *
	 * @param takes in a string name
	 */
        public Tree (String name) {
		treeName = name;
		occupancy = 0;
		root = null;
		if(debug){
			System.err.print(TREE + name + ALLOCATE);
		}	
        }
   	
	/**
         * This method set debug state to on
         */
        public static void debugOff () {

                debug = false;
        }
        /**
         * This method set debug state to on
         */
      	public static void debugOn () {

                debug = true;
        }

        /**
         * Returns the tree's name
         * 
	 * @return name of the tree
         */
        public String getName() {
                return treeName;
        }
	
	/**
	 * Return if the tree is empty
	 *
	 * @return true if empty, false if otherwise
	 */
	public boolean isEmpty () {
		if(occupancy == 0){
			return true;
		}
		else{
			return false;
		}
	}
        
	/**
	 * This method updates height of each node after insert
	 * 
	 * @param The Node that needs to be updated
	 */
	public void updateHeight(TNode current) {
		/*check if height realy needs to be updated*/
		if(current.left != null && current.right != null){
			return ;
		}
		/*update the height*/
		while(true){
			current.height++;
			/*check root*/
			if(current.parent == null)
				break;
			current = current.parent;
		}
	}

	/**
	 * This method updates balance of each node after insert
	 *
	 * @param The Node needs to be updated
	 */
	public void updateBalance(TNode current) {
		long leftHeight; /*the height of left node*/
		long rightHeight;/*the height of right node*/
		
		/*check balance*/
		while(true) {
			/*check left*/
			if(current.left == null){
				leftHeight = -1;
			}
			else{
				leftHeight = current.left.height;
			}
			/*check right*/
			if(current.right == null){
				rightHeight = -1;
			}
			else{
				rightHeight = current.right.height;
			}
                        current.balance = leftHeight - rightHeight;
			/*check root*/
			if(current.parent == null)
				break;
			current = current.parent;
		}
	}
		
	/**
	 * This method inserts the element into the binary tree.returns true or
	 * false indicating seccess of insertion
	 *
	 * @param element is the complete element to be inserted
	 * @return true or false indicating seccess of insertion
	 */
        public boolean insert (Whatever element) {
                TNode current;   /*used to keep track of the current node*/
	
		/*check if root exist*/
		if(root == null){
			if(debug){
				System.err.println(TREE + treeName + INSERT +
						element.getName() + "]");
			}
			root = new TNode(element);
                	return true;
		}
		current = root;
		while(true){	
			if(debug){
				System.err.println(TREE + treeName + COMPARE +
						element.getName() + AND +
					       	current.data.getName() + "]");
			}
			/*check to go right or left*/
			if(element.isGreaterThan(current.data)){
				/*check if right exists*/
				if(current.right == null){
					current.right = new TNode(element);
					current.right.parent = current;
					updateHeight(current);
					updateBalance(current);
					if(debug){
						System.err.println(TREE + 
						treeName + INSERT +
						element.getName() + "]");
					}
					return true;
				}
				/*go right*/
				else{
					current = current.right;
					continue;
				}
			}
			else{
				/*check if left exist*/
				if(current.left == null){
					current.left = new TNode(element);
					current.left.parent = current;
					updateHeight(current);
					updateBalance(current);
					if(debug){
						System.err.println(TREE + 
						treeName + INSERT +
						element.getName() + "]");
					}
					return true;
				}
				/*go left*/
				else{
					current = current.left;
					continue;
				}
			}
		}
        }
        
	/**
	 * this method Looks up the matching data in the binary tree. 
	 * Returns a pointer to the data if found, null otherwise. 
	 *
	 * @param the element to be looked up
	 * @return a pointer to the data if found, null otherwise
	 */
        public Whatever lookup (Whatever element) {
		TNode current; /*used to keep track of the current node*/
                
		/*check if root exists*/
		if(root == null){
			return null;
		}
                current = root;
		
		/*checking down the tree*/
		while(true){
			if(debug){
				System.err.println(TREE + treeName + COMPARE +
						element.getName() + AND +
						current.data.getName() + "]");
			}
			/*go right?*/
			if(element.isGreaterThan(current.data)){
				/*find nothing*/
				if(current.right == null){
					return null;
				}
				else{
					current = current.right;
					continue;
				}
			}
			/*found*/
			else if(element.equals(current.data)){
				/*deleted?*/
				if(current.hasBeenDeleted == false){
					return current.data;
				}
				else{
					return null;
				}
			}
			/*go left?*/
			else{
				/*find nothing*/
				if(current.left == null){
					return null;
				}
				else{
					current = current.left;
					continue;
				}
			}
		}
        }
	
	/**
	 * this method removes the matching data in the binary tree. 
	 * Returns a pointer to the data if found, null otherwise. 
	 *
	 * @param the element to be looked up
	 * @return a pointer to the data if found, null otherwise
	 */
        public Whatever remove (Whatever element) {
 		TNode current; /*used to keep track of the current node*/
                
		/*check if root exists*/
		if(root == null){
			return null;
		}
                current = root;
		
		/*checking down the tree*/
		while(true){
			if(debug){
				System.err.println(TREE + treeName + COMPARE +
						element.getName() + AND +
						current.data.getName() + "]");
			}
			/*go right?*/
			if(element.isGreaterThan(current.data)){
				/*find nothing*/
				if(current.right == null){
					return null;
				}
				else{
					current = current.right;
					continue;
				}
			}
			/*found*/
			else if(element.equals(current.data)){
				/*deleted?*/
				if(current.hasBeenDeleted == false){
					current.hasBeenDeleted = true;
					occupancy--;
					return current.data;
				}
				else{
					return null;
				}
			}
			/*go left?*/
			else{
				/*find nothing*/
				if(current.left == null){
					return null;
				}
				else{
					current = current.left;
					continue;
				}
			}
		}
        }

        /**
         * Creates a string representation of this tree. This method first
         * adds the general information of this tree, then calls the
         * recursive TNode function to add all nodes to the return string 
         *
         * @return  String representation of this tree 
         */
        public String toString () {
                String string = "Tree " + treeName + ":\noccupancy is ";
                string += occupancy + " elements.";

                if(root != null)
                        string += root.writeAllTNodes();

                return string;
        }

	/**
	 * this class implements basic methods of a treenode, including
	 * a constructor , toSrting method and writeAllNodes mathods.
	 *
	 * @author Mark Zeng(cs12fa19dm)
	 */
        private class TNode {

                public Whatever data;
                public TNode left, right, parent;
                public boolean hasBeenDeleted;

                /* left child's height - right child's height */
                public long balance;
                /* 1 + height of tallest child, or 0 for leaf */
                public long height;
                
		/**
		 * Constructor
		 * allocate and initializes the memory associated with
		 * the TNode object
		 * 
		 * @param element is the data stored in the TNode
		 */
                public TNode (Whatever element) {
			data = element;
			left = null;
			right = null;
			parent = null;
			hasBeenDeleted = false;
			balance = 0;
			height = 0;
			occupancy++;
                }

                /**
                 * Creates a string representation of this node. Information
                 * to be printed includes this node's height, its balance,
                 * and the data its storing.
                 *
                 * @return  String representation of this node 
                 */

                public String toString () {
                        return "at height:  " + height + "  with balance: " +
                                balance + "  " + data;
                }

                /**
                 * Writes all TNodes to the String representation field. 
                 * This recursive method performs an in-order
                 * traversal of the entire tree to print all nodes in
                 * sorted order, as determined by the keys stored in each
                 * node. To print itself, the current node will append to
                 * tree's String field.
                 */
                public String writeAllTNodes () {
                        String string = "";
                        if (left != null)
                                string += left.writeAllTNodes ();
                        if (!hasBeenDeleted) 
                                string += "\n" + this;          
                        if (right != null)
                                string += right.writeAllTNodes ();

                        return string;
                }
        }
}
