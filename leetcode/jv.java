import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

// javac -cp ".;*" jv.java  && java -Xmx512M -Xss64M Main
class Main {
    public static void main(String[] args) {
        String x = "fdaf{a,b,c}dsada{x,y,z}";
        char[] y = x.toCharArray();
        StringBuilder cur = new StringBuilder();
        List<List<String>> rs = new ArrayList<List<String>>();
        for (int i = 0; i < y.length; i++) {
            if (y[i] != '{' && y[i] != '}') {
                cur.append(String.valueOf(y[i]));
            } else if (y[i] == '{') {
                if(cur.length() > 0) rs.add(Arrays.asList(cur.toString()));
                cur.setLength(0);
            } else if (y[i] == '}') {
                if (cur.length() > 0) rs.add(Arrays.asList(cur.toString().split(",")));
                cur.setLength(0);
            }
        }
        if(cur.length() > 0) rs.add(Arrays.asList(cur.toString()));
        System.out.println(rs);
        String[] t = rs.get(1).toArray(new String[0]);
        System.out.println(Arrays.toString(t));

        // List<List<Integer>> q = new ArrayList<>();
        // int n = 100;
        // for (int i = 0; i < n; i++) q.add(new ArrayList<>());
        

    }
}