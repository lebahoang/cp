package main

import "fmt"

type Node struct {
	val       int64
	nChildren int64
	left      *Node
	right     *Node
}

func dfs1(i *Node, val int64, j int, items []*Node) {
	if val < i.val {
		if i.left == nil {
			i.left = items[j]
		} else {
			dfs1(i.left, val, j, items)
		}
	} else if val > i.val {
		if i.right == nil {
			i.right = items[j]
		} else {
			dfs1(i.right, val, j, items)
		}
	}
}
func buildTree(a []int) *Node {
	items := []*Node{}
	for i := 0; i < len(a); i++ {
		items = append(items, &Node{
			val:       int64(a[i]),
			nChildren: 0,
			left:      nil,
			right:     nil,
		})
	}
	for i := 1; i < len(a); i++ {
		dfs1(items[0], items[i].val, i, items)
	}
	return items[0]
}

func merge(a int64, b int64, mod int64) [1005][1005]int64 {
	dp := [1005][1005]int64{}
	prefix := [1005][1005]int64{}
	for j := int64(0); j < b; j++ {
		for i := int64(0); i < a+1; i++ {
			if j == 0 {
				dp[i][j] = 1
			} else {
				// dp[i][j] = (dp[i][j]%mod + mem[j-1]%mod) % mod
				// for k := int64(0); k <= i; k++ {
				// 	dp[i][j] = (dp[i][j]%mod + dp[k][j-1]%mod) % mod
				// }
				dp[i][j] = (dp[i][j]%mod + prefix[i][j-1]%mod) % mod
			}
			if i == 0 {
				prefix[i][j] = dp[i][j]
			} else {
				prefix[i][j] = (prefix[i-1][j]%mod + dp[i][j]%mod) % mod
			}
		}
	}
	return prefix
}
func get(a int64, b int64, mem *[1005][1005]int64) int64 {
	return (*mem)[a][b-1]
}
func dfs2(i *Node, mem *[1005][1005]int64, mod int64) int64 {
	var a int64 = 0
	var pera int64 = 0
	if i.left != nil {
		pera = dfs2(i.left, mem, mod)
		i.nChildren = i.left.nChildren + 1
		a = i.left.nChildren + 1
	} else {
		pera = 1
	}
	var b int64 = 0
	var perb int64 = 0
	if i.right != nil {
		perb = dfs2(i.right, mem, mod)
		i.nChildren += i.right.nChildren + 1
		b = i.right.nChildren + 1
	} else {
		perb = 1
	}
	var cnt int64 = 0
	if a == 0 || b == 0 {
		cnt = 1
	} else {
		cnt = get(a, b, mem)
	}
	// fmt.Println(i.val, a, b)
	return (pera % mod * perb % mod * cnt % mod) % mod

}
func solve(a []int) int {
	var mod int64 = 1e9 + 7
	mem := merge(1000, 1000, mod)
	root := buildTree(a)
	rs := dfs2(root, &mem, mod)
	fmt.Println(rs - 1)
	return int(rs - 1)
}
func main() {
	// a := []int{2, 1, 3}
	// a := []int{3, 4, 5, 1, 2}
	// a := []int{3, 4, 5, 1, 2, 10, 6, 7, 8, 9}
	a := []int{62, 82, 78, 35, 58, 81, 63, 21, 47, 54, 74, 38, 32, 60, 52, 50, 96, 29, 90, 30, 100, 8, 39, 23, 34, 80, 70, 53, 69, 18, 95, 72, 89, 10, 43, 13, 42, 97, 77, 20, 28, 75, 55, 66, 94, 2, 49, 12, 9, 91, 86, 65, 98, 15, 57, 46, 41, 71, 6, 19, 92, 17, 93, 56, 61, 4, 83, 37, 33, 31, 7, 5, 64, 59, 99, 85, 11, 16, 22, 79, 14, 51, 67, 48, 24, 84, 73, 87, 25, 27, 44, 36, 68, 45, 76, 1, 88, 3, 26, 40}
	solve(a)
}
