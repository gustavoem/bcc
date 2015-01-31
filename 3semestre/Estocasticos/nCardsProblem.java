import java.util.Random;
import java.lang.Math;
import java.util.Arrays;
import java.io.*;
import java.util.Scanner;

public class nCardsProblem{

    public static void testRandomNumbers() {
        Random gerador = new Random();
        double[] numbers = new double[10000];
        int nNumbers = numbers.length;
        graphPlot graph = new graphPlot(nNumbers, 100, "Teste do gerador de números pseudo-aleatórios");

        for (int i = 0; i < nNumbers; i++) {
            int x = gerador.nextInt(100 + 1);
            graph.addDataValue(i, x);
            numbers[i] = x;
        }

        graph.text(0.5 * nNumbers, 20, "Resultados do teste para "+ nNumbers + " números pseudo-aleatórios:");
        graph.text(0.5 * nNumbers, 0, "Média: " + graphPlot.doubleToString(graphPlot.mean(numbers)));
        graph.text(0.5 * nNumbers, 10, "Variância: " + graphPlot.doubleToString(graphPlot.var(numbers)));
    }

    //  Esta função recebe um inteiro com o tamanho de cada pacote
    //  e no vetor v, marca quais cartas foram recolhidas. Também
    //  devolve a quantidade de cartas que foram recolhidas.
    public static int openNewPack(int packSize, int[] v) {
        Random rnd = new Random();
        int collectedCards = 0;
        for (int i = 0; i < packSize; i++) {
            int x = rnd.nextInt(649);
            if (v[x] != 1) {
                collectedCards++;
                v[x] = 1;
            }
        }
        return collectedCards;
    }

    //  Esta função recebe o tamanho de cada pacote e devolve um
    //  valor inteiro com o número de pacotes que foram abertos 
    //  para completar um álbum.
    public static int completeAlbuma(int packSize) {
        int[] v = new int[649];
        int collectedCards = 0;
        int openedPacks = 0;
        while (collectedCards < 649) {
            collectedCards += openNewPack(packSize, v);
            openedPacks++;
        }
        return openedPacks;
    }

    //  Esta função calcula quantos pacotes são abertos para
    //  completar 5 álbuns, considerando um pacote com tamanho 5
    //  em que a i-ésima figurinha vai sempre para o i-ésimo album. 
    //  1<=i<=5
    public static int completeAlbumb() {
        int[][] v = new int[5][649];
        int collectedCards = 0;
        int openedPacks = 0;
        Random rnd = new Random();
        while (collectedCards < 649 * 5) {
            for (int i = 0; i < 5; i++){
                int card = rnd.nextInt(649);
                if (v[i][card] == 0) {
                    v[i][card] = 1;
                    collectedCards++;
                }
            }
            openedPacks++;
        }
        return openedPacks;
    }

    public static int completeAlbumc() {
        int[][] v = new int[5][649];
        int collectedCards = 0;
        int openedCards = 0;
        Random rnd = new Random();
        while (collectedCards < 649 * 5) {
            openedCards++;
            int card = rnd.nextInt(649);
            int i;
            for (i = 0; i < 5 && v[i][card] != 0; i++);
            if (i < 5) {
                v[i][card] = 1;
                collectedCards++;
            }
        }
        return (int) (openedCards / 5) + 1;
    }

    // Recebe um vetor x, o valor mínimo da primeira barra e um coeficiente que define a ordem dos números (10^n)
    // A função cria um vetor com as frequências observadas em x de certos intervalos.
    public static void buildHistogram(double[] x, int firstBar, int coef) {
        int outliers = 0;
        double[] histogramBars = new double[10];

        for (int i = 0; i < 10; i++)
            histogramBars[i] = 0;
      
        for (int i = 0; i < x.length; i++) {
            int bar = (int) x[i] / (int) Math.pow(10, coef);
            bar -= firstBar;
            if (bar < 0 || bar > 9)
                outliers++;
            else
                histogramBars[bar]++;
        }

        graphPlot histograma = new graphPlot();
        histograma.plotBars(x, histogramBars, (int) (firstBar * Math.pow(10, coef)), (int) Math.pow(10, coef), "Frequência de figurinhas compradas para completar a tarefa "
        + x.length +" vezes.");
    }

