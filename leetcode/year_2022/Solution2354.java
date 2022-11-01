import java.util.*;
// javac -cp ".;*" -Xlint:unchecked -d ./build Solution2354.java  && java -Xmx512M -Xss64M -cp ./build Solution2354
public class Solution2354 {
    private static int count(int x) {
        int rs = 0;
        for (int i = 0; i < 31; i++) {
            if ((x & (1 << i)) != 0) rs++;
        }
        return rs;
    }
    public static int search(Integer[] b, int val) {
        if (val <= b[0]) {
            return -1;
        }
        if (val > b[b.length-1]) {
            return b.length;
        }
        int l = 0;
        int r = b.length-1;
        while (l <= r) {
            int mid = (l+r)/2;
            if (b[mid] < val && b[mid+1] >= val) {
                return mid;
            } else if (b[mid] >= val) {
                r = mid-1;
            } else {
                l = mid+1;
            }
        }
        return -2;
    }
    public static long solve(int[] a, int k) {
        Arrays.sort(a);
        List<Integer> x = new ArrayList<>();
        x.add(a[0]);
        int cur = a[0];
        for (int i = 0; i < a.length; i++) {
            if (a[i] != cur) {
                cur = a[i];
                x.add(cur);
            }
        }
        Integer[] arr = x.toArray(new Integer[0]);
        Integer[] b = new Integer[arr.length];
        for (int i = 0; i < arr.length; i++) {
            b[i] = count(arr[i]);
        }
        // System.out.println(Arrays.toString(arr));
        // System.out.println(Arrays.toString(b));
        Arrays.sort(b);
        long rs = 0;
        for (int i = 0; i < b.length; i++) {
            int left = k-b[i];
            // System.out.println(b[i] + "   " + left);
            int ind = search(b, left);
            if (ind+1 >= 0 && ind+1 < b.length) {
                rs += b.length - (ind+1);
            }
        }
        return rs;
    }
    public static void main(String[] args) {
        // int n = 1000000000;
        // Random r = new Random();
        // for (int i = 0; i < n; i++) {
        //     int a = r.nextInt(1000000001) + 1;
        //     int b = r.nextInt(1000000001) + 1;
        //     int xor = a | b;
        //     int and = a & b;
        //     if (count(a) + count(b) != count(xor) + count(and)) {
        //         System.out.println(a + "   " + b);
        //     }
        // }
        // int n = 1000;
        // Random r = new Random();
        // for (int i = 0; i < n; i++) {
        //     System.out.println(r.nextInt(1000000001) + 1);
        // }
        // int[] a = {1,2,3,1};
        // int k = 3;
        int[] a = {312,4342,2321,432423,4324,423,1212,112,121,1,23,431,45,546,232,545665,4343};
        int k = 6;
        System.out.println(solve(a, k));
    }
}
