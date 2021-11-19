package main

import (
	"fmt"
	// "math/rand"
    "time"
)

// func simplify(a []int) ([]int, []int, []int) {
// 	rs := []int{}
// 	rsC := []int{}
// 	o2o := make([]int, len(a))
// 	x := a[0]
// 	y := 0
// 	c := 1
// 	for i := 1; i < len(a); i++ {
// 		if x != a[i] {
// 			rs = append(rs, x)
// 			rsC = append(rsC, c)
// 			o2o[y] = len(rs)-1
// 			x = a[i]
// 			y = i
// 			c = 1
// 		} else {
// 			c++
// 		}
// 	}
// 	rs = append(rs, x)
// 	rsC = append(rsC, c)
// 	o2o[y] = len(rs)-1
// 	return rs, rsC, o2o
// }

// func findPrev(b []int) []int {
// 	rs := make([]int, len(b))
// 	m := map[int]int{}
// 	for i := 0; i < len(b); i++ {
// 		v, ok := m[b[i]]
// 		if !ok {
// 			rs[i] = -1
// 		} else {
// 			rs[i] = v
// 		}
// 		m[b[i]] = i
// 	}
// 	return rs
// }

// func solve(a []int, k int) int {
// 	rs := 0
// 	b, c, o2o := simplify(a)
// 	// fmt.Println(b, c, o2o)
// 	prevOf := findPrev(b)
// 	// fmt.Println(prevOf)
// 	n := len(a)
// 	dp := make([]int, n+2)
// 	if k == 1 {
// 		dp[0] = 1
// 	}
// 	for i := 1; i < n; i++ {
// 		if (a[i] == a[i-1]) {
// 			dp[i] += dp[i-1]
// 			rs += dp[i]
// 		} else {
// 			j := o2o[i]
// 			if (prevOf[j] == -1 && j-k+1 >= 0) || (prevOf[j] > -1 && j-prevOf[j] >= k) {
// 				dp[i] += c[j-k+1]
// 				rs += dp[i]
// 			}
// 		}
// 		// fmt.Println(i, dp[i], "iiii")
// 	}
// 	return rs
// }
func copyDict(a map[int]int) map[int]int {
	rs := map[int]int{}
	for k,v := range a {
		rs[k] = v
	}
	return rs
}
func backGo(A []int, K int, m map[int]int, ck int, s int, e int) (int) {
    rs := 1
    for {
        m[A[s]]--
        if (m[A[s]] == 0) {
            ck--
		}
		if ck == K {
			rs++
		} else {
			break
		}
        s++
        if s > e {
            break
        }
    }
    return rs
}
func solve(A []int, K int) int {
	// if K == 1 {
	// 	return len(A)
	// }
    rs := 0
    m := map[int]int{}
    mem := make([]int, len(A))
    ck := 0
	s := 0
    for i := 0; i < len(A); i++ {
		val, ok := m[A[i]]
		if !ok || val == 0 {
			m[A[i]] = 1
			ck++
			if ck >= K {
				if ck > K {
					for {
						if ck == K {
							break
						}
						m[A[s]]--
						if m[A[s]] == 0 {
							ck--
						}
						s++
					}
				}
				tm := copyDict(m)
                mem[i] = backGo(A, K, m, ck, s, i)
				rs += mem[i]
				m = tm
			}
		} else {
			m[A[i]]++
			if ck == K {
				mem[i] = mem[i-1]
				if (A[i] != A[i-1] && K == 2) || (A[i] == A[i-1] && K == 1) {
					mem[i]++
				}
				rs += mem[i]
			}
		}
		fmt.Println(i, mem[i])
    }
    return rs
}
func main() {
	// a := []int{1,1,1,2,2,2,4,4,4,1,2}
	// a := []int{1,1,2,2,3}
	// a := []int{1,2,1,3,4}
	// k := 3
	// a := []int{1,2,1,2,3}
	// k := 2
	// a := []int{2,1,1,1,2}
	// k := 1
	a := []int{2,2,1,2,2,2,1,1}
	k := 2
	// s := rand.NewSource(time.Now().UnixNano())
	// r := rand.New(s)
	// n := 20000
	// a := []int{}
	// for i := 0; i < n; i++ {
	// 	t := r.Intn(n+1)
	// 	if t == 0 {
	// 		t++
	// 	}
	// 	a = append(a, t)
	// }
	// k := 6
	start := time.Now()
	fmt.Println(solve(a, k))
	elapsed := time.Since(start)
	fmt.Println("running time", elapsed.Seconds())
}