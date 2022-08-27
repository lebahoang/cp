import java.io.PrintWriter;
import java.util.*;
// javac -cp ".;*" -d ./build Solution1.java  && java -Xmx512M -Xss64M -cp ./build Solution1
public class Solution1 {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        PrintWriter out = new PrintWriter(System.out);
        try {
            int t = scan.nextInt();
            for (int cs = 1; cs <= t; cs++) {
                int[] cnt = new int[103];
                int n = scan.nextInt();
                int k = scan.nextInt();
                int a = -1;
                int b = -1;
                if (n%2 == 0) {
                    a = n/2;
                    b = n/2;
                } else {
                    a = (n-1)/2;
                    b = a+1;
                }
                boolean f = true;
                int[] x = new int[n];
                for (int i = 0; i < n; i++) {
                    x[i] = scan.nextInt();
                    cnt[x[i]]++;
                    if (cnt[x[i]] > 2) {
                        f = false;
                    }
                }
                if (a > k || b > k || !f) {
                    out.println(String.format("Case #%d: NO", cs));
                } else {
                    out.println(String.format("Case #%d: YES", cs));
                }
            }
        } finally {
            scan.close();
            out.close();
        }
        
    }
}