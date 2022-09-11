import java.io.PrintWriter;
import java.util.*;
// javac -cp ".;*" -d ./build Solution2.java  && java -Xmx512M -Xss64M -cp ./build Solution2 < x.txt
public class Solution2 {
    private static long mod = 1000_000_007L;
    private static PrintWriter out = new PrintWriter(System.out);
    private static long bf(int[] x, int[] y, int n, int[] qx, int[] qy, int q) {
        long rs = 0;
        for (int i = 0; i < q; i++) {
            for (int j = 0; j < n; j++) {
                long t = (qx[i] - x[j]);
                t = t*t;
                long tt = qy[i] - y[j];
                tt = tt*tt;
                rs = (rs%mod + t%mod + tt%mod)%mod;
            }
        }
        return rs;
    }
    private static long compute(int[] a, int n, int[] b, int q) {
        long rs = 0;
        long x = 0;
        long y = 0;
        for (int i = 0; i < n; i++) {
            x = (x%mod + (a[i]%mod * a[i]%mod)%mod)%mod;
            y = (y%mod + (2*a[i])%mod)%mod;
        }
        for (int i = 0; i < q; i++) {
            long t = (b[i]%mod * b[i]%mod)%mod;
            t = (t%mod * n%mod)%mod;
            rs = (rs%mod + (mod + x%mod - (y%mod * b[i]%mod)%mod)%mod)%mod;
            rs = (rs%mod + t%mod)%mod;
        }
        return rs;
    }
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        try {
            int t = scan.nextInt();
            for (int cs = 1; cs <= t; cs++) {
                int n = scan.nextInt();
                int[] x = new int[n];
                int[] y = new int[n];
                for (int i = 0; i < n; i++) {
                    x[i] = scan.nextInt();
                    y[i] = scan.nextInt();
                }
                int q = scan.nextInt();
                int[] qx = new int[q];
                int[] qy = new int[q];
                for (int i = 0; i < q; i++) {
                    qx[i] = scan.nextInt();
                    qy[i] = scan.nextInt();
                }
                long rs1 = (compute(x, n, qx, q)%mod + compute(y, n, qy, q)%mod)%mod;
                out.println(String.format("Case #%d: %d", cs, rs1));
                // long rs2 = bf(x, y, n, qx, qy, q);
                // if(rs1 != rs2) {
                //     out.println(String.format("Case #%d: OPT %d BF %d", cs, rs1, rs2));
                // }
            }

        } finally {
            scan.close();
            out.close();
        }
        
    }
}