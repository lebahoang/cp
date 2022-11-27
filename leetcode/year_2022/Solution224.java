import java.util.*;
// javac -cp ".;*" -Xlint:unchecked -d ./build Solution224.java  && java -Xmx512M -Xss64M -cp ./build Solution224

enum Type {
    NUMBER,
    OP,
    BRACKET_OPEN,
    BRACKET_CLOSE
}
class I {
    public Type t;
    public StringBuffer s;
    public I (Type t, StringBuffer s) {
        this.t = t;
        this.s = s;
    }
}
class SolutionX {
    private static void pp(Deque<I> s) {
        Iterator<I> it = s.descendingIterator();
        StringBuffer buf = new StringBuffer();
        while (it.hasNext()) {
            I item = it.next();
            buf.append(item.s.toString());
            buf.append(' ');
        }
        System.out.println(buf.toString());
    }
    private static boolean isNumber(Character c) {
        Character[] a = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
        for (Character x: a) {
            if (c.equals(x)) return true;
        }
        return false;
    }
    private static boolean isOP(Character c) {
        Character[] a = {'+', '-'};
        for (Character x: a) {
            if (c.equals(x)) return true;
        }
        return false;
    }
    private static boolean isBracketOpen(Character c) {
        if (c.equals('(')) return true;
        return false;
    }
    private static Type getType(Character c) {
        if (isNumber(c)) return Type.NUMBER;
        else if (isOP(c)) return Type.OP;
        else if (isBracketOpen(c)) return Type.BRACKET_OPEN;
        return Type.BRACKET_CLOSE;
    }
    private static void addNumberToStack(Deque<I> s, Character i, Type t) {
        Type lastType = s.getLast().t;
        if (t.equals(lastType)) {
            s.getLast().s.append(i);
        } else {
            I item = s.removeLast();
            if (item.t.equals(Type.BRACKET_OPEN)) {
                s.addLast(item);
                s.addLast(new I(t, new StringBuffer().append(i)));
            } else if (item.t.equals(Type.OP) && item.s.toString().equals("-")) {
                StringBuffer v = item.s;
                v.append(i);
                s.addLast(new I(item.t, new StringBuffer().append('+')));
                s.addLast(new I(t, v));
            } else {
                s.addLast(item);
                s.addLast(new I(t, new StringBuffer().append(i)));
            }
        }
    }
    private static void resolveOneBracketPair(Deque<I> s) {
        int num = 0;
        while (!s.isEmpty()) {
            I item = s.removeLast();
            if (!item.t.equals(Type.BRACKET_OPEN)) {
                if (item.t.equals(Type.NUMBER)) num += Integer.parseInt(item.s.toString());
            } else {
                StringBuffer v = new StringBuffer();
                if (!s.isEmpty()) {
                    I last = s.getLast();
                    if (last.t.equals(Type.OP) && last.s.toString().equals("-")) {
                        s.removeLast();
                        if (num > 0) v = last.s;
                        else num = -num;
                        s.addLast(new I(Type.OP, new StringBuffer().append('+')));
                    }
                }
                s.addLast(new I(Type.NUMBER, v.append(num)));
                break;
            }
        }
    }
    public static int solve(String str) {
        char[] arr = str.toCharArray();
        Deque<I> s = new ArrayDeque<>();
        for (char i: arr) {
            if (i == ' ') continue;
            Type t = getType(i);
            if (s.isEmpty()) {
                s.addLast(new I(t, new StringBuffer().append(i)));
            } else {
                if (t == Type.NUMBER) {
                    addNumberToStack(s, i, t);
                } else if (t == Type.OP) {
                    s.addLast(new I(t, new StringBuffer().append(i)));
                } else if (t ==Type.BRACKET_OPEN) {
                    s.addLast(new I(t, new StringBuffer().append(i)));
                } else {
                    resolveOneBracketPair(s);
                }
            }
            // pp(s);
        }
        // System.out.println("------");
        // pp(s);
        int num = 0;
        while (!s.isEmpty()) {
            I item = s.removeLast();
            if (item.t.equals(Type.NUMBER)) num += Integer.parseInt(item.s.toString());
        }
        return num;
    }
}
public class Solution224 {
    public static void main(String[] args) {
        // String str = "(((1+(4+5+2)-3)+(6+8)-4-5-6) + 5+65)";
        String str = "1-(     -2)";
        System.out.println(SolutionX.solve(str));
    }
}