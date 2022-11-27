import java.io.PrintWriter;
import java.util.*;

// javac -cp ".;*" -d ./build Solution1704D.java  && java -Xmx512M -Xss64M -cp ./build Solution1704D < x.txt
public class Solution1704D {
    private static PrintWriter out = new PrintWriter(System.out, true);
    private static Scanner scan = new Scanner(System.in);
    public static void main(String[] args) {
        int t = scan.nextInt();
        for (int cs = 0; cs < t; cs++) {
            int ans1 = 0;
            long ans2 = 0;
            int n = scan.nextInt();
            int m = scan.nextInt();
            List<List<Long>> l = new ArrayList<>();
            for (int i = 0; i < n; i++) {
                List<Long> k = new ArrayList<>();
                for (int j = 0; j < m; j++) {
                    k.add(scan.nextLong());
                }
                l.add(k);
            }
            HashMap<Long, List<Integer>> map = new HashMap<>();
            for (int i = 0; i < n; i++) {
                long sum = 0;
                for (int j = 0; j < m; j++) {
                    sum += l.get(i).get(j)*j;
                }
                if (map.containsKey(sum)) {
                    List<Integer> temp = map.get(sum);
                    temp.add(i);
                    map.put(sum, temp);
                } else {
                    List<Integer> temp = new ArrayList<>();
                    temp.add(i);
                    map.put(sum, temp);
                }
            }
            long[] arr = new long[2];
            for (Map.Entry<Long, List<Integer>> e: map.entrySet()) {
                // out.println(e.getKey() + "  " + e.getValue());
                List<Integer> a = e.getValue();
                if (a.size() == 1) {
                    ans1 = a.get(0)+1;
                    arr[1] = e.getKey();
                } else {
                    arr[0] = e.getKey();
                }
            }
            ans2 = arr[1] - arr[0];
            out.println(ans1 + " " + ans2);
        }
    }
}
