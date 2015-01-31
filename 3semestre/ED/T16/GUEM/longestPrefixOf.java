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
// Este arquivo faz parte da tarefa T16
/////////////////////////////////////////////////////////////////
    
/*
Invariante:
prefixLocation guarda o indice de query tal que a substring
query.substring(0, prefixLocation) é a maior chave da tabela que é prefixo de
query.substring(0, d)
*/

public String longestPrefixOf(String query) {
    int prefixLocation = -1;
    Node protagonist = root;

    for (int d = 0; d < query.length() && protagonist != null; d++) {
        protagonist = protagonist.next[query.charAt(d)];
        if (protagonist == null)
            break;
        if (protagonist.val != null) 
            prefixLocation = d;
        }

    if (prefixLocation == -1)
        return null;
    return query.substring(0, prefixLocation + 1);
}