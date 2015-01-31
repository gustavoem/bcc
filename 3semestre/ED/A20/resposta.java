
1)
AAAAAAAAA
    0  1  2  3  4  5  6  7  8
-------------------------------
A |  1  2  3  4  5  6  7  8  9

2) 
ABRACADABRA

    0  1  2  3  4  5  6  7  8  9  10
------------------------------------
A |  1  1  1  4  1  6  1  8  1  1 11
B |  0  2  0  0  2  0  2  0  9  0  0
C |  0  0  0  0  5  0  0  0  0  0  0
D |  0  0  0  0  0  0  7  0  0  0  0
R |  0  0  3  0  0  0  0  0  0 10  0



3)
public int search(String txt) {
    int j, M = pat.length();
    int i, N = txt.length();

    for (i = 0, j = 0; i < N && j < M; i++) {
        /*A*/
        j = dfa[txt.charAt(i)][j];
    }
    if (j == M) return i - M;
    else        return N;
}
Invariantes:
Em /*A*/ vale que txt.substring(i - j, i - 1) é prefixo de pat e é igual a pat.substring(0, j - 1)

4)
public int[][] buildDFA(String pat, char[] alphabet) {
    int[][] newdfa = new int[alphabet.length][pat.length()];
    for (int j = 0; j < pat.length(); j++) {
        for (int i = 0; i < alphabet.length; i++) {
            int shifts = 0;
            String txt;
            txt = pat.substring(0, j) + alphabet[i];
            while (!(pat.substring(0, j + 1 - shifts).equals(txt))) {
                txt = txt.substring(1);
                shifts++;
            }
            /*A*/
            newdfa[i][j] = txt.length();
        }
    }
    return newdfa;
}
Invariantes:
Em /*A*/ vale que txt é maior prefixo de pat.substring(0, j) que é sufixo de pat.substring(0, j) + alphabet[i].
