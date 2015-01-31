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
// Data: 2014-06-05
// Disciplina: MAC0323
// Este arquivo faz parte da tarefa T19
/////////////////////////////////////////////////////////////////

public class Palindromo {
    private long wordHash;
    private long invertedHash;
    private long Q;
    private int R = 256;
    private long RM;

    public Palindromo() {
        Q = 997;
        RM = 1;
        wordHash = 0;
        invertedHash = wordHash;
    }

    public void addLetter(char c) {
        wordHash = newWordHash(c);
        invertedHash = newInvertedHash(c);
    }

    private long newWordHash(char c) {
        return (wordHash * R + (int) c) % Q;
    }

    private long newInvertedHash(char c) {
        long hash = (invertedHash + RM * ((int) c)) % Q;
        RM = (R * RM) % Q;
        return hash;
    }

    public boolean isPalindromo() {
        return wordHash == invertedHash;
    }

    public static void main(String[] args) {
        int counter = 0;
        Palindromo pal = new Palindromo();

        for (int i = 0; !StdIn.isEmpty(); i++) {
            char c = StdIn.readChar();
            pal.addLetter(c);
            if (pal.isPalindromo()) {
                counter++;
                StdOut.println(i);
            }
        }

        StdOut.println("Palindromos encontrados: " + counter);
    }
}