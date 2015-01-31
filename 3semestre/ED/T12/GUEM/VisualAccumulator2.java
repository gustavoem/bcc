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

public class VisualAccumulator2 {

   private double total;
   private double totalM;
   private int N;
   private Draw janela = new Draw();

   public VisualAccumulator2(int X, double Y, String name,
   String val1, String val2) {
      janela.setCanvasSize(1000, 500);
      janela.setXscale(0, X);
      janela.setYscale(0, Y);
      janela.setPenRadius(0.008);
      janela.text(0.5 * X, Y , name);
      janela.setPenColor(220, 95, 95);
      janela.point(0, Y);
      janela.text(0.2 * X, Y, val1);

      janela.setPenColor(95, 100, 220);
      janela.point(0, 0.95 * Y);
      janela.text(0.2 * X, 0.95 * Y , val2);
   }

   public void addDataValue(double val, double valM) {
      N++;
      total += val;
      totalM += valM;

      janela.setPenColor(220, 95, 95);
      janela.point(N, val);
      janela.setPenColor(95, 100, 220);
      janela.point(N, valM);


      janela.setPenColor(220, 25, 25);
      janela.point(N, mean());
      janela.setPenColor(25, 30, 220);
      janela.point(N, meanM());
   }

   public double mean() { 
      return total / N; 
   }

   public double meanM() {
      return totalM / N;
   }

   public String toString() { 
      return "Media (de " + N + " valores): " 
             + String.format("%7.5f", mean()); 
   }
}