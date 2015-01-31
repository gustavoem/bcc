public class Intervalos<Key extends Comparable<Key>> {
    
    private ST<Key, Key> st;

    public Intervalos() {
        st = new ST<Key, Key>();
    }

    public void put(Key[] interval) {
        st.put(interval[0], interval[1]);
    }

    public Key[] get(Key searched) {
        Key base = st.floor(searched);
        Key top = st.get(base);
        Key[] interval = (Key[]) new Comparable[2];
        if (top.compareTo(searched) >= 0) { 
            interval[0] = base;
            interval[1] = top;
        }
        return interval;
    } 

    public static void main(String[] args) {
        Intervalos<String> intervals = new Intervalos<String>();
        while (!StdIn.isEmpty()) {
            String linha = StdIn.readLine();
            String[] entry = new String[2];
            entry = linha.split("-");
            intervals.put(entry);
        }
        String procurado = args[0];
        String[] resposta = intervals.get(procurado);
        StdOut.println("A chave " + procurado + " pertence ao intervalo "
        + resposta[0] + " - " + resposta[1]);
    }
}
