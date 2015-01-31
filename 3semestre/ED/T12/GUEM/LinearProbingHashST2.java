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
// Data: 2014-04-22
// Disciplina: MAC0323
// Este arquivo faz parte da tarefa T12
/////////////////////////////////////////////////////////////////

public class LinearProbingHashST2<Key, Value> {

    private int N;       
    private int M = 16;
    private int toques = 0;  
    private Key[] keys;  
    private Value[] vals;
    
    public LinearProbingHashST2() {
        keys = (Key[])   new Object[M];
        vals = (Value[]) new Object[M];
    }

    public LinearProbingHashST2(int cap) {
        M = cap;
        keys = (Key[])   new Object[M];
        vals = (Value[]) new Object[M];
    }

    public double proposicaoMHit() {
        return (0.5 * (1 + 1 / (1 - alpha())));
    }

    public double proposicaoMMiss() {
        return (0.5 * (1 + 1 / ((1 - alpha()) * (1 - alpha()))));
    }

    private double alpha() {
        return (double) N / M;
    }

    public double averageSearchHit() {
        int totalToques = 0;
        int chaves = 0;
        for (int i = 0; i < M; i++) {
            if (keys[i] != null) {
                Value fulano;
                chaves++;
                toques = 0;
                fulano = get(keys[i]);
                totalToques += toques;
            }
        }
        return (double) totalToques / chaves;
    }

    public double averageSearchMiss() {
        int totalToques = 0;
        for (int i = 0; i < M; i++) {
            toques = 1;
            for (int j = i; keys[j] != null; j = (j + 1) % M)
                toques++;
            totalToques += toques;
        }
        return (double) totalToques / M;
    }

    private int hash(Key key) {
        return (key.hashCode() & 0x7fffffff) % M;
    }

    public void put(Key key, Value val) {
        int i;
        for (i = hash(key); keys[i] != null; i = (i + 1) % M) 
            if (keys[i].equals(key)) { 
                vals[i] = val; 
                return; 
            }
        keys[i] = key;
        vals[i] = val;
        N++;
    }

    public Value get(Key key) {
        for (int i = hash(key); keys[i] != null; i = (i + 1) % M) {
            toques++;
            if (keys[i].equals(key))
                return vals[i];
        }
        return null;
    }
}