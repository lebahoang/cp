package main

import (
	"fmt"
	"strconv"
	"strings"
)

func insert(a []string, c string, i int) []string {
	return append(a[:i], append([]string{c}, a[i:]...)...)
}
func isNumber(c byte) bool {
	cc := rune(c)
	arr := "0123456789"
	for _, x := range arr {
		if cc == x {
			return true
		}
	}
	return false
}
func doOP(a float64, b float64, op string) float64 {
	if op == "+" {
		return a + b
	} else if op == "-" {
		return a - b
	} else if op == "*" {
		return a * b
	} else {
		return a / b
	}
}
func flattenToNonMulpDiv(s []string) [][]string {
	fmt.Println("flattenToNonMulpDiv", s)
	last := [][]string{}
	cur := []string{}
	for _, x := range s {
		if x != "+" && x != "-" {
			cur = append(cur, x)
		} else {
			fmt.Println("xxxxx", cur)
			last = append(last, cur, []string{x})
			cur = []string{}
		}
	}
	if len(cur) > 0 {
		last = append(last, cur)
	}
	return last
}
func compute(t []string) string {
	n := len(t)
	if n == 2 {
		if t[0] == "-" && string(t[1][0]) == "-" {
			return t[1][1:]
		}
		return t[1]
	}
	var rs float64 = 0
	rs, _ = strconv.ParseFloat(t[0], 64)
	op := ""
	for i := 1; i < n; i++ {
		if i%2 == 1 {
			op = t[i]
		} else {
			b, _ := strconv.ParseFloat(t[i], 64)
			rs = doOP(rs, b, op)
		}
	}
	return fmt.Sprintf("%.10f", rs)
}
func solve1(expression string) float64 {
	arr := strings.Split(expression, " ")
	exp := []string{}
	for _, x := range arr {
		sz := len(x)
		cur := ""
		for j := 0; j < sz; j++ {
			if (j < sz-1 && x[j] == '-') || isNumber(x[j]) || x[j] == '.' {
				cur += string(x[j])
			} else {
				if cur != "" {
					exp = append(exp, cur)
				}
				exp = append(exp, string(x[j]))
				cur = ""
			}
		}
		if cur != "" {
			exp = append(exp, cur)
		}
	}
	fmt.Println("Expression", expression)
	fmt.Println("Parsed Exp", exp)
	n := len(exp)
	s := []string{}
	for i := 0; i < n; i++ {
		if exp[i] != ")" {
			s = append(s, exp[i])
		} else {
			t := []string{}
			c := ""
			for {
				i := len(s) - 1
				c = s[i]
				s = s[:i]
				if c == "(" {
					for i, j := 0, len(t)-1; i < j; i, j = i+1, j-1 {
						t[i], t[j] = t[j], t[i]
					}
					break
				} else {
					t = append(t, c)
				}
			}
			n := len(t)
			if n == 2 {
				if t[0] == "-" && string(t[1][0]) == "-" {
					s = append(s, t[1][1:])
				} else if t[0] != "-" {
					s = append(s, compute([]string{t[0], string(t[1][0]), t[1][1:]}))
				} else {
					s = append(s, t[1])
				}
				continue
			}
			ft := flattenToNonMulpDiv(t)
			ftt := []string{}
			for _, f := range ft {
				if len(f) == 1 && (f[0] == "+" || f[0] == "-") {
					ftt = append(ftt, f[0])
					continue
				}
				out := compute(f)
				fmt.Println("F", f, "TEMP OUT ", out)
				ftt = append(ftt, out)
			}
			out := compute(ftt)
			fmt.Println("T", ftt, "OUT ", out)
			s = append(s, out)
		}
	}
	ss := []string{s[0]}
	i := 1
	for i < len(s) {
		if (s[i-1] == "+" || s[i-1] == "-" || s[i-1] == "*" || s[i-1] == "/") && (s[i] == "-") {
			if s[i+1][0] == '-' {
				ss = append(ss, s[i+1][1:])
			} else {
				ss = append(ss, s[i+1])
			}
			i += 2
		} else {
			ss = append(ss, s[i])
			i++
		}
	}
	s = ss
	var rs float64 = 0
	fmt.Println("SSS", s)
	last := []string{}
	cur := []string{}
	for _, x := range s {
		if x != "+" && x != "-" {
			cur = append(cur, x)
		} else {
			fmt.Println("xxxxx", cur)
			last = append(last, compute(cur), x)
			cur = []string{}
		}
	}
	if len(cur) > 0 {
		last = append(last, compute(cur))
	}
	fmt.Println("LAST", last)
	sz := len(last)
	if sz == 1 {
		rs, _ = strconv.ParseFloat(last[0], 64)
	} else {
		op := ""
		rs, _ = strconv.ParseFloat(last[0], 64)
		for i := 1; i < sz; i++ {
			if i%2 == 1 {
				op = last[i]
			} else {
				fmt.Println("Compute", rs, last[i], op)
				b, _ := strconv.ParseFloat(last[i], 64)
				rs = doOP(rs, b, op)
			}
		}
	}
	return rs
}
func main() {
	// expression := "(1 - 2) + -(-(-(-4)))"
	// expression := "((12.3 + 23.56) * 3234.2) + ((2+3)*34)*(3+4)"
	// expression := "(-4 + -10) * ((12/4) * (2+4))"
	// expression := "2 /2+3 * 4.75- -6"
	// expression := "123.45*(678.90 / (-2.5+ 11.5)-(80 - 19) *33.25) / 20 + 11"
	// expression := "2 / (2 + 3) * 4.33 - -6"
	// expression := "12* 123/-(-5 + 2)"
	// expression := "678.90 / (-2.5+ 11.5)-(80 - 19) *33.25"
	exps := []string{
		"(1 - 2) + -(-(-(-4)))",
		"((12.3 + 23.56) * 3234.2) + ((2+3)*34)*(3+4)",
		"(-4 + -10) * ((12/4) * (2+4))",
		"2 /2+3 * 4.75- -6",
		"123.45*(678.90 / (-2.5+ 11.5)-(80 - 19) *33.25) / 20 + 11",
		"2 / (2 + 3) * 4.33 - -6",
		"12* 123/-(-5 + 2)",
		"678.90 / (-2.5+ 11.5)-(80 - 19) *33.25",
		"678.90 / (-2.5+ 11.5)-(80 -19) *33.25",
	}
	for _, exp := range exps {
		fmt.Println(solve1(exp))
	}
}
