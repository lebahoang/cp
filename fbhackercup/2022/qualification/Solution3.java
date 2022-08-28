import java.io.PrintWriter;
import java.util.*;
// javac -cp ".;*" -d ./build Solution3.java  && java -Xmx512M -Xss64M -cp ./build Solution3 < x.txt
public class Solution3 {
    private static PrintWriter out = new PrintWriter(System.out);
    private static List<Object> isNotHaveTree(char[][] a, int r, int c) {
        boolean[][] rs = new boolean[r][c];
        int cnt = 0;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (a[i][j] == '^') {
                    rs[i][j] = true;
                    cnt++;
                }
            }
        }
        return Arrays.asList(cnt, rs);
    }
    private static void fillMap(char[][] a, int r, int c) {
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (a[i][j] != '#') {
                    a[i][j] = '^';
                }
            }
        }
    }
    private static boolean isLessThan2(char[][] a, int i, int j, int r, int c, int[][] coords) {
        int cnt = 0;
        for (int[] cc: coords) {
            int x = cc[0];
            int y = cc[1];
            if (i+x >= 0 && i+x < r && j+y >= 0 && j+y < c && a[i+x][j+y] == '^') {
                cnt++;
            }
        }
        
        if (cnt < 2) return true;
        return false;
    }
    private static boolean bfs(int i, int j, char[][] a, int r, int c,
        int[][] coords, boolean[][] visited, boolean[][] ordinary) {

        Deque<int[]> q = new ArrayDeque<>();
        q.add(new int[]{i, j});
        while (!q.isEmpty()) {
            int[] it = q.pollFirst();
            int ix = it[0];
            int iy = it[1];
            visited[ix][iy] = true;
            boolean b = isLessThan2(a, ix, iy, r, c, coords);
            // out.println(String.format("I %d J %d IS_LESS_THAN_2 %b ordinary %b", ix, iy, b, ordinary[ix][iy]));
            if (b && ordinary[ix][iy]) {
                return false;
            }
            if (b && !ordinary[ix][iy]) {
                a[ix][iy] = '.';
            }
            for (int[] cc: coords) {
                int x = cc[0];
                int y = cc[1];
                if (ix+x >= 0 && ix+x < r
                    && iy+y >= 0 && iy+y < c && !visited[ix+x][iy+y]
                    && a[ix+x][iy+y] == '^' && isLessThan2(a, ix+x, iy+y, r, c, coords)) {
                    q.add(new int[]{ix+x, iy+y});
                }
            }
        }
        return true;
    }
    private static boolean check(char[][] a, int r, int c, boolean[][] ordinary) {
        int[][] coords = {
            {-1, 0}, {1, 0}, {0, -1}, {0, 1}
        };
        boolean[][] visited = new boolean[r][c];
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (visited[i][j] || a[i][j] != '^') {
                    continue;
                }
                if (a[i][j] == '^' && !isLessThan2(a, i ,j, r, c, coords)) {
                    // visited[i][j] = true;
                    continue;
                }
                if (!bfs(i, j, a, r, c, coords, visited, ordinary)) {
                    return false;
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
                List<Object> temp = isNotHaveTree(a, r, c);
                int cnt = (int)temp.get(0);
                boolean[][] ordinary = (boolean[][])temp.get(1);
                if (cnt == 0) {
                    out.println(String.format("Case #%d: %s", cs, pos));
                    for (int ii = 0; ii < r; ii++) {
                        out.println(String.valueOf(a[ii]));
                    }
                } else {
                    fillMap(a, r, c);
                    // for (int i = 0; i < r; i++) {
                    //     out.println(String.valueOf(a[i]));
                    // }
                    if (check(a, r, c, ordinary)) {
                        out.println(String.format("Case #%d: %s", cs, pos));
                        for (int ii = 0; ii < r; ii++) {
                            out.println(String.valueOf(a[ii]));
                        }
                    } else {
                        out.println(String.format("Case #%d: %s", cs, impos));
                    }
                }
            }
        } finally {
            scan.close();
            out.close();
        }
        
    }
}