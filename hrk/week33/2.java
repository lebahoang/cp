import java.io.*;
import java.lang.*;
import java.util.*;

class Solution {
  private static int solve(String s) {
    int count = 0;
    int len = s.length();
    int i = 0;
    while (i < len) {
      if (s.charAt(i) == '1') {
        int j = i+1;
        int x = 0;
        int f = 0;
        while (j < len) {
          if (s.charAt(j) == '1') {
            f = 1;
            break;
          } else if (s.charAt(j) != '0') {
            break;
          }
          x += 1;
          j += 1;
        }
        if (f == 1 && x > 0) count += 1;
        i = j;
      } else {
        i += 1;
      }
    }
    return count;
  }
  public static void main(String[] args) throws Exception {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    int n = Integer.parseInt(br.readLine());
    for (int i = 0; i < n; i++) {
      int c = solve(br.readLine());
      System.out.println(c);
    }
  }
}