package main

import (
	"fmt"
)

func max(a ...int) int {
	v := 0
	for _,x := range a {
		if x > v {
			v = x
		}
	}
	return v
}

func do(g [][]int, dp *[55][55][55][55]int, i, j, k, p int) int {
	if dp[i][j][k][p] > -1e9 {
		// fmt.Println(i,j,k,p,dp[i][j][k][p])
		return dp[i][j][k][p]
	}
	if g[i][j] == -1 || g[k][p] == -1 {
		dp[i][j][k][p] = -1
		return dp[i][j][k][p]
	}
	isPass := false
	if i-1 >= 0 && k-1 >= 0 {
		x := do(g, dp, i-1, j, k-1, p)
		if x > -1 {
			isPass = true
			dp[i][j][k][p] = max(dp[i][j][k][p], x)
		}
	}
	if i-1 >= 0 && p-1 >= 0 {
		x := do(g, dp, i-1, j, k, p-1)
		if x > -1 {
			isPass = true
			dp[i][j][k][p] = max(dp[i][j][k][p], x)
		}
	}
	if j-1 >= 0 && k-1 >= 0 {
		x := do(g, dp, i, j-1, k-1, p)
		if x > -1 {
			isPass = true
			dp[i][j][k][p] = max(dp[i][j][k][p], x)
		}
	}
	if j-1 >= 0 && p-1 >= 0 {
		x := do(g, dp, i, j-1, k, p-1)
		if x > -1 {
			isPass = true
			dp[i][j][k][p] = max(dp[i][j][k][p], x)
		}
	}
	if !isPass {
		dp[i][j][k][p] = -1
	} else {
		if i == k && j == p {
			dp[i][j][k][p] += g[i][j]
		} else {
			dp[i][j][k][p] += g[i][j]
			dp[i][j][k][p] += g[k][p]
		}
	}
	// fmt.Println(i,j,k,p,dp[i][j][k][p])
	return dp[i][j][k][p]
}
func cherryPickup(grid [][]int) int {
	n := len(grid)
	dp := [55][55][55][55]int{}
	for i := 0; i < n; i++ {
		for j := 0; j < n; j++ {
			for k := 0; k < n; k++ {
				for p := 0; p < n; p++ {
					dp[i][j][k][p] = -1e9
				}
			}
		}
	}
	dp[0][0][0][0] = grid[0][0]
	rs := do(grid, &dp, n-1, n-1, n-1, n-1)
	if rs == -1 {
		return 0
	}
	return rs
}

func main() {
	fmt.Println(cherryPickup([][]int{
		{0, -1, -1},
		{1, 0, -1},
		{1, 1,  1},
	}))
}