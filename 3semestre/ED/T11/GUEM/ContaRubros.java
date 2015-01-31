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
// Data: 2014-04-08
// Disciplina: MAC0323
// Este arquivo faz parte da tarefa T11
//////////////////////////////////////////////////////////////////

//  Manual
//
//  O programa ContaRubros faz ao menos 100 calculos de frequencia
//  de links vermelhos da arvore e devolve a media das frequencias
//  para arvores com 10^4, 10^5 e 10^6 nos. O programa tambem
//  devolve a menor frequencia e a maior frequencia de links
//  vermelhos observados.
//
//  Para fazer mais testes rode o programa passando um inteiro 
//  como argumento. Se o inteiro for menor do que 100 ou nao  
//  houver passagem de parametros o programa fara, por padrao, 100
//  testes.
//////////////////////////////////////////////////////////////////

//  Resultados
//
//  Foi possivel observar que a frequencia media de links
//  vermelhos e de 0.25.
//  Isso acontece porque uma arvore rubro-negra so pode ter links
//  vermelhos que vao para a esquerda. Sendo assim, apenas metade
//  dos links poderiam ser vermelhos, logo a porcentagem de links
//  vermelhos esta entre 0 e 0.5.
//  Podemos ter qualquer porcentagem de nos vermelhos entre 0 e 
//  0.5. Porém, os casos onde ha frequencias proximas a 0 e 0.5
//  sao casos mais isolados e dificeis de acontecer. Lembrando que
//  as nossas entradas sao aleatorias, as frequencias observadas
//  tendem a "fugir" desses casos extremos e se concentram no caso
//  medio, perto de 0.25.
//  Essa tendencia de fugir dos extremos e apresentada no programa
//  pelos resultados de porcentagem maxima e porcentagem minima,
//  que sao proximos de 0.25 e nao diferem muito um do outro.
//////////////////////////////////////////////////////////////////

import java.util.Random;

public class ContaRubros {
    public static void main(String[] args) {
        Random gerador = new Random();
        RedBlackBST2<Integer, Integer> myBST;
        int testsN = 100;
        int entriesN = 10000;

        if (args.length > 0 && Integer.parseInt(args[0]) > 100)
            testsN = Integer.parseInt(args[0]);

        for (int k = 4; k <= 6; k++) {
            double maxPercent = 0;
            double minPercent = 1;
            double percentM = 0;
            for (int i = 0; i < testsN; i++) {
                myBST = new RedBlackBST2<Integer, Integer>();
                for (int j = 0; j < entriesN; j++) {
                    myBST.put(gerador.nextInt(), j);
                }
                double percent = myBST.redPercent();
                percentM += percent;
                if (percent > maxPercent)
                    maxPercent = percent;
                if (percent < minPercent)
                    minPercent = percent;
            }
            percentM /= testsN;
            System.out.printf("Porcenagem media de links vermelhos para" 
            +" 10^%d entradas apos " + testsN +" testes: %.4f\n", k, percentM);
            System.out.printf("Porcentagem maxima: %.4f\n", maxPercent);
            System.out.printf("Porcentagem minima: %.4f\n\n", minPercent);
            entriesN *= 10;
        }
    }
}