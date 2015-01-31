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
// Data: 2014-04-29
// Disciplina: MAC0323
// Este arquivo faz parte da tarefa T14
/////////////////////////////////////////////////////////////////

public class Ortografia {  
    public static void main(String[] args) {
        Stopwatch time = new Stopwatch();
        In in = new In(args[1]);
        int type;
        long memory;
        Runtime runtime = Runtime.getRuntime();
        if (args[0].equals("r") || args[0].equals("R")) {
            RedBlackBST<String, Integer> st;
            st = new RedBlackBST<String, Integer>(); 
            while (!in.isEmpty()) {
                String word = in.readString();
                st.put(word, 0);
            }
            while (!StdIn.isEmpty()) {
                String word = StdIn.readString();
                if (!st.contains(word))
                    type = 1;
                    StdOut.println(word);
            }
            StdOut.println("Tempo necessario usando RedBlackBST: "
            + time.elapsedTime());
            memory = runtime.totalMemory() - runtime.freeMemory();
            StdOut.println("Memoria consumida usando RedBlackBST em MBytes: "
            + memory / (1000000));
        } 
        else if (args[0].equals("s") || args[0].equals("S")) {
            SeparateChainingHashST<String, Integer> st;
            st = new SeparateChainingHashST<String, Integer>();
            while (!in.isEmpty()) {
                String word = in.readString();
                st.put(word, 0);
            }
            while (!StdIn.isEmpty()) {
                String word = StdIn.readString();
                if (!st.contains(word))
                    type = 1;
                    StdOut.println(word);
            }
            StdOut.println("Tempo necessario usando " 
            + "SeparateChainingHashST: " + time.elapsedTime());
            memory = runtime.totalMemory() - runtime.freeMemory();
            StdOut.println("Memoria consumida usando SeparateChainingHashST" 
            + " em MBytes: " + memory / (1000000));
        }
        else if (args[0].equals("l") || args[0].equals("L")) {
            LinearProbingHashST<String, Integer> st;
            st = new LinearProbingHashST<String, Integer>();    
            while (!in.isEmpty()) {
                String word = in.readString();
                st.put(word, 0);
            }
            while (!StdIn.isEmpty()) {
                String word = StdIn.readString();
                if (!st.contains(word))
                    type = 1;
                    StdOut.println(word);
            }
            StdOut.println("Tempo necessario usando " 
            + "LinearProbingHashST: " + time.elapsedTime());
            memory = runtime.totalMemory() - runtime.freeMemory();
            StdOut.println("Memoria consumida usando LinearProbingHashST "
            + "em MBytes: " + memory / (1000000));
        }
        else {
            StdOut.println("Opa! Nao entendi o tipo de tabela pedida");
        }
    }
}

/////////////////////////////////////////////////////////////////////
//  Manual
//  Para rodar o programa o programa use:
// Ortografia (Tipo de ST) (arquivo "dicionario") < (arquivo "texto")
//  No qual Tipo de ST é:
//      s para SeparateChainingHashST
//      r para RedBlackBST
//      l para LinearProbingHashST
//
//  Resultados
//  Após rodar o programa para cada uma das ST, foi possível observar
//  que a implementação que foi mais rápida nesses casos foi a 
//  LinearProbingHashST, seguida por RedBlackBST e a pior foi a 
//  implementação SeparateChainingHashST.
//  Rodando o programa  com entradas words.utf-8.txt e tale-PF.txt
//  os resultados foram em volta de:
//      3.467 segundos para SeparateChainingHashST
//      3.338 segundos para RedBlackBST
//      3.195 segundos para LinearProbingHashST
//  Vemos que a diferença não é muito grande com essa tabela de
//  símbolos com mais de 600 mil entradas. Então resolvi adicionar
//  na saída do programa a quantidade, em MegaBytes, de memória 
//  consumida, mas o valor continua sendo próximos nas 3 implementações.
//      167 MB para SeparateChainingHashST
//      134 MB para RedBlackBST
//      137 MB para LinearProbingHashST
//  A única implementação que foi um pouco pior foi a SeparateChainingHashST
//  que teve a maior quantidade de memória consumida e maior tempo.
//