package main

import (
	"fmt"
	"sort"
	"math"
)

func do(set []int, k int, length int, arr []int) int {
	t := 0
	n := len(set)
	newSet := []int{}
	fmt.Println(set, k)
	for _,x := range arr {
		if x > 0 && t+n >= k {
			y := k-t
			return x*int(math.Pow(10, float64(length))) + set[y-1]
		}
		if x > 0 {
			t += n
		}
		for _, i := range set {
			newSet = append(newSet, x*int(math.Pow(10, float64(length)))+i)
		}
	}
	return do(newSet, k-t, length+1, arr)
}
func numberSequence(arr []int, k int) int {
	if len(arr) == 1 && arr[0] == 0 && k >= 1 {
		return 0
	}
	tarr := []int{}
	all := [10]int{}
	for _,x := range arr {
		if all[x] == 0 {
			all[x]++
			tarr = append(tarr, x)
		}
	}
	sort.Ints(tarr)
	arr = tarr
	
	rs := []int{}
	for _,x := range arr {
		rs = append(rs, x)
	}
	if k <= len(rs) {
		return rs[k-1]
	}
	return do(rs, k-len(arr), 1, arr)
}

func main() {
	fmt.Println(numberSequence([]int{2,5,6}, 5))
}