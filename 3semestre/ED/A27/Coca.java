public class Coca {

	public static void compress() {
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
	public static void expand() {
		boolean b = false;
		while (!BinaryStdIn.isEmpty()) {
			char cnt = BinaryStdIn.readChar(); // comprimento de uma carreira
			for (int i = 0; i < cnt; i++)
			BinaryStdOut.write(b);          // sai um único bit
			b = !b;
	   }
	   BinaryStdOut.close();
	}

    public static void main(String[] args) {
        if      (args[0].equals("-")) compress();
        else if (args[0].equals("+")) expand();
        else throw new IllegalArgumentException("Illegal command line argument");
    }
}