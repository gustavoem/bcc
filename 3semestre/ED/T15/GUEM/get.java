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
// Data: 2014-05-06
// Disciplina: MAC0323
// Este arquivo faz parte da tarefa T15
/////////////////////////////////////////////////////////////////

public Value get(String key) {
    Node x = root.next[key.charAt(0)];
    Value valor = null;
    for (int i = 1; x != null && i <= key.length(); x = x.next[key.charAt(i++)]){   
   		if (x == null) return null;
        if (i == key.length()) return (Value) x.val;
    }
    return valor;
}