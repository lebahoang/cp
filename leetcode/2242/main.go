package main

import (
	"fmt"
	"strconv"
	"strings"
)

type Y struct {
	i   int
	len int
}
type X struct {
	i   int
	len int
	sum int
}

func min(a ...int) int {
	var k int = 1e9
	for _, x := range a {
		if k > x {
			k = x
		}
	}
	return k
}

func max(a ...int) int {
	var k int = -1e9
	for _, x := range a {
		if k < x {
			k = x
		}
	}
	return k
}

func dfs(i int, l int, sum int, scores []int, nei [][]int, visited map[int]bool, mem map[Y]int) int {
	key := Y{i, l}
	y, ok := mem[key]
	if ok && y >= sum {
		fmt.Println("Return now")
		return -1
	}
	if l == 4 {
		return sum
	}
	rs := -1
	mem[key] = sum
	visited[i] = true
	for _, j := range nei[i] {
		if _, ok := visited[j]; !ok {
			rs = max(rs, dfs(j, l+1, sum+scores[j], scores, nei, visited, mem))
		}
	}
	delete(visited, i)
	return rs
}
func maximumScore(scores []int, edges [][]int) int {
	rs := -1
	n := len(scores)
	nei := make([][]int, n)
	for _, e := range edges {
		a := e[0]
		b := e[1]
		nei[a] = append(nei[a], b)
		nei[b] = append(nei[b], a)
	}
	for i := 0; i < n; i++ {
		fmt.Println("I", i)
		visited := map[int]bool{}
		mem := map[Y]int{}
		rs = max(rs, dfs(i, 1, scores[i], scores, nei, visited, mem))
		fmt.Println("rs", rs)
	}
	return rs
}

