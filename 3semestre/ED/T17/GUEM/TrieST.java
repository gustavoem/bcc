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
// Data: 2014-05-22
// Disciplina: MAC0323
// Este arquivo faz parte da tarefa T17
/////////////////////////////////////////////////////////////////

//  Funções adicionadas/modificadas da classe TrieST.java
//
//  -min()      devolve a chave mínima da TrieST
//
//  -isEmpty()  verifica se a TrieST está vazia
//
//  -main()     recebe um arquivo da entrada padrão e imprime na
//  saída as palavras arquivo em ordem alfabética.

public class TrieST<Value> {

    private static final int R = 256;

    private Node root = new Node();

    private static class Node {
        private Object val;
        private Node[] next = new Node[R];
    }

    public Value get(String key) {
        Node x = get(root, key, 0);
        if (x == null) return null;
        return (Value) x.val;
    }

    private Node get(Node x, String key, int d) {
        if (x == null) return null;
        if (d == key.length()) return x;
        char c = key.charAt(d);
        return get(x.next[c], key, d+1);
    }

    public void put(String key, Value val) {
        root = put(root, key, val, 0);
    }

    private Node put(Node x, String key, Value val, int d) {
        if (x == null) 
            x = new Node();
        if (d == key.length()) {
            x.val = val;
            return x;
        }
        char c = key.charAt(d);
        x.next[c] = put(x.next[c], key, val, d+1);
        return x;
    }

    public void delete(String key) {
        root = delete(root, key, 0);
    }

    private Node delete(Node x, String key, int d) {
        if (x == null) return null;
        if (d == key.length()) x.val = null;
        else {
            char c = key.charAt(d);
            x.next[c] = delete(x.next[c], key, d+1);
        }
        if (x.val != null) return x;
        for (int c = 0; c < R; c++)
            if (x.next[c] != null)
                return x;
        return null;
    }

    public String min() {
        if (root == null) return null;
        String answer = "";
        Node x = root;
        while (x.val == null) {
            char c;
            for (c = 0; x.next[c] == null; c++);
            /*A*/
            x = x.next[c];
            answer += c;
        }
        return answer;
    }

//   
//  Em A vale que answer é um prefixo da chave mínima e c é a 
//  próxima letra dessa chave
///////////////////////////////////////////////////////////

    public boolean isEmpty() {
        if (root == null) return true;
        for (char c = 0; c < R; c++)
            if (root.next[c] != null)
                return false;
        return true;
    }

    public static void main(String[] args) {
        TrieST<Integer> st = new TrieST<Integer>();
        for (int i = 0; !StdIn.isEmpty(); i++) {
            String key = StdIn.readString();
            st.put(key, i);
        }
        while (!st.isEmpty()) {
            String minKey = st.min();
            st.delete(minKey);
            StdOut.println(minKey);
        }
    }
}
