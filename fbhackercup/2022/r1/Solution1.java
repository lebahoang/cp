import java.io.PrintWriter;
import java.util.*;
// javac -cp ".;*" -d ./build Solution1.java  && java -Xmx512M -Xss64M -cp ./build Solution1 < x.txt
public class Solution1 {
    private static PrintWriter out = new PrintWriter(System.out, true);
    private static boolean isSame(int[] a, int[] b, int n) {
        boolean f = true;
        for (int i = 0; i < n; i++) {
            if (a[i] != b[i]) {
                f = false;
                break;
            }
        }
        return f;
    }
    private static boolean isConvertable(int[] a, int[] b, int n) {
        int first = a[0];
        HashMap<Integer, Integer> m1 = new HashMap<>();
        HashMap<Integer, Integer> m2 = new HashMap<>();
        for (int i = 0; i < n; i++) {
            m1.put(a[i], i);
            m2.put(b[i], i);
        }
        int dist = -1;
        int x = m1.get(first);
        int y = m2.get(first);
        if (x <= y) dist = y-x;
        else dist = n-1-x + 1 + y;
        // out.println(x + "   " + y + "   " + dist);
        boolean f = true;
        for (int key: m1.keySet()) {
            if (key == first) continue;
            int v1 = m1.get(key);
            int v2 = m2.get(key);
            if ((v1+dist)%n != v2) {
                // out.println(key + "   " + v1 + "  " + v2 + "   " + ((v1+dist)%n));
                f = false;
                break;
            }
        }
        return f;
    }
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        try {
            int t = scan.nextInt();
            for (int cs = 1; cs <= t; cs++) {
                int n = scan.nextInt();
                int k = scan.nextInt();
                int[] a = new int[n];
                for (int i = 0; i < n; i++) a[i] = scan.nextInt();
                int[] b = new int[n];
                for (int i = 0; i < n; i++) b[i] = scan.nextInt();
                // out.println(n + "   " + k);
                // out.println(Arrays.toString((a)));
                // out.println(Arrays.toString((b)));
                if (n < 3) {
                    boolean f = isSame(a, b, n);
                    if (!f && k%2 == 0) out.println(String.format("Case #%d: NO", cs));
                    else if (!f && k%2 == 1) out.println(String.format("Case #%d: YES", cs));
                    else if (f && k%2 == 0) out.println(String.format("Case #%d: YES", cs));
                    else out.println(String.format("Case #%d: NO", cs));
                } else {
                    boolean f1 = isSame(a, b, n);
                    if (f1) {
                        if (k == 1) out.println(String.format("Case #%d: NO", cs));
                        else out.println(String.format("Case #%d: YES", cs));
                    } else {
                        boolean f2 = isConvertable(a, b, n);
                        // out.println(f2 + "    dsad");
                        if (!f2) out.println(String.format("Case #%d: NO", cs));
                        else {
                            if (k == 0) out.println(String.format("Case #%d: NO", cs));
                            else out.println(String.format("Case #%d: YES", cs));
                        }
                    } 
                }
                // out.println("-----------");
            }

        } finally {
            scan.close();
            out.close();
        }
        
    }
}