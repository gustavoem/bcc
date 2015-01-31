import java.io.*;
import java.util.Scanner;

public class linearSystem {
    public static double[][] binomialTable = new double[651][651];

    public static void fillBinomialTable (){
        binomialTable[0][0] = 1;
        for (int i = 1; i < 650; i++) {
            binomialTable[i][0] = 1;
            binomialTable[0][i] = 0;
        }
        for (int n = 1; n <= 650; n++) {
            for (int k = 1; k <= n; k++) {
                binomialTable[n][k] = binomialTable[n-1][k-1] + binomialTable[n-1][k];
            }
        }
    }

    public static double inverseHiperGeometricP(int x, int n, int k, int N) {
        return (binomialCoefficient(k, x) * binomialCoefficient(N-k, n-x) / binomialCoefficient(N, n));
    }

    public static double binomialCoefficient(int n, int k) {
        return binomialTable[n][k];
    }


    public static void main(String[] args) throws IOException{
        fillBinomialTable();

        File decimaltxt = new File("decimal.txt");
        if (!decimaltxt.exists()) {
                decimaltxt.createNewFile();
        }
        FileWriter fwd = new FileWriter(decimaltxt.getAbsoluteFile());
        BufferedWriter bwd = new BufferedWriter(fwd);

        StdOut.println("se liga: " +inverseHiperGeometricP(1,5,30,649));
        StdOut.println("binomial(30, 1): " +binomialCoefficient(30, 1));
        StdOut.println("binomial(619, 4): " +binomialCoefficient(619, 4));

        for (int i = 0; i <= 649; i++) {
        // Ti,649(1 - P(xi=0)) - (Ti+1,649)*P(xi=1) - (Ti+2,649)*P(xi=2) - (Ti+3,649)*P(xi=3) - (Ti+4,649)*P(xi=4) - (Ti+5,649)*P(xi=5) = 1
            bwd.write("T"+i+"649*(" + (1 - inverseHiperGeometricP(0, 5, 649 - i, 649))+")" + 
            " - (T"+(i+1)+"649)*("+inverseHiperGeometricP(1, 5, 649 - i, 649)+")" +
            " - (T"+(i+2)+"649)*("+inverseHiperGeometricP(2, 5, 649 - i, 649)+")" +
            " - (T"+(i+3)+"649)*("+inverseHiperGeometricP(3, 5, 649 - i, 649)+")" +
            " - (T"+(i+4)+"649)*("+inverseHiperGeometricP(4, 5, 649 - i, 649)+")" +
            " - (T"+(i+5)+"649)*("+inverseHiperGeometricP(5, 5, 649 - i, 649)+") = 1\n");
        }
        bwd.close();
    }
}