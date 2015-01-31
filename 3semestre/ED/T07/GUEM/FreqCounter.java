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
// Data: 2014-03-18
// Disciplina: MAC0323
// Este arquivo faz parte da tarefa T07
/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
// Use layout padrao. 
// Deste ponto em diante, nao escreva NENHUM comentario.
/////////////////////////////////////////////////////////////////

public class FreqCounter {

    public static void main(String[] args) {
        int minlen = Integer.parseInt(args[0]);
        int maxFreq = 0;
        int maxAccesses = 0;
        String lastWord = null;
        MyST<String, Integer> st = new MyST<String, Integer>();
        Queue<Integer> accessesQueue = new Queue<Integer>();
        while (!StdIn.isEmpty()) {
            String word = StdIn.readString();
            if (word.length() < minlen) 
                continue;
            Integer freq = st.get(word);
            if (freq == null) {
                freq = 0;
                lastWord = word;
            }
            st.put(word, freq + 1);
            if (freq + 1 > maxFreq)
                maxFreq = freq + 1;
            accessesQueue.enqueue(st.getAccessCounter());
            if (st.getAccessCounter() > maxAccesses)
                maxAccesses = st.getAccessCounter();
            st.setAccessCounter(0);
        }
        StdOut.println("Quantidade de palavras do texto: " + st.size());
        StdOut.println("Ultima palavra processada: " + lastWord);
        Queue<String> maxFreqWords = new Queue<String>(); 
        for (String word : st.keys()) {
            if (st.get(word) == maxFreq)
                maxFreqWords.enqueue(word);   
        }
        StdOut.println("Frequencia maxima: " + maxFreq + "\nPalavras:");
        while (!maxFreqWords.isEmpty()) {
            String word = maxFreqWords.dequeue();
            StdOut.println(word);
        }
        VisualAccumulator plot;
        plot = new VisualAccumulator(accessesQueue.size(), maxAccesses);
        while (!accessesQueue.isEmpty()) {
            plot.addDataValue(accessesQueue.dequeue());
        }
    }
}