func insert(a []string, c string, i int) []string {
	return append(a[:i], append([]string{c}, a[i:]...)...)
}
func isNumber(c rune) bool {
	arr := "0123456789"
	for _, x := range arr {
		if c == x {
			return true
		}
	}
	return false
}
func isContainedOPAtLast(x string) bool {
	i := len(x) - 1
	var c rune = rune(x[i])
	if c == '+' || c == '-' || c == '*' || c == '/' {
		return true
	}
	return false
}
func isNegativeNumber(x string) bool {
	if x[0] == '-' {
		for i := 1; i < len(x); i++ {
			c := rune(x[i])
			if i == len(x)-1 && isContainedOPAtLast(x) {
				continue
			}
			if !isNumber(c) && c != '.' {
				return false
			}
		}
		return true
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
func main() {
	// scores := []int{21520, 43161, 61439, 44778, 44211, 31994, 45330, 94461, 74266, 74315, 77873, 92309, 39270, 5232, 47812, 38689, 6576, 86322, 8164, 24481, 59113, 61398, 86394, 14777, 92667, 22112, 95799, 15090, 73017, 19857, 51308, 15315, 84789, 62090, 25226, 88446, 65814, 42580, 5537, 20846, 11460, 95070, 86174, 81676, 33944, 54148, 2526, 5480, 54885, 15681, 78851, 94652, 3421, 86847, 71358, 26721, 4557, 13943, 48945, 50512, 47185, 45428, 22781, 88078, 15285, 80781, 76268, 41162, 92558, 37205, 52955, 106, 71797, 71106, 41209, 57541, 17752, 49684, 20509, 17004, 33575, 48918, 88778, 93751, 42289, 96848, 27874, 27175, 47376, 64926, 39739, 48198, 98270, 27117, 44612, 56961, 76320, 29881, 73222, 49794, 177, 68243, 74381, 49166, 66565, 21376, 94041, 61651, 2121, 5302, 21565, 51907, 39066, 54290, 91222, 53927, 6576, 40150, 60783, 48246, 19441, 99577, 78686, 33938, 20885, 33442, 99506, 46015, 50771, 41760, 43155, 73089, 33971, 15633, 36687, 50365, 62673, 60767, 23081, 18737, 96399, 29480, 35628, 13786, 91115, 45945, 6069, 65179, 80015, 45708, 76533, 29664, 199, 99472, 21941, 7056, 75857, 96447, 76761, 10300, 98380, 33942, 40883, 61466, 89294, 15863, 48734, 99677, 383, 15513, 92212, 52527, 36968, 91285, 35531, 17627, 95664, 37258, 83059, 98117, 46362, 6102, 78499, 93158, 64428, 97226, 45432, 74761, 19545, 77545, 19143, 80026, 69411, 24967, 23536, 81728, 88443, 15352, 49255, 61658, 25841, 23534, 85929, 89961, 63417, 46021, 86154, 53674, 14014, 93679, 58207, 12773, 1470, 88011, 84920, 28378, 75693, 71634, 28010, 30163, 94034, 38734, 96416, 91985, 83281, 35783, 51299, 22011, 93432, 58513, 49578, 21196, 33158, 9880, 44913, 91893, 99924, 84249, 63232, 7572, 79085, 45812, 37878, 51119, 80859, 64082, 82942, 55546, 76076, 3801, 68498, 57372, 3784, 72189, 84136, 43269, 43722, 55787, 88936, 70712, 70809, 16054, 70181, 2520, 17803, 38299, 29318, 77089, 28596, 58618, 95982, 46685, 69794, 25831, 70705, 59720, 68352, 78429, 69805, 36641, 54225, 38190, 93524, 40766, 80687, 58813, 74032, 53032, 39244, 59864, 4920, 60822, 60986, 52962, 59657, 79345, 69190, 88341, 82535, 80556, 5760, 9727, 57598, 48976, 62543, 32106, 1905, 42374, 53000, 3258, 60475, 35272, 11302, 96332, 18463, 41851, 8196, 36929, 283, 14194, 71233, 66070, 96091, 3440, 41769, 13655, 50695, 94953, 12222, 27583, 50505, 66811, 46036, 55137, 10758, 13924, 69694, 80356, 77824, 96106, 7597, 22656, 16102, 80824, 95808, 18188, 88117, 69447, 74722, 5230, 58899, 83899, 8281, 70006, 97920, 90340, 31290, 61388, 81229, 4803, 96337, 60474, 7662, 46746, 58932, 62434, 4771, 25287, 77279, 32158, 73171, 27682, 65117, 95303, 7814, 62562, 84302, 43945, 37030, 17717, 14597, 54826, 39569, 34793, 84739, 17893, 21763, 1931, 41347, 65188, 88338, 17665, 46661, 51302, 85917, 24303, 87493, 48248, 10382, 12478, 5853, 76416, 58345, 15340, 25831, 60505, 22333, 79096, 36796, 27308, 50417, 50809, 64685, 40327, 30103, 23058, 9120, 30968, 75560, 5281, 18855, 27079, 86504, 73580, 24146, 84814, 11074, 97291, 25590, 64940, 47734, 48984, 23826, 13357, 23746, 10722, 84585, 2932, 58581, 84877, 38710, 90466, 35801, 74954, 14264, 11340, 11562, 68816, 3236, 83441, 75369, 94116, 10670, 30318, 30959, 45480, 63548, 74253, 20841, 26111, 86765, 82446, 93467, 58354, 17590, 48910, 40842, 59377, 69238, 91152, 60784, 97237, 23764, 72425, 69042, 5944, 41173, 1408, 36497, 27404, 40961, 50882, 7947, 79004, 50330, 30526, 1997, 10655, 43306, 86160, 89682, 62444, 35348, 43395, 69883, 6946, 9352, 59061, 92015, 65839, 97402, 76374, 63886, 51350, 2917, 3359, 12750, 69219, 64775, 47889, 81600, 79991, 11322, 94712, 51849, 83461, 47571, 26184, 41113, 80580, 26353, 97356, 56797, 79572, 90436, 79072, 65772, 85227, 33739, 79745, 6181, 40210, 73643, 48489, 98350, 16664, 24254, 91713, 18244, 43563, 7560, 44234, 41653, 65050, 90830, 23600, 70246, 69702, 29001, 87226, 59066, 5925, 94045, 57834, 67868, 21541, 20176, 61498, 69436, 89875, 95313, 72312, 31958, 91040, 83589, 58078, 85263, 74131, 51512, 58052, 94074, 60026, 47161, 25542, 84063, 97124, 5269, 96142, 99270, 59910, 75895, 22245, 68217, 59002, 29095, 40831, 35464, 67440, 68839, 52260, 17980}
	// fmt.Println(len(scores))
	// edges := [][]int{
	// 	{0, 1},
	// 	{1, 2},
	// 	{2, 3},
	// 	{0, 2},
	// 	{1, 3},
	// 	{2, 4},
	// 	{0, 3},
	// }
	// scores := []int{9, 20, 6, 4, 11, 12}
	// edges := [][]int{
	// 	{0, 3},
	// 	{5, 3},
	// 	{2, 4},
	// 	{1, 3},
	// }
	// fmt.Println(maximumScore(scores, edges))

	// expression := "(1 - 2) + -(-(-(-4)))"
	// expression := "((12.3 + 23.56) * 3234.2) + ((2+3)*34)*(3+4)"
	// expression := "(-4 + -10) * ((12/4) * (2+4))"
	// expression := "2 /2+3 * 4.75- -6"
	// expression := "123.45*(678.90 / (-2.5+ 11.5)-(80 - 19) *33.25) / 20 + 11"
	expression := "2 / (2 + 3) * 4.33 - -6"
	// expression := "12* 123/-(-5 + 2)"
	// expression := "678.90 / (-2.5+ 11.5)-(80 - 19) *33.25"
	arr := strings.Split(expression, " ")
	exp := []string{}
	for _, x := range arr {
		sz := len(x)
		cur := ""
		for j := 0; j < sz; j++ {
			if (j < sz-1 && x[j] == '-') || isNumber(rune(x[j])) || x[j] == '.' {
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
	fmt.Println("RS", rs)
}