    // Recebe um vetor x e escreve seus valores em um arquivo
    public static void writeVector(double[] x) throws IOException{
        File decimaltxt = new File("v.txt");
        if (!decimaltxt.exists()) {
                decimaltxt.createNewFile();
        }
        FileWriter fwd = new FileWriter(decimaltxt.getAbsoluteFile());
        BufferedWriter bwd = new BufferedWriter(fwd);

        for (int i = 0; i < x.length; i++)
            bwd.write(i+1 + " " + x[i] + "\n");
        bwd.close();
    }

    //  Manual
    //
    //  
    //  java nCardsProblem [Tipo do teste] [Número de testes]
    //  [Quantidade de cartas no pacote]
    //
    /***************************************************************/
    //  Tipo do teste
    //
    //  a - completa [Número de testes] vezes 1 album com pacotes de
    //  [Numero de figurinhas em cada pacote] figurinhas.
    //  Para rodar esse modo é necessário passar como argumentos o 
    //  número de testes e o número de figurinhas em cada pacote.
    //
    //  b - completa [Número de testes] vezes 5 albuns considerando 
    //  que cada pacote tem 5 figurinhas em que a i-ésima
    //  figurinha vai sempre para o i-ésimo album. 1<=i<=5
    //  Para rodar esse modo é necessário passar como argumento o 
    //  número de testes
    //  
    //  c - completa [Número de testes] vezes 5 albuns considerando 
    //  que cada pacote tem 5 figurinhas em que cada figurinha 
    //  sorteada vai para o primeiro albúm que ainda não tem essa
    //  figurinha.
    //  Para rodar esse modo é necessário passar como argumento o 
    //  número de testes
    //  
    //  t - testa o gerador de numeros aleatórios
    /***************************************************************/
    //  Número de testes
    //  
    //  Um numero inteiro que define quantas vezes o programa
    //  resolverá o mesmo problema
    /***************************************************************/
    //  Quantidade figurinhsa em um pacote
    //
    //  Um numero inteiro que define quantas cartas vem em um pacote
    //  Esse argumento só é necessário se estiver sendo rodado com 
    //  [Tipo do teste] sendo "a".
    /////////////////////////////////////////////////////////////////

    public static void main(String[] args) throws IOException{   

        if (args[0].equals("t")) {
            testRandomNumbers();
            return; 
        }

        int testsNumber = Integer.parseInt(args[1]);
        int packSize;
        double[]  packsNeeded = new double[testsNumber];
        
        if (args[0].equals("a")) {
            for (int i = 0; i < testsNumber; i++){
                packSize = Integer.parseInt(args[2]);
                int openedPacks;
                openedPacks = completeAlbuma(packSize);
                packsNeeded[i] = openedPacks;
                System.out.println("Numero de pacotes comprados: " + openedPacks);
            }
        }

        else if (args[0].equals("b")) { 
            for (int i = 0; i < testsNumber; i++){
                packSize = 5;
                int openedPacks;
                openedPacks = completeAlbumb();
                packsNeeded[i] = openedPacks;
                System.out.println("Numero de pacotes comprados: " + openedPacks);
            }
        }
        else if (args[0].equals("c")) {
            for (int i = 0; i < testsNumber; i++){
                packSize = 5;
                int openedPacks;
                openedPacks = completeAlbumc();
                packsNeeded[i] = openedPacks;
                System.out.println("Numero de pacotes comprados: " + openedPacks);
            }
        }
        else {
            System.out.println("Opa! Opção inválida");
        }

        writeVector(packsNeeded);
        double media = graphPlot.mean(packsNeeded);
        double var = graphPlot.var(packsNeeded);
        System.out.println("Média de pacotes comprados: " + media);
        if (args[0] == "b" || args[0] == "c")
            System.out.println("Média de pacotes comprados: " + media);
        System.out.println("Variância: " + var);
        String num = "" + (int) media;
        int coefm = num.length();
        num = "" + (int) var;
        int coefv = num.length();
        int firstBar = (int) (media / Math.pow(10, coefm - 1)) - (int) (var / Math.pow(10, coefv - 1));
        buildHistogram(packsNeeded, firstBar, coefm - 1);
    }
}
