package main

import (
	"fmt"
)

func min(a ...int) int {
	v := -1
	for _, x := range a {
		if x == -1 {
			continue
		}
		if v == -1 || v > x {
			v = x
		}
	}
	return v
}
func minDeletionSize(A []string) int {
	nStrings := len(A)
	n := len(A[0])
	dp := make([]int, n)
	for i := 0; i < n; i++ {
		dp[i] = i
		for j := 0; j < i; j++ {
			f := true
			for k := 0; k < nStrings; k++ {
				if A[k][i] < A[k][j] {
					f = false
					break
				}
			}
			if f {
				dp[i] = min(dp[i], dp[j]+(i-1-j))
			}	
		}
	}
	// fmt.Println(dp)
	rs := -1
	for i := 0; i < n; i++ {
		dp[i] += n-1-i
		rs = min(rs, dp[i])
	}
	// fmt.Println(dp)
	return rs
	
}

func main() {
	// fmt.Println(minDeletionSize([]string{
	// 	"babca",
	// 	"bbazb",
	// }))
	fmt.Println(minDeletionSize([]string{
		"a",
		"d",
		"k",
	}))
	
}