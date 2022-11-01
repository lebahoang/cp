import java.util.*;
// javac -cp ".;*" -Xlint:unchecked -d ./build Solution1595.java && java -Xmx512M -Xss64M -cp ./build Solution1595

class Solve {
    public static int solve(int[][] cost, int n, int m) {
        int[][] dp = new int[n+5][(1 << m)+5];
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < (1 << m); j++) {
                dp[i][j] = 1000_000_000;
            }
        }
        int[] minV = new int[n];
        for (int i = 0; i < n; i++) {
            int t = 1000_000_000;
            for (int z = 0; z < m; z++) {
                 if (t > cost[i][z]) {
                     t = cost[i][z];
                 }
            }
            minV[i] = t;
        }
        for (int j = 1; j < (1 << m); j++) {
            int total = 0;
            for (int bit = 0; bit < m; bit++) {
                if ((j & (1 << bit)) != 0) {
                    total += cost[0][bit];
                }
            }
            dp[0][j] = total;
            // System.out.println(String.format("dp[%d][%d] = %d", 0, j, dp[0][j]));
        }
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < (1 << m); j++) {
                for (int z = j; z > 0; z = (j & (z-1))) {
                    int tj = j;
                    int total = 0;
                    for (int bit = 0; bit < m; bit++) {
                        if ((z & (1 << bit)) != 0) {
                            total += cost[i][bit];
                            tj = tj ^ (1 << bit);
                        }
                    }
                    if (tj > 0) dp[i][j] = Math.min(dp[i][j], dp[i-1][tj] + total);
                }
                dp[i][j] = Math.min(dp[i][j], dp[i-1][j] + minV[i]);
                // System.out.println(String.format("dp[%d][%d] = %d", i, j, dp[i][j]));
            }
        }
        return dp[n-1][(1 << m)-1];
    }
}
public class Solution1595 {
    public static void main(String[] args) {
        // int n = 12;
        // int x = 0;
        // int cnt = 0;
        // for (int a = 0; a < n; a++) {
        //     for (int i = 0; i < (1 << n); i++) {
        //         for (int z = i; z > 0; z = (i & (z-1))) {
        //             if((z&i) != z || (z|i) != i) {
        //                 System.out.println("AAAAAA");
        //             }
        //             int total = 0;
        //             for (int bit = 0; bit < n; bit++) {
        //                 cnt++;
        //                 if ((z & (1 << bit)) != 0) {
        //                     total += 100;
        //                 }
        //             }
        //             x = Math.max(x, total);
        //         }
        //     }
        // }
        
        // System.out.println("dsadasd " + x + "   " + cnt);
        int[][] c = {
            {15,96},
            {36,2}
        };
        int n = c.length;
        int m = c[0].length;
        // int[][] c = {
        //     {1,3,5},
        //     {4,1,1},
        //     {1,5,3}
        // };
        // List<List<Integer>> cost = new ArrayList<>();
        // int n = c.length;
        // int m = c[0].length;
        // for (int i = 0; i < n; i++) {
        //     List<Integer> t = new ArrayList<>();
        //     for (int j = 0; j < m; j++) {
        //         t.add(c[i][j]);
        //     }
        //     cost.add(t);
        // }
        System.out.println(Solve.solve(c, n, m));
    }
}
