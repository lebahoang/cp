import java.lang.*;
import java.util.concurrent.*;
import java.util.*;
import java.math.*;


class Solution {
  public static double heronMethod(double a, int d) {
    double c = 0;
    double x = 0;
    if (d%2 == 1) {
      x = 2 * Math.pow(10, (d-1)/2);
    } else {
      x = 7 * Math.pow(10, (d-2)/2);
    }

    double t = 0;
    while (true) {
      t = Math.floor((x + Math.ceil(a/x))/2);
      // System.out.println(t);
      c += 1;
      if (t == x) {
        break;
      }
      x = t;
    }
    // System.out.println(a + " " + x + " " + c);
    return c;
  }
  public static double run(double start, double end) {
    // System.out.println(start + " " + end);
    Hashtable<Double, Double> t = new Hashtable<Double, Double>();
    double i = start;
    int d = Integer.toString((int)start).length();
    while (i <= end) {
      double c = heronMethod(i, d);
      if (!t.containsKey(c)) {
        t.put(c, 1.0);
      } else {
        double x = t.get(c);
        t.put(c, x+1);
      }
      i += 1;
    }

    double rs = 0;
    Enumeration<Double> e = t.keys();
    while (e.hasMoreElements()) {
      double c = e.nextElement();
      double times = t.get(c);
      rs += c*times;
    } 
    // System.out.println("Dasdsad " + rs);
    return rs;
  }
  public static void main(String[] args) throws Exception {
    CompletableFuture<Double> ttt = new CompletableFuture<Double>();
    ttt.thenApply((t) -> {return t;});
    // Hashtable<Integer, ArrayList<Integer>> h = new Hashtable<Integer, ArrayList<Integer>>();
    // for (int i = 100; i < 1000; i++) {
    //   int c = heronMethod((double)i, Integer.toString(i).length());
    //   if (h.containsKey(c)) {
    //     h.get(c).add(i);
    //   } else {
    //     ArrayList<Integer> t = new ArrayList<Integer>();
    //     t.add(i);
    //     h.put(c, t);
    //   }
    // }
    // int c = heronMethod(10000000000000.0, 14);
    // int cc = heronMethod(99999999999999.0, 14);
    // int c = heronMethod(111, 3);
    // System.out.println(c + " " + cc);
    // System.out.println(Collections.list(h.keys()));
    // System.out.println(h);

    int numOfThreads = 10;
    double range = 1000000-1;
    double start = 10000000000000.0;
    double end = 99999999999999.0;
    double rs = 0;

    // int numOfThreads = 10;
    // double range = 1000-1;
    // double start = 1000;
    // double end = 10000;
    // double rs = 0;

    ExecutorService executor = Executors.newFixedThreadPool(numOfThreads);
    ArrayList<CompletableFuture<Double>> runs = new ArrayList<CompletableFuture<Double>>();
    // CompletableFuture<Integer>[] runs = (CompletableFuture<Integer>[]) new CompletableFuture[numOfThreads];
    double ii = start;
    while (ii < end) {
      runs.clear();
      for (int i = 0; i < numOfThreads; i++) {
        final double startT = ii;
        final double endT = Math.min(ii + range, end);
        CompletableFuture<Double> r = CompletableFuture.supplyAsync(() -> {
          // System.out.println(Thread.currentThread().getName());
          return run(startT, endT);
        }, executor);
        runs.add(r);
        ii = ii + range + 1;
        if (ii > end) {
          break;
        }
      }
      System.out.println("XXXXXXXXXXXXX");
      CompletableFuture<Void> t = CompletableFuture.allOf(runs.toArray((CompletableFuture<Double>[]) new CompletableFuture<?>[runs.size()]));
      System.out.println("YYYYYYYYYYYYY");
      t.thenApply((v) -> {
        System.out.println("CCCC");
        return 1;
      });
      for (int i = 0; i < runs.size(); i++) {
        double x = runs.get(i).get();
        // System.out.println("I " + i + " " + x);
        rs += x;
      }
      System.out.println("----------------  " + rs);  
    }
    System.out.println("Total is " + rs);
    System.out.println("Avg is " + rs/(end-start+1));
    executor.shutdown();
  }
}