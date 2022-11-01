import java.util.*;
// javac -cp ".;*" -Xlint:unchecked -d ./build Solution2354.java  && java -Xmx512M -Xss64M -cp ./build Solution2402
class X {
    public long s;
    public long e;
    public int roomInd;
    public X(long s, long e, int roomInd) {
        this.s = s;
        this.e = e;
        this.roomInd = roomInd;
    }
}
class Comp1 implements Comparator<X> {
    public int compare(X a, X b) {
        if (a.roomInd < b.roomInd) return -1;
        return 1;
    }
}
class Comp2 implements Comparator<X> {
    public int compare(X a, X b) {
        if (a.e < b.e) return -1;
        else if (a.e > b.e) return 1;
        if (a.roomInd < b.roomInd) return -1;
        return 1;
    }
}
class Solution {
    private PriorityQueue<X> q1;
    private PriorityQueue<X> q2;
    public int mostBooked(int n, int[][] arr) {
        int m = arr.length;
        int[] cnt = new int[n];
        Arrays.sort(arr, (int[] i, int [] j) -> {
            return i[0] - j[0];
        });
        q1 = new PriorityQueue<X>(n+5, new Comp1());
        q2 = new PriorityQueue<X>(n+5, new Comp2());
        for (int i = 0; i < n; i++) {
            if (i >= m) {
                break;
            }
            q1.add(new X(0, 0, i));
        }
        int i = 0;
        while (i < m) {
            int[] it = arr[i];
            while (!q2.isEmpty()) {
                X x = q2.peek();
                // System.out.println(x.e + "  " + it[0]);
                if (x.e > it[0]) {
                    break;
                }
                q2.poll();
                q1.add(x);
            }
            if (q1.isEmpty()) {
                X x = q2.poll();
                // System.out.println("X   " + x.roomInd + "  " + x.s + "   " + x.e);
                q1.add(x);
            }
            assert q1.size() + q2.size() <= n;
            X x = q1.poll();
            long s = Math.max(x.e, (long)it[0]);
            q2.add(new X(s, s+(long)(it[1]-it[0]), x.roomInd));
            cnt[x.roomInd]++;
            i++;
        }
        // System.out.println(Arrays.toString(cnt));
        int maxV = -1;
        int rs = -1;
        for (i = 0; i < n; i++) {
            if (maxV == -1 || maxV < cnt[i]) {
                maxV = cnt[i];
                rs = i;
            }
        }
        return rs;
    }
}
public class Solution2402 {
    public static void main(String[] args) {
        Solution s = new Solution();
        int n = 10;

        int l = 80000;
        int[][] arr = new int[l][2];
        for (int i = 0; i < l; i++) {
            arr[i] = new int[]{i+1, i+1+300000};
        }
        System.out.println(s.mostBooked(n, arr));
    }
}