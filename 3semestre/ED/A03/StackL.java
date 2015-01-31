public class StackL<Item> {

    private Node first; 

    private class Node {
        private Item item;
        private Node next;
    }

    public boolean isEmpty() {
        return first == null;
    }

    public void push(Item item) {
        Node oldfirst = first;
        first = new Node();
        first.item = item;
        first.next = oldfirst;
    }

    public Item pop() {
        Item item = first.item;
        first = first.next;
        return item;
    }

    public void show() {
        Node x = first;
        int i = 0;
        while (x != null) {
            StdOut.println("No " + i + " " + x.item);
            i++;
            x = x.next;
        }
    }

    public void deleteLast() {
        first = deleteLast(first);
    }

    public Node deleteLast(Node x) {
        if (x.next == null)
            return null;
        else if (x.next.next == null) {
            x.next = null;
            return x;
        }
        else{
            x.next = deleteLast(x.next);
            return x;
        }
    }

    public static void main(String[] args) {
        StackL<Integer> interos = new StackL<Integer>();
        while (!StdIn.isEmpty()) {
            interos.push(StdIn.readInt());
        }
        interos.show();
    }
}