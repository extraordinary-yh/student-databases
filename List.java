
/* DO NOT CHANGE:  This file is used in evaluation */

public class List<Arbitrary extends Base> {
        protected static final short END = 0;
        protected static final short FRONT = 1;

        private Node end;
        private long occupancy;

        public List () {
                end = null;
                occupancy = 0;
        }

        public Arbitrary insert (Arbitrary element, long where) {
                Arbitrary retval;
                Node new_node;

                /* store element in a Node */
                new_node = new Node (element);
                retval = new_node.data;

                /* is this the only element in the list??? */
                if (occupancy == 0)
                        end = new_node.next = new_node.pre = new_node;
                
                else {
                        new_node.next = end.next;
                        new_node.pre = end;
                        end.next.pre = new_node;
                        end.next = new_node;
                }

                if (where == END)
                        end = end.next;

                /* update occupancy */
                occupancy++;

                return retval;
        }

        public Arbitrary remove (long where) {
                Node old_node;          /* working node */
                Arbitrary retval;

                /* check status of list */
                if (occupancy == 0) {
                        System.err.print ("Popping from an empty list!!!\n");
                        return null;
                }

                /* adjust END if necessary to always remove from the FRONT */
                if (where == END)
                        end = end.pre;

                old_node = end.next;
                retval = old_node.data;

                /* remove old_node from list */
                old_node.next.pre = end;
                end.next = old_node.next;

                /* update occupancy */
                occupancy--;

                return retval;
        }

        public Arbitrary view (long where) {

                /* empty list */
                if (occupancy == 0)
                        return null;

                return (where == END) ? end.data : end.next.data;
        }

        public boolean isEmpty () {
                return size () == 0;
        }

        public long size () {
                return occupancy;
        }

        public String toString () {

                long count;             /* to know how many elements to print */
                Node current;           /* working node */
                String temp = "";       /* string to be returned */

                current = end.next;
                for (count = 1; count <= occupancy; count++) {
                        temp += "" + current;
                        current = current.next;
                }
                        
                return temp;
        }

        private class Node {
                public Arbitrary data;
                public Node pre;
                public Node next;

                public Node (Arbitrary element) {
                        data = element;
                        pre = null;
                        next = null;
                }
                public String toString () {
                        return "" + data;
                }
        }
}
