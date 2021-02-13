package main

import (
	"fmt"
	"sort"
)
func find2(dp [12][50005]int, ind int, k int) (int, int) {
	last := -1
	rem := k
	i := 0
	for {
		if rem <= dp[i][ind] {
			last = i
			break
		}
		rem -= dp[i][ind]
		i++
	}
	return last, rem
}
func find(dp [12][50005]int, total [50005]int, upto [50005]int, k int) (int, int, int) {
	n := 0
	last := -1
	i := 1
	remain := k
	for {
		if i == 50005 {
			break
		}
		if remain <= total[i] {
			n = i
			last, remain = find2(dp, n, remain)
			// fmt.Println("upto", n-2, upto[n-2])
			if n > 1 {
				remain += upto[n-2]
			}
			break
		}
		remain -= total[i]
		i++
	}
	return n-1, last, remain
}
func numberSequence(arr []int, k int) int {
	if len(arr) == 1 && arr[0] == 0 && k > 1 {
		return -1
	}
	sort.Ints(arr)
	dp := [12][50005]int{}
	total := [50005]int{}
	upto := [50005]int{}
	for _, x := range arr {
		dp[x][1]++
		total[1] += dp[x][1]
	}
	for i := 2; i <= 50000; i++ {
		for j := 0; j < len(arr); j++ {
			if i > 1 && arr[j] == 0 {
				continue
			}
			for k := 0; k < len(arr); k++ {
				if i-1 > 1 && arr[k] == 0 {
					continue
				}
				dp[arr[j]][i] += dp[arr[k]][i-1]
			}
			total[i] += dp[arr[j]][i]
		}
		if total[i] > 50000 {
			break
		}
	}
	for i := 1; i <= 50000; i++ {
		if i-1 == 0 {
			upto[i] = total[i]
		} else {
			upto[i] = total[i] + upto[i-1]
		}
		if upto[i] > 50000 {
			// fmt.Println("BREAK", i)
			break
		}
	}
	// fmt.Println(dp)
	// fmt.Println(total)
	// fmt.Println(upto)

	t := []int{}
	n := -1
	last := -1
	for {
		n, last, k = find(dp, total, upto, k)
		// fmt.Println(last, n, k)
		t = append(t, last)
		if n == 0 {
			break
		}
	}
	// fmt.Println(t)
	rs := 0
	for i := 0; i < len(t); i++ {
		rs = rs*10 + t[i]
	}
	return rs
	// return 0;
}
func main() {
	// 13
	fmt.Println(numberSequence([]int{2,5,6}, 50000))
	// fmt.Println(numberSequence([]int{1,2,3,4,5,6,7,8,9}, 50000))
}