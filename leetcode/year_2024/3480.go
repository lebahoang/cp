package main

import (
	"fmt"
	"sort"
)

func key(a int, b int) string {
	return fmt.Sprintf("%d;%d", a, b)
}
func find(cps [][]int, n int, val int) int {
	if cps[0][1] >= val {
		return 0
	}
	if cps[n-1][1] <= val {
		return n - 1
	}
	l := 0
	r := n - 1
	for {
		mid := (l + r) / 2
		if cps[mid][1] <= val && cps[mid+1][1] > val {
			return mid
		} else if cps[mid][1] > val {
			r = mid - 1
		} else {
			l = mid + 1
		}
	}
}
func solve(n int, cps [][]int) int64 {
	sort.Slice(cps, func(i, j int) bool {
		if cps[i][1] < cps[j][1] {
			return true
		} else if cps[i][1] > cps[j][1] {
			return false
		}
		return cps[i][0] < cps[j][0]
	})

	pc := map[string]int{}
	p := make([][]int, n+3)
	pp := make([][][]int, n+3)
	mem := make([]int, n+3)
	for i := 0; i <= n; i++ {
		p[i] = []int{}
		mem[i] = -1
	}
	length := len(cps)
	for i, x := range cps {
		p[x[0]] = append(p[x[0]], x[1])
		pp[x[1]] = append(pp[x[1]], []int{x[0], i})
		k := key(x[0], x[1])
		if _, ok := pc[k]; !ok {
			pc[k] = 1
		} else {
			pc[k]++
		}
	}
	indexs := make([]int, length)
	cur := -1
	for i := 1; i <= n; i++ {
		if len(pp[i]) > 0 {
			sort.Slice(pp[i], func(x, y int) bool {
				return pp[i][x][0] < pp[i][y][0]
			})
			for j, it := range pp[i] {
				if j-1 >= 0 {
					indexs[it[1]] = pp[i][j-1][1]
				} else {
					if cur > -1 {
						indexs[it[1]] = pp[cur][len(pp[cur])-1][1]
					} else {
						indexs[it[1]] = 1
					}
				}
			}
			cur = i
		}
	}
	var rs int64 = 0
	// a := map[int]int{}
	b := map[int]int{}
	start := 1
	end := 1
	for {
		if start > n {
			break
		}
		_, ok := b[end]
		if end <= n && !ok {
			if len(p[end]) > 0 {
				// if _, ok = a[end]; !ok {
				// 	a[end] = 1
				// } else {
				// 	a[end]++
				// }
				for _, v := range p[end] {
					if _, ok = b[v]; !ok {
						b[v] = 1
					} else {
						b[v]++
					}
				}
			}
			end++
		} else {
			if mem[start] == -1 {
				mem[start] = end - 1
				rs += int64(end - start)
			}
			if len(p[start]) > 0 {
				// a[start]--
				// if a[start] == 0 {
				// 	delete(a, start)
				// }
				for _, v := range p[start] {
					b[v]--
					if b[v] == 0 {
						delete(b, v)
					}
				}
			}
			start++
			if start > end {
				end = start
			}
		}
	}
	fmt.Println(mem[1 : n+1])
	fmt.Println(indexs)
	var ans int64 = rs
	for i, x := range cps {
		k := key(x[0], x[1])
		if pc[k] == 1 {
			ind := indexs[i]
			if cps[ind][0]+1 <= x[0] {
				ans = max(ans, rs+int64((x[0]-cps[ind][0])*(mem[x[0]+1]-x[1]+1)))
				fmt.Println(x, ind, rs, int64((x[0]-cps[ind][0])*(mem[x[0]+1]-x[1]+1)))
			} else {
				ans = max(ans, rs+int64((cps[ind][0]+1)*(mem[cps[ind][0]+1]-cps[ind][0])))
				fmt.Println(x, ind, rs, int64((cps[ind][0]+1)*(mem[cps[ind][0]+1]-cps[ind][0])))
			}
		}
	}
	fmt.Println(ans)
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
