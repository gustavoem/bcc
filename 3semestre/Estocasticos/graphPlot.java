import java.awt.Color;
import java.awt.FontMetrics;
import java.awt.Font;

public class graphPlot {

    private Draw janela = new Draw();
    private double width;
    private double height;

    public graphPlot() {}

    public graphPlot(double X, double Y, String name) {
        janela.setCanvasSize(1000, 500);
        janela.setXscale(0, X);
        width = X;
        janela.setYscale(0, Y);
        height = Y;
        Color corFundo = new Color(220, 220, 220);
        janela.clear(corFundo);
        janela.setPenRadius(0.004);
        janela.setPenColor(0, 0, 0);
        janela.text(0.5 * X, Y, name);
    }

    public void addDataValue(double X, double Y) {
        janela.setPenColor(19, 154, 195);
        janela.point(X, Y);
    }

    public void write(double x, double y, double value, String name) { 
        janela.setPenRadius(0.01);
        janela.setPenColor(0, 0, 0);
        String sValue = Double.toString(value);
        int interestedSize;

        for (interestedSize = 0; interestedSize < sValue.length(); interestedSize++) { 
            if (sValue.charAt(interestedSize) == '.') { 
                interestedSize += 2;
                break;
            }
        }

        janela.text(x, y, name + " " + sValue.substring(0, interestedSize));
    }

    public void text(double x, double y, String s) {
        janela.setPenColor(0, 0, 0);
        janela.text(x, y, s);
    }

    public void plotBars(double[] x,double[] a, int firstBar, int intervalBars, String title) {
        int N = a.length;
        janela.setCanvasSize(800, 600);
        janela.setXscale(0, N-1);
        double maxa = max(a);
        janela.setYscale(-maxa / 10, maxa * 1.2);

        Font f1 = new Font("sansserif", Font.PLAIN, 12);
        janela.setFont(f1);
        double var = var(x);
        double mean = mean(x);
        janela.textLeft(0.5 * N, maxa * 0.95, "Media: " + doubleToString(mean));
        janela.textLeft(0.5 * N,  maxa * 0.90, "Variância:" + doubleToString(var));
        janela.setFont();

        for (int i = 0; i < N; i++) {
            janela.filledRectangle(i, a[i]/2, .25, a[i]/2);
            Integer bar = i * intervalBars + firstBar;
            String barInterval = bar.toString() + "~" +  (new Integer(bar + intervalBars)).toString();
            String barValue = "" + (int) a[i];
            janela.text(i, a[i] + N * 0.005 * maxa, barValue, 60.0);
            Font f = new Font("sansserif", Font.ITALIC, 10);
            janela.setFont(f);
            janela.text(i, - N * 0.005 * maxa, barInterval);
            janela.setFont();
        }

        Font f2 = new Font("sansserif", Font.BOLD, 16);
        janela.setFont(f2);
        janela.textLeft(0, maxa * 1.2, title);
        janela.setFont();
    }

    public static String doubleToString(double x) {
        String sValue = Double.toString(x);
        int interestedSize;

        for (interestedSize = 0; interestedSize < sValue.length(); interestedSize++) { 
            if (sValue.charAt(interestedSize) == '.') { 
                interestedSize += 2;
                break;
            }
        }
        return sValue.substring(0, interestedSize);
    }

    public static double mean(double[] a) {
        if (a.length == 0) return Double.NaN;
        double sum = sum(a);
        return sum / a.length;
    }

    public static double sum(double[] a) {
        double sum = 0.0;
        for (int i = 0; i < a.length; i++) {
            sum += a[i];
        }
        return sum;
    }

    public static double var(double[] a) {
        if (a.length == 0) return Double.NaN;
        double avg = mean(a);
        double sum = 0.0;
        for (int i = 0; i < a.length; i++) {
            sum += (a[i] - avg) * (a[i] - avg);
        }
        return sum / (a.length - 1);
    }

    public static double max(double[] a) {
        double max = Double.NEGATIVE_INFINITY;
        for (int i = 0; i < a.length; i++) {
            if (Double.isNaN(a[i])) return Double.NaN;
            if (a[i] > max) max = a[i];
        }
        return max;
    }
}