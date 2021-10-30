import java.lang.*;
import java.io.*;
import java.util.*;

class Point {
  public int x;
  public int y;
  public Point (int x, int y) {
    this.x = x;
    this.y = y;
  }
}

class QueueItem {
  public Point topLeft;
  public Point bottomRight;
  public int[] m;
  public QueueItem(Point topLeft, Point bottomRight, int[] m) {
    this.topLeft = topLeft;
    this.bottomRight = bottomRight;
    this.m = m;
  }
}
class Solution {
  private static boolean isOnlyZero(int[] m) {
    int c = 0;
    for (int i = 1; i < 10; i++) {
      c += m[i];
    }
    if (m[0] > 0 && c == 0) return true;
    return false;
  }
  private static boolean isOnlyZeroAndOther(int[] m) {
    int c = 0;
    int cc = 0;
    for (int i = 1; i < 10; i++) {
      if (m[i] > 0) c += 1;
      cc += m[i];
    }
    if (m[0] > 1 && c == 1 && cc == 1) return true;
    return false;
  }
  private static int[] unmerge(int[] src, int [] dest) {
    int[] m = new int[10];
    for (int i = 0; i < src.length; i++) {
      m[src[i]] -= 1;
    }
    return m;
  }

  private static boolean isPalindrome(int[] m) {
    int sum = 0;
    int c = 0;
    for (int i = 0; i < 10; i++) {
      sum += m[i];
      if (i%2 == 1) {
        c += 1;
        if (c > 1) return false;
      }
    }
    if (m[0] > 1 && sum-m[0] == 0) return false;
    if (m[0] > 1 && sum-m[0] < 2) return false;
    return true;
  }
  private static String[] find(int[][] arr, Point topLeft, Point bottomRight, int[] map) {
    String[] rs = {"", ""};
    int currentMax = 0;
    QueueItem positionMax = new QueueItem(new Point(), new Point(), null);
    Queue<QueueItem> q = new LinkedList<QueueItem>();
    Hashtable<String, Integer> mem = new Hashtable<String, Integer>();
    //String.format("%d-%d-%d-%d", topLeft.x, topLeft.y, bottomRight.x, bottomRight.y)
    q.add(new QueueItem(topLeft, bottomRight, map));
    while (!q.isEmpty()) {
      QueueItem item = q.remove();
      int i = item.topLeft.x;
      int j = item.topLeft.y;
      int ii = item.bottomRight.x;
      int jj = item.bottomRight.y;
      int[] tHashtable = item.m;

      int area = (ii - i + 1)*(jj - j + 1);
      if (isOnlyZero(tHashtable)) {
        if (currentMax < 1) {
          currentMax = 1;
          positionMax.topLeft.x = 0;
          positionMax.topLeft.y = 0;
          positionMax.bottomRight.x = 0;
          positionMax.bottomRight.y = 0;
        }
        continue;
      }

      if (isOnlyZeroAndOther(tHashtable)) {
        if (currentMax < 1) {
          currentMax = 1;
          positionMax.topLeft.x = 0;
          positionMax.topLeft.y = 0;
          positionMax.bottomRight.x = 0;
          positionMax.bottomRight.y = 0;
        }
        continue;
      }

      if (area <= currentMax)
        continue;

      if (isPalindrome(tHashtable)) {
        if (currentMax < area) {
          currentMax = area;
          positionMax.topLeft = item.topLeft;
          positionMax.bottomRight = item.bottomRight;
        }
      }

      if (i+1 <= item.bottomRight.x) {
        int[] x = new int[jj+1-j];
        for (int k = j; k < jj+1-j; k++) {
          x[k-j] = arr[i][k];
        }

        int[] t = unmerge(x, tHashtable);
        String key = String.format("%d-%d-%d-%d", i+1, j, ii, jj);
        if (!mem.containsKey(key)) {
          q.add(new QueueItem(new Point(i+1, j), new Point(ii, jj), t));
          mem.put(key,1);
        }
      }

      if (j+1 <= item.bottomRight.y) {
        int[] x = new int[ii+1-i];
        for (int k = j; k < ii+1-i; k++) {
          x[k-i] = arr[k][j];
        }

        int[] t = unmerge(x, tHashtable);
        String key = String.format("%d-%d-%d-%d", i, j+1, ii, jj);
        if (!mem.containsKey(key)) {
          q.add(new QueueItem(new Point(i, j+1), new Point(ii, jj), t));
          mem.put(key,1);
        }
      }

      if (ii-1 <= bottomRight[1]) {
        int[] x = new int[ii+1-i];
        for (int k = j; k < ii+1-i; k++) {
          x[k-i] = arr[k][j];
        }

        int[] t = unmerge(x, tHashtable);
        String key = String.format("%d-%d-%d-%d", i, j+1, ii, jj);
        if (!mem.containsKey(key)) {
          q.add(new QueueItem(new Point(i, j+1), new Point(ii, jj), t));
          mem.put(key,1);
        }
      }


      if ii-1 >= topLeft[0]:
        x = arr[ii][j:jj+1]
        t = unmerge(x, tHashtable)
        if (i,j,ii-1,jj) not in setO:
          q.put((item[0], (ii-1, jj), t))
          setO.add((i,j,ii-1,jj))

      if jj-1 >= topLeft[1]:
        x = []
        for k in xrange(i, ii+1):
          x.append(arr[k][jj])
        t = unmerge(x, tHashtable)
        #print 'dddddd', t, topLeft, (ii, jj-1)
        if (i,j,ii,jj-1) not in setO:
          q.put((item[0], (ii, jj-1), t))
          setO.add((i,j,ii,jj-1))
    }
    return rs;
  }
  public static void main(String[] args) throws Exception {
    
  }
}