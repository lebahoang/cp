package main

import (
	"fmt"
	"sort"
)
func abs(x int) int {
	fmt.Println(x)
	if x < 0 {
		return -x
	}
	return x
}

func countSwapAndDiff(x int, y int, code string, header string) (int,int) {
	swap := 0
	diff := 0
	j := 0
	for i := x; i <= y; i++ {
		if code[i] != header[j] {
			ok := j+1 < len(header) && code[i] == header[j+1] &&
				  i+1 <= y && code[i+1] == header[j]
				  // abs(int(header[j])-int(header[j+1])) == 1
				  // (abs(int(header[j])-int(header[j+1])) == 1 || abs(int(header[j])-int(header[j+1])) == 25)
			// fmt.Println(i,j,ok)
			if ok {
				swap++
			}
			diff++
		}
		j++
	}
	return swap, diff
}
func isDeleteOne(x int, y int, code string, header string) int {
	c := 0
	i := x
	j := 0
	for {
		if i > y || j >= len(header) {
			break
		}
		if code[i] != header[j] {
			if j+1 >= len(header) || code[i] != header[j+1] {
				c++
			} else {
				i--
			}
		}
		i++
		j++
	}
	return c
}
func calAB(a []bool, b []bool, n int, code string, header string) {
	for i := 0; i < len(code); i++ {
		if i < n-2 {
			a[i] = false
		} else {
			if (i-n+1 >= 0) {
				swap, diff := countSwapAndDiff(i-n+1, i, code, header)
				// if c == 0 || (c < 2 && notSwapStartEnd(i-n+1, i, code, s, e)) {
				// 	a[i] = true
				// }
				if (swap == 0 && diff == 0) || (swap == 1 && diff == 2)|| (swap == 0 && diff == 1) {
					a[i] = true
				}
			}
			if i-n+2 >= 0 {
				c := isDeleteOne(i-n+2, i, code, header)
				if c == 0 {
					b[i] = true
				}
			}
		}
	}
}
func antivirus(header string, keywords []string, code string) []string {
	maxKeyLen := -1
	mKey := map[string]int{}
	ind := 0
	printed := []bool{}
	for _, kw := range keywords {
		if maxKeyLen < len(kw) {
			maxKeyLen = len(kw)
		}
		_, ok := mKey[kw]
		if !ok {
			mKey[kw] = ind
			printed = append(printed, false)
			ind++
		}
	}
	a := make([]bool, len(code))
	b := make([]bool, len(code))
	// it := &item{}
	// it.init(header)
	// calAB(a, b, it, len(header), code, header)
	calAB(a, b, len(header), code, header)
	fmt.Println(header, code)
	fmt.Println(a)
	fmt.Println(b)
	rs := []string{}
	for i := 0; i < len(code); i++ {
		s := []byte{}
		for j := 0; j < maxKeyLen; j++ {
			if i+j >= len(code) {
				break
			}
			s = append(s, code[i+j])
			ss := string(s)
			ind, found := mKey[ss]
			if found && !printed[ind] {
				if (len(header) == 1 ) || (i-1 >= 0 && (a[i-1] || b[i-1])) {
					printed[ind] = true
					rs = append(rs, ss)
				}
			}
		}
	}
	sort.Strings(rs)
	return rs
}

func main() {
	// fmt.Println(antivirus("aze", []string{"a", "b", "c", "d", "e", "f", "g"}, "zaecaezd"))
	// fmt.Println(antivirus("xxx", []string{"bc", "abc"}, "sssssaxxabcyyyyy"))
	// fmt.Println(antivirus("xxx", []string{"acb", "y"}, "axxacbxxay"))
	// fmt.Println(antivirus("aa", []string{"a", "b", "c", "d"}, "abcd"))
	fmt.Println(countSwapAndDiff(0,5,"abakhg","baefgh"))
	// fmt.Println(countSwap(0,2,"xzy","xyz"))
	// fmt.Println(isDeleteOne(0,2,"xyz", "xyzk"))
}