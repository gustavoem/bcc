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
// Data: 2014-06-25
// Disciplina: MAC0323
// Este arquivo faz parte da tarefa T22
/////////////////////////////////////////////////////////////////

public class AqueleFilme {

    private static TrieSET set = new TrieSET();

    public static void readMovies() {
        In file = new In("movies.txt");
        while (!file.isEmpty()) {
            String s = file.readLine();
            String movie = s.substring(0, s.indexOf('(') - 1);
            movie = fixString(movie);
            set.add(movie);
        }
    }

    public static String fixString(String s) {
        char[] cA = s.toCharArray();
        for (int i = 0; i < cA.length; i++)
            cA[i] = fixChar(cA[i]);
        return new String(cA);
    }

    public static char fixChar(char c) {
        if (c == 32)
            return c;
        if (c == 38)
            return 'e';
        if (c > 47 && c < 58)
            return c;
        if (c == 64)
            return 'a';
        if (c > 64 && c < 91) {
            int d = c + 'a' - 'A';
            return (char) d;
        }
        if (c > 96 && c < 123)
            return c;
        if (c == 128)
            return 'c';
        if (c == 129)
            return 'u';
        if (c == 130)
            return 'e';
        if (c > 130 && c < 135)
            return 'a';
        if (c == 135)
            return 'c';
        if (c > 135 && c < 139)
            return 'e';
        if (c > 139 && c < 142)
            return 'i';
        if (c > 142 && c < 144)
            return 'a';
        if (c == 144)
            return 'e';
        if (c > 146 && c < 150)
            return 'o';
        if (c > 149 && c < 152)
            return 'i';
        if (c == 152)
            return 'y';
        if (c == 153)
            return 'o';
        if (c == 154)
            return 'u';
        if (c == 155)
            return 'c';
        if (c == 156)
            return 'l';
        if (c == 157)
            return 'y';
        if (c == 159)
            return 'f';
        if (c == 160)
            return 'a';
        if (c == 161)
            return 'i';
        if (c == 162)
            return 'o';
        if (c == 163)
            return 'u';
        if (c == 161)
            return 'i';
        if (c == 164 || c == 165)
            return 'n';
        if (c == 166)
            return 'a';
        if (c == 167)
            return 'o';
        if (c == 212)
            return 'o';
        if (c == 213)
            return 'f';
        if (c == 224)
            return 'a';
        if (c == 225)
            return 'b';
        if (c == 238)
            return 'e';
        return '?';
    }

    public static void searchMovie(String op, String query) {
        if (op.equals("1")) {
            for (String s : set.keysWithPrefix(query))
                StdOut.println(s);
        }
        if (op.equals("2")) {
            StdOut.println(set.longestPrefixOf(query));
        }
        if (op.equals("3")) {
            for (String s : set.keysThatMatch(query))
                StdOut.println(s);   
        }
    }

    public static void main(String[] args) {
        String op = args[0];
        String query = args[1];
        readMovies();
        searchMovie(op, query);
    }
}

//  Pequeno manual:
//  Opcoes de uso do programa
//  1: os títulos dos filmes que tenham s como prefixo
//  2: o mais longo prefixo de s que seja um título de filme
//  3: os títulos dos filmes que casam com s quando os caracteres
//  '.' em s são interpretados como curingas.
//
//  Resultados
//
//  Filmes que começam com "the":
//  gustavo@Gustavo-Note:~/Dropbox/ED/T22$ java AqueleFilme 1 'the'
//  thelma e louise
//  them?
//  there?s something about mary
//  they
//  they live
//  they shoot horses? don?t they?
//  
//  Filmes que começam com "adventure"
//  gustavo@Gustavo-Note:~/Dropbox/ED/T22$ java AqueleFilme 1 'adventure'
//  adventures in babysitting
//  adventures of baron munchausen? the
//  adventures of bob e doug mckenzie? strange brew? the
//  adventures of buckaroo banzai across the 8th dimension? the
//  adventures of ford fairlane? the
//  adventures of pluto nash? the
//  adventures of priscilla? queen of the desert? the
//  adventures of robin hood? the
//  adventures of rocky e bullwinkle? the
//
//  O mais longe prefixo de 'brazillian' que é o titulo de um filme
//  gustavo@Gustavo-Note:~/Dropbox/ED/T22$ java AqueleFilme 2 'brazillian'
//  brazil
//
//  Filmes com apenas uma letra: 
//  gustavo@Gustavo-Note:~/Dropbox/ED/T22$ java AqueleFilme 3 '.'
//  m
//  o
//  z
//
//  Filmes com apenas duas letras:
//  gustavo@Gustavo-Note:~/Dropbox/ED/T22$ java AqueleFilme 3 '..'
//  10
//  54
//  8?
//  go
//  pi
//  rv
//  x2
