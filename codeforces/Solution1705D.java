import java.io.PrintWriter;
import java.util.*;

// javac -cp ".;*" -d ./build Solution1705D.java  && java -Xmx512M -Xss64M -cp ./build Solution1705D < x.txt
public class Solution1705D {
    private static PrintWriter out = new PrintWriter(System.out, true);
    private static Scanner scan = new Scanner(System.in);
    private static long solve(char[] s, char[] e, int n) {
        if (s[0] != e[0] || s[n-1] != e[n-1]) {
            return -1;
        }
        List<List<Integer>> a = compress(s);
        List<List<Integer>> b = compress(e);
        // out.println(Arrays.toString(a.toArray()));
        // out.println(Arrays.toString(b.toArray()));
        long ans = 0;
        if (a.size() != b.size()) {
            return -1;
        }
        for (int i = 1; i < a.size(); i++) {
            Integer[] x = a.get(i).toArray(new Integer[0]);
            Integer[] y = b.get(i).toArray(new Integer[0]);
            if (x[0] < y[0]) {
                ans += y[0]-x[0];
            } else if (x[0] > y[0]) {
                ans += x[0]-y[0];
            }
        }
        return ans;
    }
    private static List<List<Integer>> compress(char[] s) {
        List<List<Integer>> rs = new ArrayList<>();
        int n = s.length;
        char cur = '\0';
        Integer a = -1;
        Integer b = -1;
        for (int i = 0; i < n; i++) {
            if (cur == '\0' || cur != s[i]) {
                if (cur != '\0') {
                    List<Integer> x = new ArrayList<>();
                    x.add(a);
                    x.add(b);
                    rs.add(x);
                }
                cur = s[i];
                a = i;
                b = i;
            } else {
                b = i;
            }
        }
        List<Integer> x = new ArrayList<>();
        x.add(a);
        x.add(b);
        rs.add(x);
        return rs;
    }
    public static void main(String[] args) {
        try {
            int t = scan.nextInt();
            for (int cs = 0; cs < t; cs++) {
                int n = scan.nextInt();
                char[] s = scan.next().toCharArray();
                char[] e = scan.next().toCharArray();
                out.println(solve(s, e, n));
            }
            
        } finally {
            scan.close();
            out.close();
        }
        
    }
}