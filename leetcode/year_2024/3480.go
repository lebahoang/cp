package main

import (
	"fmt"
	"sort"
)

func cmp(a []int, b []int) int {
	if a[1] < b[1] {
		return -1
	} else if a[1] > b[1] {
		return 1
	}
	return a[0] - b[0]
}

func getKey(a []int) string {
	return fmt.Sprintf("[%d,%d]", a[0], a[1])
}

func find(val int, m int, arr [][]int) int {
	if val <= arr[0][0] {
		return 0
	} else if val > arr[m-1][0] {
		return -1
	}
	l := 0
	r := m - 1
	for {
		if l > r {
			break
		}
		mid := (l + r) / 2
		if val > arr[mid][0] && val <= arr[mid+1][0] {
			return mid + 1
		} else if val <= arr[mid][0] {
			r = mid - 1
		} else {
			l = mid + 1
		}
	}
	return -1
}
func solve(n int, a [][]int) int64 {
	d := map[string]int{}
	d2 := map[string]int64{}
	arr := [][]int{}
	for _, v := range a {
		it := []int{min(v[0], v[1]), max(v[0], v[1])}
		k := getKey(it)
		if _, ok := d[k]; !ok {
			d[k] = 1
			d2[k] = 0
			arr = append(arr, it)
		} else {
			d[k]++
		}
	}
	sort.Slice(arr, func(i, j int) bool {
		if arr[i][0] < arr[j][0] {
			return true
		} else if arr[i][0] > arr[j][0] {
			return false
		}
		return arr[i][1] < arr[j][1]
	})
	m := len(arr)
	b := make([][]int, m)
	for i := m - 1; i >= 0; i-- {
		if i == m-1 {
			b[i] = []int{i, m}
		} else {
			t1 := cmp(arr[i], arr[b[i+1][0]])
			t2 := -1
			if b[i+1][1] < m {
				t2 = cmp(arr[i], arr[b[i+1][1]])
			}
			if t1 < 0 && t2 < 0 {
				b[i] = []int{i, b[i+1][0]}
			} else if t1 > 0 && t2 < 0 {
				b[i] = []int{b[i+1][0], i}
			} else {
				b[i] = []int{b[i+1][0], b[i+1][1]}
			}
		}
	}
	// fmt.Println(b)
	t := int64(0)
	for i := 1; i <= n; i++ {
		ind := find(i, m, arr)
		// fmt.Println(i, ind)
		if ind > -1 {
			k := getKey(arr[b[ind][0]])
			if d[k] == 1 {
				if b[ind][1] < m {
					d2[k] += int64(arr[b[ind][1]][1] - 1 - arr[b[ind][0]][1] + 1)
				} else {
					d2[k] += int64(n - arr[b[ind][0]][1] + 1)
				}
			}
			t += int64(arr[b[ind][0]][1] - 1 - i + 1)
		} else {
			t += int64(n - i + 1)
		}
		// fmt.Println("T", t)
	}
	ans := t
	// fmt.Println("ANS", t, d2)
	for i := 0; i < m; i++ {
		k := getKey(arr[i])
		ans = max(ans, t+d2[k])
	}
	// fmt.Println("FINAL ANS:", ans)
	return ans
}

func main() {
	n := 4
	cps := [][]int{
		{2, 3},
		{1, 4},
	}
	// n := 5
	// cps := [][]int{
	// 	{1, 2},
	// 	{2, 5},
	// 	{3, 5},
	// }
	// n := 20
	// cps := [][]int{
	// 	// {1, 7},
	// 	{1, 4},
	// 	{2, 7},
	// 	{8, 10},
	// 	{6, 8},
	// 	{10, 15},
	// 	{13, 15},
	// }
	solve(n, cps)
}
