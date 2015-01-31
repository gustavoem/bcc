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
// Data: 2014-03-25
// Disciplina: MAC0323
// Este arquivo faz parte da tarefa T09
/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
// Use layout padrao. 
// Deste ponto em diante, nao escreva NENHUM comentario.
/////////////////////////////////////////////////////////////////

import java.util.Arrays;

public class PerfectBalance {
    private static void balancedput(int[] keys, BST<Integer, Integer> balancedBst) {
        balancedput(keys, 0, keys.length - 1, balancedBst);
    }

    private static void balancedput(int[] keys, int begin, int end,
    BST<Integer, Integer> balancedBst) {
        if (begin > end) return;
        int mid = (begin + end) / 2;
        balancedBst.put(keys[mid], mid);
        balancedput(keys, begin, mid - 1, balancedBst);
        balancedput(keys, mid + 1, end, balancedBst);   
    }

    public static void main(String[] args) {
        BST<Integer, Integer> balancedBst = new BST<Integer, Integer>();
        BST<Integer, Integer> bst = new BST<Integer, Integer>();
        int[] keys = StdIn.readAllInts();
        for (int i = 0; i < keys.length; i++)
            bst.put(keys[i], i);
        Arrays.sort(keys);
        balancedput(keys, balancedBst);
        StdOut.println("Numero de nos: " + keys.length);
        StdOut.println("Altura da arvore padrao: " + bst.height());
        StdOut.println("Altura da arvore balanceada: " + balancedBst.height());
        double logn = Math.log(keys.length) / Math.log(2);
        StdOut.println("|_ lg N _| = " + Math.floor(logn));
    }

}