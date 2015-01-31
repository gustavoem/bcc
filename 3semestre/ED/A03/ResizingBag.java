public class ResizingBag<Item> {

   private Item[] array = (Item[]) new Object[2];
   private int N;

   public ResizingBag() { }

   public void add(Item item) {
      if (N == array.length) {
         resize(2*N);
      }
      array[N] = item;
      N++;
   }

   public boolean isEmpty() {
      return N == 0;
   }  

   private void resize(int n){
      Item[] newarray = (Item[]) new Object[2];
      for (int i = 0; i < array.length; i++)
         newarray[i] = array[i];
      array = newarray;
   }
}