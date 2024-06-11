package main

import (
	"fmt"
)

func findInB2(b []int, m int, val int) int {
	if m == 0 {
		return 0
	}
	if b[0] > val {
		return 0
	}
	if b[m-1] <= val {
		return m
	}
	l := 0
	r := m - 1
	for {
		if l > r {
			break
		}
		mid := (l + r) / 2
		if b[mid] <= val && val < b[mid+1] {
			return mid + 1
		} else if b[mid] > val {
			r = mid - 1
		} else {
			l = mid + 1
		}
	}
	return -100
}
func findInB(b []int, m int, val int) int {
	if m == 0 {
		return 0
	}
	if b[0] >= val {
		return 0
	}
	if b[m-1] < val {
		return m
	}
	l := 0
	r := m - 1
	for {
		if l > r {
			break
		}
		mid := (l + r) / 2
		if b[mid] < val && val <= b[mid+1] {
			return mid + 1
		} else if b[mid] >= val {
			r = mid - 1
		} else {
			l = mid + 1
		}
	}
	return -100
}
func run(a []int, b []int) (float64, bool) {
	n := len(a)
	m := len(b)
	ind := -1
	f := 0
	if (n+m)%2 == 0 {
		ind = (n+m)/2 - 1
		f = 1
	} else {
		ind = (n + m - 1) / 2
	}
	// fmt.Println("XXXXXX", ind, f)
	l := 0
	r := n - 1
	abi := -1
	abj := -1
	for {
		if l > r {
			break
		}
		mid := (l + r) / 2
		i := findInB(b, m, a[mid])
		j := findInB2(b, m, a[mid])
		// fmt.Println(a[mid], "mid", mid, "i", i, "j", j)
		if i > -100 {
			abi = mid
			abj = mid
			if i >= 0 {
				abi += i
			}
			if j >= 0 {
				abj += j
			}
			if abi == ind {
				if f == 1 {
					if (mid+1 < n && i < m && a[mid+1] <= b[i]) || (i >= m) {
						return float64(a[mid]+a[mid+1]) / 2.0, true
					} else {
						return float64(a[mid]+b[i]) / 2.0, true
					}
				} else {
					return float64(a[mid]), true
				}
			} else if abi <= ind && abj >= ind {
				if f == 1 {
					if abj > ind {
						return float64(a[mid]), true
					} else {
						if (mid+1 < n && j < m && a[mid+1] <= b[j]) || (j >= m) {
							return float64(a[mid]+a[mid+1]) / 2.0, true
						} else {
							return float64(a[mid]+b[j]) / 2.0, true
						}
					}
				} else {
					return float64(a[mid]), true
				}
			} else if abi < ind {
				l = mid + 1
			} else {
				r = mid - 1
			}
		}
	}
	return 0.0, false
}
func findMedianSortedArrays(a []int, b []int) float64 {
	rs, found := run(a, b)
	if !found {
		// fmt.Println("---------")
		rs, _ = run(b, a)
	}
	return rs
}

func main() {
	// a := []int{1, 2}
	// b := []int{3, 4}
	// a := []int{1, 3}
	// b := []int{2}
	// a := []int{1, 2}
	// b := []int{2, 3, 4, 5, 6, 7}
	// a := []int{}
	// b := []int{1, 2, 3, 4, 5}
	a := []int{2, 2, 4, 4}
	b := []int{2, 2, 2, 2, 2, 2, 4, 4}
	fmt.Println(findMedianSortedArrays(a, b))
}
