package main

import "fmt"

func find(i int, j int, k int, prefix []int, C int) int {
	jj := j
	s := prefix[j]
	if i-1 >= 0 {
		s -= prefix[i-1]
	}
	if s < k {
		return C
	}
	if s >= k && i == j {
		return 1
	}
	rs := C
	for {
		if i > jj {
			return rs
		}
		mid := (jj + i) / 2
		total := prefix[j]
		if mid-1 >= 0 {
			total -= prefix[mid-1]
		}
		if total >= k && prefix[j]-prefix[mid] < k {
			return j - mid + 1
		} else if total < k {
			jj = mid - 1
		} else {
			i = mid + 1
		}
	}
}
func solve(arr []int, k int) int {
	C := 10000000
	rs := C
	n := len(arr)
	prefix := make([]int, n)
	maxs := make([]int, n)
	cnt := 0
	for i, val := range arr {
		if i == 0 {
			prefix[i] = val
		} else {
			prefix[i] = prefix[i-1] + val
		}
		if i == 0 || arr[i-1] >= 0 {
			cnt++
			maxs[i] = cnt
		} else {
			cnt = 1
			maxs[i] = cnt
		}
		fmt.Println(i-maxs[i]+1, i)
		x := find(i-maxs[i]+1, i, k, prefix, C)
		fmt.Println(i-maxs[i]+1, i, x)
		rs = min(rs, x)
	}
	fmt.Println(maxs)
	if rs == C {
		return -1
	}
	return rs
}
func main() {
	// arr := []int{-34, 37, 51, 3, -12, -50, 51, 100, -47, 99, 34, 14, -13, 89, 31, -14, -44, 23, -38, 6}
	// k := 151
	arr := []int{84, -37, 32, 40, 95}
	k := 167
	fmt.Println(solve(arr, k))
}
