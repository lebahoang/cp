package main

import (
	"fmt"
	"math/rand"
)

func dfs(ans int, step int, grid [][]int, k int, used int, i int, j int, n int, m int, visited [][]int) int {
	if i == n-1 && j == m-1 {
		if ans == -1 || ans > step {
			ans = step
		}
		return ans
	}
	if i-1 >= 0 && j >= 0 && visited[i-1][j] == 0 {
		visited[i-1][j] = 1
		if grid[i-1][j] == 1 && used < k {
			ans = dfs(ans, step+1, grid, k, used+1, i-1, j, n, m, visited)
		} else if grid[i-1][j] == 0 {
			ans = dfs(ans, step+1, grid, k, used, i-1, j, n, m, visited)
		}
		visited[i-1][j] = 0
	}
	if i+1 < n && j >= 0 && visited[i+1][j] == 0 {
		visited[i+1][j] = 1
		if grid[i+1][j] == 1 && used < k {
			ans = dfs(ans, step+1, grid, k, used+1, i+1, j, n, m, visited)
		} else if grid[i+1][j] == 0 {
			ans = dfs(ans, step+1, grid, k, used, i+1, j, n, m, visited)
		}
		visited[i+1][j] = 0
	}
	if i >= 0 && j-1 >= 0 && visited[i][j-1] == 0 {
		visited[i][j-1] = 1
		if grid[i][j-1] == 1 && used < k {
			ans = dfs(ans, step+1, grid, k, used+1, i, j-1, n, m, visited)
		} else if grid[i][j-1] == 0 {
			ans = dfs(ans, step+1, grid, k, used, i, j-1, n, m, visited)
		}
		visited[i][j-1] = 0
	}
	if i >= 0 && j+1 < m && visited[i][j+1] == 0 {
		visited[i][j+1] = 1
		if grid[i][j+1] == 1 && used < k {
			ans = dfs(ans, step+1, grid, k, used+1, i, j+1, n, m, visited)
		} else if grid[i][j+1] == 0 {
			ans = dfs(ans, step+1, grid, k, used, i, j+1, n, m, visited)
		}
		visited[i][j+1] = 0
	}
	return ans
}

func shortestPath(grid [][]int, k int) int {
	ans := -1
	used := 0
	n := len(grid)
	m := len(grid[0])
	visited := make([][]int, n)
	for i := 0; i < n; i++ {
		visited[i] = make([]int, m)
	}
	return dfs(ans, 0, grid, k, used, 0, 0, n, m, visited)
}
func main() {
	// fmt.Println(shortestPath([][]int{
	// 	{0, 0, 0},
	// 	{1, 1, 0},
	// 	{0, 0, 0},
	// 	{0, 1, 1},
	// 	{0, 0, 0},
	// }, 1))
	rand.Seed(86)
	grid := make([][]int, 40)
	for i := 0; i < 40; i++ {
		grid[i] = make([]int, 40)
		for j := 0; j < 40; j++ {
			t := rand.Intn(2)
			if t > 1 {
				fmt.Println("dsadas")
			}
			grid[i][j] = t
		}
	}
	grid[0][0] = 0
	grid[39][39] = 0
	k := rand.Intn(1601)
	if k == 0 {
		k++
	}
	fmt.Println("GOGOGO")
	fmt.Println(shortestPath(grid, k))
}
