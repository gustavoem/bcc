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
// Este arquivo faz parte da tarefa Topcional
/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
// Use layout padrao. 
// Deste ponto em diante, nao escreva NENHUM comentario.
/////////////////////////////////////////////////////////////////

import java.util.NoSuchElementException;

public class BSTwithCaching<Key extends Comparable<Key>, Value> {

   private Node root;
   private Node lastNode;

   private class Node {
      private Key key;
      private Value val;
      private Node left, right;

      public Node(Key key, Value val) {
         this.key = key;
         this.val = val;
      }
   }

   public Value get(Key key) {
      if (lastNode != null) {
         int cmp = key.compareTo(lastNode.key);
         if (cmp == 0)
            return lastNode.val;
      }
      return get(root, key);
   }

   private Value get(Node x, Key key) {
      // Considera apenas a subárvore que tem raiz x
      if (x == null) return null;
      int cmp = key.compareTo(x.key);
      if      (cmp < 0) return get(x.left, key);
      else if (cmp > 0) return get(x.right, key);
      else {
         lastNode = x;
         return x.val;
      }
   }

   public void put(Key key, Value val) {
      if (lastNode != null) {
         int cmp = key.compareTo(lastNode.key);
            if (cmp == 0) {
               lastNode.val = val;
               return;
            }
      }
      root = put(root, key, val);
   }

   private Node put(Node x, Key key, Value val) {
      if (x == null) return new Node(key, val);
      int cmp = key.compareTo(x.key);
      if      (cmp < 0) x.left = put(x.left, key, val);
      else if (cmp > 0) x.right = put(x.right, key, val);
      else 
         x.val = val;
         lastNode = x;
      return x;
   }
}