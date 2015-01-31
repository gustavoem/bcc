public class acStackRA<Item> {

   private Item[] a;
   private int N;
   private int acessos;

   public acStackRA() {
      a = (Item[]) new Object[2];
      N = 0;
      acessos = 0;
   }
   public boolean isEmpty() {
      return N == 0;
   }
   
   public void push(Item item) { 
      if (N == a.length)
         resize(2 * a.length);
      a[N++] = item;
      acessos++;
   }

   public Item pop() {
      Item item = a[--N];
      acessos++;
      if (N > 0 && N == a.length/4)
         resize(a.length/2);
      return item;
   }

   private void resize(int max) {
      Item[] temp;
      temp = (Item[]) new Object[max];
      for (int i = 0; i < N; i++) {
         temp[i] = a[i];
         acessos++;
      }
      a = temp;
   }

   public void clearAcessos() {
      acessos = 0;
   }

   public int getAcessos() {
      return acessos;
   }

   public static void main(String[] args) {
      acStackRA<Integer> pilha = new acStackRA<Integer>();
      Queue<Integer> fila = new Queue<Integer>();
      int maxAccess = 0;
      while(!StdIn.isEmpty()) {
         pilha.clearAcessos();
         pilha.push(StdIn.readInt());
         int acessos = pilha.getAcessos();
         fila.enqueue(acessos);
         if (acessos > maxAccess)
            maxAccess = acessos;
      }
      VisualAccumulator plot = new VisualAccumulator(fila.size() , maxAccess);
      while (!fila.isEmpty())
         plot.addDataValue(fila.dequeue());
   }
}