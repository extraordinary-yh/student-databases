
/* DO NOT CHANGE:  This file is used in evaluation */

public class Stack<Arbitrary extends Base> extends List<Arbitrary> {

        public Arbitrary pop () {
                return remove (END);
        }

        public Arbitrary push (Arbitrary element) {
                return insert (element, END);
        }

        public Arbitrary top () {
                return view (END);
        }
}
