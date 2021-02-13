import java.lang.*;
import java.io.*;
import java.util.*;
class Node {
  public ArrayList<Integer> neighbors;
  public Node() {
    this.neighbors = new ArrayList<Integer>();
  }
}
class Solution {
  private static void printMultiDimensionArray(int[][] d, int n) {
    String str = "[";
    for (int i = 0; i < n-1; i++) {
      for (int j = i+1; j < n; j++) {
        str += String.format("%d, %d, %d", i, j, d[i][j]) + "|";
      }
    }
    str += "]";
    System.out.println(str);
  }
  private static Node[] getNeighbor(String[] pairs, int k, int n) {
    Node[] nodes = new Node[n+1];
    for (int i = 0; i < n+1; i++) {
      nodes[i] = new Node();
    }
    for (int i = 0; i < k; i++) {
      int x = Integer.parseInt(pairs[i].split(" ")[0]);
      int y = Integer.parseInt(pairs[i].split(" ")[1]);
      nodes[x].neighbors.add(y);
      nodes[y].neighbors.add(x);
    }
    return nodes;
  }
  private static int[] getConnectedPair(Node[] nodes, int n) {
    int[] rs = new int[n+1];
    int[] visited = new int[n+1];
    Stack<Integer> stack = new Stack<Integer>();
    int componentInd = 1;
    for (int ind = 1; ind <= n; ind++) {
      if (visited[ind] == 0) {
        ArrayList<Integer> component = new ArrayList<Integer>();
        stack.push(ind);
        while (!stack.isEmpty()) {
          int it = stack.pop();
          visited[it] = 1;
          component.add(it);
          for (int i = 0; i < nodes[it].neighbors.size(); i++) {
            int x = nodes[it].neighbors.get(i);
            if (visited[x] == 0) {
              stack.push(x);
            }
          }
        }

        // get ans

        for (int m = 0; m < component.size(); m++) {
          // rs.put(String.format("%d", component.get(m)), componentInd);
          rs[component.get(m)] = componentInd;
        }
        componentInd += 1;
      }
    }
    return rs;
  }
  private static Boolean isConnected(int[] replaceTable, int node1, int node2) {
    if (node1 == node2) return true;
    if (replaceTable[node1] == replaceTable[node2]) return true;
    return false;
  }
  private static int findLongestPalindromeSubsequence(int[] string, int[] replaceTable) {
    int n = string.length;
    int[][] d = new int[n+1][n+1];
    for (int i = 0; i < n; i++) {
      d[i][i] = 1;
    }
    for (int j = 1; j < n; j++) {
      for (int i = 0; i < n; i++) {
        if (i+j < n) {
          int a = d[i][i+j-1];
          int b = d[i+1][i+j];
          int c = 0;

          if (isConnected(replaceTable, string[i], string[i+j])) {
            if (i+1 <= i+j-1) {
              c = d[i+1][i+j-1] + 2;
            } else {
              c = 2;
            }
          }
          
          d[i][i+j] = Math.max(a, Math.max(b,c));
        } 
      }
    }
    // printMultiDimensionArray(d, n);
    return d[0][n-1];
  }
  public static void main(String[] args) throws Exception {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    //int c = findLongestPalindromeSubsequence("dasd1331");
    String[] arr = br.readLine().split(" ");
    int n = Integer.parseInt(arr[0]);
    int k = Integer.parseInt(arr[1]);
    int m = Integer.parseInt(arr[2]);
    String[] pairs = new String[k];
    for (int i = 0; i < k; i++) {
      pairs[i] = br.readLine();
    }
    int[] string = new int[m];
    String[] s = br.readLine().split(" ");
    for (int i = 0; i < m; i++) {
      string[i] = Integer.parseInt(s[i]);
    }
    Node[] nodes = getNeighbor(pairs, k, n);
    int[] replaceTable = getConnectedPair(nodes, n);
    // System.out.println(replaceTable);
    int c = findLongestPalindromeSubsequence(string, replaceTable);
    System.out.println(c);
  }
}