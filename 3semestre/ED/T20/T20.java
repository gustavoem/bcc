public class T20 {
    public static void main(String[] args) {
        char cnt = 0;
        boolean b, old = false;
        while (!BinaryStdIn.isEmpty()) {
            b = BinaryStdIn.readBoolean();
            if (b != old) {
                BinaryStdOut.write(cnt);
                cnt = 0;
                old = !old;
            }
            else {
                if (cnt == 255) {
                    BinaryStdOut.write(cnt);
                    cnt = 0;
                    BinaryStdOut.write(cnt); // indica carreira de 0 bits
                }
            }
            cnt++;
        }
        BinaryStdOut.write(cnt);
        BinaryStdOut.close();
    }
}