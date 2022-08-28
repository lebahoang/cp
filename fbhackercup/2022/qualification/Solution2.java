import java.io.PrintWriter;
import java.util.*;
// javac -cp ".;*" -d ./build Solution2.java  && java -Xmx512M -Xss64M -cp ./build Solution2 < x.txt
public class Solution2 {
    private static PrintWriter out = new PrintWriter(System.out);
    private static boolean isNotHaveTree(char[][] a, int r, int c) {
        int cnt = 0;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (a[i][j] == '^') cnt++;
            }
        }
        if (cnt > 0) return false;
        return true;
    }
    private static boolean checkCoord(char[][] a, int r, int c,
        int i, int j, int[][][] coords, boolean[][] visited) {

        a[i][j] = '^';
        for (int[][] coord: coords) {
            boolean ff = true;
            for (int[] cc: coord) {
                int x = cc[0];
                int y = cc[1];
                if (i+x < 0 || i+x >= r || j+y < 0 || j+y >= c) {
                    ff = false;
                    break;
                } else {
                    // out.println("dsadsa " + (i+x) + " dsad " + (j+y));
                    visited[i+x][j+y] = true;
                    a[i+x][j+y] = '^';
                }
            }
            if (ff) return ff;
        }
        return false;
    }
    private static boolean check(char[][] a, int r, int c) {
        boolean[][] visited = new boolean[r][c];
        int[][][] coords = {
            {{-1, 0}, {-1, -1}, {0, -1}},
            {{-1, 0}, {-1, 1}, {0, 1}},
            {{1, 0}, {1, -1}, {0, -1}},
            {{1, 0}, {1, 1}, {0, 1}},
        };
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (a[i][j] == '.') continue;
                if (a[i][j] == '^' && visited[i][j]) continue;
                if (a[i][j] == '^') {
                    boolean f = checkCoord(a, r, c, i, j, coords, visited);
                    if (!f) return false;
                }
            }
        }
        return true;
    }
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        try {
            String pos = "Possible";
            String impos = "Impossible";
            int t = scan.nextInt();
            for (int cs = 1; cs <= t; cs++) {
                int r, c;
                r = scan.nextInt();
                c = scan.nextInt();
                char[][] a = new char[r][c];
                for (int i = 0; i < r; i++) {
                    String l = scan.next();
                    // out.println(l);
                    a[i] = l.toCharArray();
                }
                if (isNotHaveTree(a, r, c)) {
                    out.println(String.format("Case #%d: %s", cs, pos));
                    for (int ii = 0; ii < r; ii++) {
                        out.println(String.valueOf(a[ii]));
                    }
                } else {
                    boolean f = check(a, r, c);
                    if (!f) {
                        out.println(String.format("Case #%d: %s", cs, impos));
                    } else {
                        out.println(String.format("Case #%d: %s", cs, pos));
                        for (int ii = 0; ii < r; ii++) {
                            out.println(String.valueOf(a[ii]));
                        }
                    }
                }
            }
        } finally {
            scan.close();
            out.close();
        }
        
    }
}