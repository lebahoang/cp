package main

import (
	"fmt"
	"sort"
)

func get(v int) int {
	return max(0, v)
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

func calculatePrefix(h []int, e int) []int {
	prefix := []int{-1}
	p := 0
	ind := 0
	c := 0
	for i := 1; i <= e; i++ {
		if prefix[p] >= 0 {
			prefix = append(prefix, prefix[p]+c)
		} else if i == h[0] {
			prefix = append(prefix, 0)
		} else {
			prefix = append(prefix, -1)
		}
		p++

		if i == h[ind] {
			ind++
			c++
		}
	}
	return prefix
}

func calculateSuffix(h []int, e int) []int {
	suffix := make([]int, e+1)
	s := e
	ind := len(h) - 1
	c := 0
	for i := e; i >= 1; i-- {
		if i == h[len(h)-1] {
			suffix[s] = 0
		} else if s+1 <= h[len(h)-1] && suffix[s+1] >= 0 {
			suffix[s] = suffix[s+1] + c
		} else {
			suffix[s] = -1
		}
		s--

		if i == h[ind] {
			if ind > 0 {
				ind--
			}
			c++
		}
	}
	return suffix
}

func search(h []int, n int, v int) int {
	l := 0
	r := n - 1
	for {
		if l > r {
			break
		}
		mid := (l + r) / 2
		// fmt.Println(mid)
		if h[mid] <= v {
			if mid+1 == n || h[mid+1] > v {
				return mid
			}
			l = mid + 1
		} else {
			r = mid - 1
		}
	}
	return -1
}

// func solve(h []int, k int) int {
// 	var rs int = 1e9
// 	n := len(h)
// 	sort.Ints(h)
// 	prefix := calculatePrefix(h, h[n-1])
// 	suffix := calculateSuffix(h, h[n-1])
// 	// fmt.Println(prefix, len(prefix))
// 	// fmt.Println(suffix, len(suffix))
// 	dp := [10004][105]int{}
// 	ind := [10004][105]int{}

// 	for i := 1; i <= h[n-1]; i++ {
// 		for j := 1; j <= k; j++ {
// 			if i < j {
// 				continue
// 			}
// 			if j == 1 {
// 				x := dp[i-1][j]
// 				if i-1 < j {
// 					x = 1e9
// 				}
// 				y := get(prefix[i]) + get(suffix[i])
// 				if y < x {
// 					dp[i][j] = y
// 					ind[i][j] = i
// 				} else {
// 					dp[i][j] = dp[i-1][j]
// 					ind[i][j] = ind[i-1][j]
// 				}
// 			} else {
// 				dp[i][j] = dp[i-1][j]
// 				ind[i][j] = ind[i-1][j]
// 				if i-1 < j {
// 					dp[i][j] = 1e9
// 				}
// 				for m := 1; m < i; m++ {
// 					jOne := ind[m][j-1]
// 					mid := search(h, n, (i + jOne)/2)
// 					if mid > -1 {
// 						a := h[mid]
// 						y := dp[m][j-1] - get(suffix[jOne]) +
// 							get(suffix[i]) +
// 							(get(suffix[jOne]) - get(suffix[a]) - (a-jOne)*(n-1-mid))
// 						if mid+1 < n {
// 							b := h[mid+1]
// 							y += (get(prefix[i]) - get(prefix[b]) - (i-b)*(mid+1))
// 						}
// 						// fmt.Println(i,j,m,dp[m][j-1],y)
// 						if y >= 0 && y < dp[i][j] {
// 							dp[i][j] = y
// 							ind[i][j] = i
// 						}
// 					}
// 				}
// 			}
// 			if j == k {
// 				rs = min(rs, dp[i][j])
// 			}
// 			// fmt.Println("aaaa", i, j, ind[i][j], dp[i][j])
// 		}
// 	}
// 	return rs
// }

func solve(h []int, k int) int {
	var rs int = 1e9
	n := len(h)
	sort.Ints(h)
	prefix := calculatePrefix(h, h[n-1])
	suffix := calculateSuffix(h, h[n-1])
	// fmt.Println(prefix, len(prefix))
	// fmt.Println(suffix, len(suffix))
	dp := [104][105]int{}
	ind := [104][105]int{}

	for i := 0; i < n; i++ {
		for j := 1; j <= k; j++ {
			if i+1 < j {
				continue
			}
			if j == 1 {
				dp[i][j] = 1e9
				if i >= j {
					dp[i][j] = dp[i-1][j]
					ind[i][j] = ind[i-1][j]
				}
				if i == 0 {
					dp[i][j] = get(prefix[h[i]]) + get(suffix[h[i]])
					ind[i][j] = h[i]
				}
				for g := 0; g < i; g++ {
					m := h[i]
					y := get(prefix[m]) + get(suffix[m])
					if y < dp[i][j] {
						dp[i][j] = y
						ind[i][j] = m
					}
				}
			} else {
				dp[i][j] = 1e9
				if i >= j {
					dp[i][j] = dp[i-1][j]
					ind[i][j] = ind[i-1][j]
				}
				for g := 0; g < i; g++ {
					m := h[i]
					jOne := ind[g][j-1]
					mid := search(h, n, (m+jOne)/2)
					if mid > -1 {
						a := h[mid]
						y := dp[g][j-1] - get(suffix[jOne]) +
							get(suffix[m]) +
							(get(suffix[jOne]) - get(suffix[a]) - (a-jOne)*(n-1-mid))
						if mid+1 < n {
							b := h[mid+1]
							y += (get(prefix[m]) - get(prefix[b]) - (m-b)*(mid+1))
						}
						// fmt.Println(i,j,m,dp[g][j-1],y)
						if y >= 0 && y < dp[i][j] {
							dp[i][j] = y
							ind[i][j] = m
						}
					}
				}
			}
			if j == k {
				rs = min(rs, dp[i][j])
			}
			// fmt.Println("aaaa", i, j, ind[i][j], dp[i][j])
		}
	}
	return rs
}
func main() {
	// houses := []int{2,3,5,12}
	// k := 2
	// houses := []int{7,4,6,1}
	// k := 1
	houses := []int{6459, 6288, 5120, 83, 4547, 1743, 4240, 8018, 1691, 6439, 2031, 3694, 470, 8133, 7982, 2972, 7370, 560, 3863, 6237, 7589, 4170, 3662, 1185, 9474, 5681, 5400, 6862, 8008, 5957, 440, 1617, 5298, 3158, 6616, 6336, 9071, 1787, 446, 6555, 5116, 9305, 9552, 1414, 8964, 6363, 840, 2973, 9728, 518, 9501, 2014, 2913, 433, 8100, 5971, 8487, 6764, 8101, 7955, 9967, 9425}
	k := 53

	fmt.Println(solve(houses, k))
}
