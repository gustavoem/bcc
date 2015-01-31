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

import java.util.Random;

public class CustoSondagemLinear {
    public static void main(String[] args) {
        Random gerador = new Random();
        int N = 100;

        if (args.length > 0)
            N = Integer.parseInt(args[0]);

        int tableSize = (int) (1.3 * N);

        LinearProbingHashST2<Integer, Integer> myHash;
        myHash = new LinearProbingHashST2<Integer, Integer>(tableSize);

        double maxAlpha = (double) (N - 1) / tableSize;
        double maxHit = 0.5 * (1 + 1 / (1 - maxAlpha)) + 1;
        double maxMiss = 0.5 * (1 + 1 / ((1 - maxAlpha) * ((1 - maxAlpha)))) + 1;
        VisualAccumulator2 hit;
        hit = new VisualAccumulator2(N, maxHit, "Hits",
        "Custo medio observado", "Custo medio segundo proposiçao M");
        VisualAccumulator2 miss;
        miss = new VisualAccumulator2(N, maxMiss, "Misses",
        "Custo medio observado", "Custo medio segundo proposiçao M");

        for (int i = 0; i < N - 1; i++) {
            myHash.put(gerador.nextInt(), i);

            double toquesM = myHash.proposicaoMHit();
            double toques = myHash.averageSearchHit();
            hit.addDataValue(toques, toquesM);
            StdOut.printf("\n Hit: %.3f HitM: %.3f", toques, toquesM);
            
            toquesM = myHash.proposicaoMMiss();
            toques = myHash.averageSearchMiss();
            miss.addDataValue(toques, toquesM);
            StdOut.printf(" || Miss: %.3f MissM: %.3f", toques, toquesM);
            StdOut.printf(" || Alpha: %.3f N: %d", (double) i / tableSize, i);
        }
    }
}

// Manual
// 
// O cliente CustoSondagemLinear insere N elementos aleatorios 
// na tabela de simbolos e a cada insercao o programa calcula o 
// custo medio de buscas mas e bem sucedidas na tabela. 
// O programa usa a classe VisualAccumulator2 para gerar dois 
// graficos de custo medio, um para buscas mas sucedidas e outro
// para buscas bem sucedidas.
// Os graficos ainda trazem de outra cor o custo medio das buscas
// segundo a proposicao M.
// O programa tambem imprime na entrada padrao o custo medio das
// buscas observada e esperada pela proposicao M seguido do valor
// de alfa (N/M).
// 
// Exemplo:
// Hit: 1.188 HitM: 1.235 || Miss: 1.480 MissM: 1.581 || Alpha: 0.300
// Para um N/M de 0.3, a busca bem sucedida na tabela de simbolos
// teve um custo medio 1.188 e a proposicao M diz que esse custo e 
// de 1.235. Ja a busca mal sucedida teve custo medio de 1.480 e
// a proposicao M diz que esse custo e de 1.581. 
// 
// Por padrao o programa insere 100 elementos aleatorios, mas e
// possivel determinar N se o programa for chamado com um 
// argumento.
//
// Resultados
// 
// Para valores de N/M nao proximos de 1 o valor observado e o 
// valor sugerido pela proposicao M ficaram bem proximos. Quando
// N/M e maior do que 70% os esses valores comecam a ficar mais
// distantes, tanto para operacoes de busca bem sucedidas quanto
// para operacoes de busca mal sucedidas.
// Essa diferenca fez com que, para alfas como 90%, os valores da
// proposicao M ficassem muito altos, deixando o grafico muito 
// truncado e dificil de ser observado. Sendo assim, decidi que 
// o tamanho da tabela de simbolos seria o piso de 1.3 * N, assim
// forcei o alfa a nao passar muito de 0.75, consequentemente nao
// houveram mais valores muito altos, facilitando a leitura do 
// grafico. 
// E interessante observar que o custo medio da operacao de busca
// cresce conforme aumenta o valor de alfa. Esse aumento de custo
// medio e causado pela formacao de clusters na tabela de simbolos,
// que como visto em aula, tendem a se formar conforme sao 
// inseridos elementos na tabela.
// Os clusters podem ser a explicacao para os "saltos" que a curva
// vermelha faz. Esses saltos devem ocorrer por conta de clusters
// que se juntam formando um cluster ainda maior, o que aumenta
// consideravelmente o custo medio de uma busca.
///////////////////////////////////////////////////////////////////
