import java.io.PrintWriter;
import java.util.*;

// javac -cp ".;*" -d ./build Solution1728D.java  && java -Xmx512M -Xss64M -cp ./build Solution1728D < x.txt
public class Solution1728D {
    private static PrintWriter out = new PrintWriter(System.out, true);
    private static Scanner scan = new Scanner(System.in);
    private static int go(char[] s, int i, int j, int[][] dp) {
        if (dp[i][j] != 0) {
            return dp[i][j];
        }
        if (i == j-1) {
            dp[i][j] = (s[i] != s[j]) ? 1 : 3;
            // out.println(i + "  " + j + "  " + dp[i][j]);
            return dp[i][j];
        }
        int thisStep1 = 0;
        if (s[i] < s[j]) thisStep1 = 1;
        else if (s[i] > s[j]) thisStep1 = 2;
        else thisStep1 = 3;
        int thisStep2 = 0;
        if (s[i] < s[i+1]) thisStep2 = 1;
        else if (s[i] > s[i+1]) thisStep2 = 2;
        else thisStep2 = 3;
        int[] x1 = {
            Math.min(go(s, i+1, j-1, dp), thisStep1),
            Math.min(go(s, i+2, j, dp), thisStep2),
        };
        int thisStep3 = 0;
        if (s[j] < s[i]) thisStep3 = 1;
        else if (s[j] > s[i]) thisStep3 = 2;
        else thisStep3 = 3;
        int thisStep4 = 0;
        if (s[j] < s[j-1]) thisStep4 = 1;
        else if (s[j] > s[j-1]) thisStep4 = 2;
        else thisStep4 = 3;
        int[] x2 = {
            Math.min(go(s, i+1, j-1, dp), thisStep3),
            Math.min(go(s, i, j-2, dp), thisStep4)
        };
        int rs1 = -1;
        for (int v: x1) {
            rs1 = Math.max(rs1, v); 
        }
        int rs2 = -1;
        for (int v: x2) {
            rs2 = Math.max(rs2, v); 
        }
        dp[i][j] = Math.min(rs1, rs2);
        // out.println(i + "  " + j + "  " + dp[i][j]);
        return dp[i][j];
    }
    private static String solve(char[] s) {
        int n = s.length;
        String a = "Alice";
        String b = "Bob";
        String d = "Draw";
        int [][] dp = new int[n][n];
        int rs = go(s, 0, n-1, dp);
        if (rs == 1) {
            return a;
        } else if (rs == 2) {
            return b;
        } else {
            return d;
        }
    }
    public static void main(String[] args) {
        try {
            int t = scan.nextInt();
            for (int cs = 0; cs < t; cs++) {
                char[] s = scan.next().toCharArray();
               
                out.println(solve(s));
            }
            
        } finally {
            scan.close();
            out.close();
        }
        
    }
}