// DECLARO QUE SOU O UNICO AUTOR E RESPONSAVEL POR ESTE PROGRAMA. 
// TODAS AS PARTES DO PROGRAMA (EXCETO AS QUE FORAM FORNECIDAS 
// PELO PROFESSOR OU COPIADAS DO LIVRO OU DA BIBLIOTECA DE 
// SEDGEWICK E WAYNE) FORAM DESENVOLVIDAS POR MIM.  DECLARO 
// TAMBEM QUE SOU RESPONSAVEL POR TODAS AS COPIAS DESTE PROGRAMA
// E QUE NAO DISTRIBUI NEM FACILITEI A DISTRIBUICAO DE COPIAS. 
//
// Nome: Gustavo Estrela de Matos
// NUSP: 8536051
// Sigla: GUEM
//
// Data: 2014-04-08
// Disciplina: MAC0323
// Este arquivo faz parte da tarefa T11
/////////////////////////////////////////////////////////////////

public class RedBlackBST2<Key extends Comparable<Key>, Value> {
    private static final boolean RED   = true;
    private static final boolean BLACK = false;

    private Node root; 
    private int N;

    private class Node {
        private Key key;       
        private Value val;       
        private Node left, right;  
        private boolean color;    

        public Node(Key key, Value val, boolean color) {
            this.key = key;
            this.val = val;
            this.color = color;
        }
    }

    public Value get(Key key) { return get(root, key); }
    public Value get(Node x, Key key) {
        while (x != null) {
            int cmp = key.compareTo(x.key);
            if      (cmp < 0) x = x.left;
            else if (cmp > 0) x = x.right;
            else              return x.val;
        }
        return null;
    }

    public boolean contains(Key key) {
        return (get(key) != null);
    }

    public void put(Key key, Value val) {
        root = insert(root, key, val);
        root.color = BLACK;
        assert check();
    }

    private Node insert(Node h, Key key, Value val) { 
        if (h == null) {
            N++;
            return new Node(key, val, RED);
        }

        int cmp = key.compareTo(h.key);
        if      (cmp < 0) h.left  = insert(h.left,  key, val); 
        else if (cmp > 0) h.right = insert(h.right, key, val); 
        else              h.val   = val;

        if (isRed(h.right) && !isRed(h.left))      h = rotateLeft(h);
        if (isRed(h.left)  &&  isRed(h.left.left)) h = rotateRight(h);
        if (isRed(h.left)  &&  isRed(h.right))     flipColors(h);

        return h;
    }

    private boolean isRed(Node x) {
        if (x == null) return false;
        return (x.color == RED);
    }

    private Node rotateRight(Node h) {
        assert (h != null) && isRed(h.left);
        Node x = h.left;
        h.left = x.right;
        x.right = h;
        x.color = h.color;
        h.color = RED;
        return x;
    }

    private Node rotateLeft(Node h) {
        assert (h != null) && isRed(h.right);
        Node x = h.right;
        h.right = x.left;
        x.left = h;
        x.color = h.color;
        h.color = RED;
        return x;
    }

    private void flipColors(Node h) {
        assert !isRed(h) && isRed(h.left) && isRed(h.right);
        h.color = RED;
        h.left.color = BLACK;
        h.right.color = BLACK;
    }

    public int size() {
        return N;
    }

    public boolean isEmpty() {
        return N == 0;
    }

    public int height() { return height(root); }

    private int height(Node x) {
        if (x == null) return -1;
        return 1 + Math.max(height(x.left), height(x.right));
    }

    public Key min() { return min(root); }

    private Key min(Node x) {
        Key key = null;
        while (x != null) {
            key = x.key;
            x = x.left;
        }
        return key;
    }

    public Key max() { return max(root); }

    private Key max(Node x) {
        Key key = null;
        while (x != null) {
            key = x.key;
            x = x.right;
        }
        return key;
    }

    public Iterable<Key> keys() {
        Queue<Key> queue = new Queue<Key>();
        keys(root, queue);
        return queue;
    }

    private void keys(Node x, Queue<Key> queue) { 
        if (x == null) return; 
        keys(x.left, queue); 
        queue.enqueue(x.key); 
        keys(x.right, queue); 
    } 

    private boolean check() {
        if (!isBST())            StdOut.println("Not in symmetric order");
        if (!is23())             StdOut.println("Not a 2-3 tree");
        if (!isBalanced())       StdOut.println("Not balanced");
        return isBST() && is23() && isBalanced();
    }

    private boolean isBST() {
        return isBST(root, null, null);
    }

    private boolean isBST(Node x, Key min, Key max) {
        if (x == null) return true;
        if (min != null && x.key.compareTo(min) <= 0) return false;
        if (max != null && x.key.compareTo(max) >= 0) return false;
        return isBST(x.left, min, x.key) && isBST(x.right, x.key, max);
    } 

    private boolean is23() { return is23(root); }

    private boolean is23(Node x) {
        if (x == null) return true;
        if (isRed(x.right)) return false;
        if (x != root && isRed(x) && isRed(x.left))
            return false;
        return is23(x.left) && is23(x.right);
    } 

    private boolean isBalanced() { 
        int black = 0; 
        Node x = root;
        while (x != null) {
            if (!isRed(x)) black++;
            x = x.left;
        }
        return isBalanced(root, black);
    }

    private boolean isBalanced(Node x, int black) {
        if (x == null) return black == 0;
        if (!isRed(x)) black--;
        return isBalanced(x.left, black) && isBalanced(x.right, black);
    }

    public double redPercent() {
        if (N > 0)
            return ((double) redCount())/N;
        return -1;
    }

    public int redCount() {
        return redCount(root);
    }

    public int redCount(Node x) {
        if (x == null) return 0;
        if (isRed(x))  return 1 + redCount(x.right) + redCount(x.left);
        else           return 0 + redCount(x.right) + redCount(x.left);
    }
} 



