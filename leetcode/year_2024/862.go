package main

import "fmt"

func solve(arr []int, k int) int {
	C := 10000000
	rs := C
	n := len(arr)
	s := 0
	cnt := 0
	a := 0
	last_negative := -1
	for i := 0; i < n; i++ {
		s += arr[i]
		cnt++
		if arr[i] <= 0 {
			last_negative = i
		}
		if s >= k {
			rs = min(rs, cnt)
			for {
				if a <= last_negative || (a > last_negative && s >= k) {
					s -= arr[a]
					a++
					cnt--
					if s >= k {
						rs = min(rs, cnt)
					}
				} else {
					last_negative = -1
					break
				}
			}
		}
	}
	if rs == C {
		return -1
	}
	return rs
}
func main() {
	arr := []int{2, -1, 2}
	k := 3
	fmt.Println(solve(arr, k))
}
