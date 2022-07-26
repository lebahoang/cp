package main

import "fmt"
type I struct {
	i int
	j int
}
func min(a ...int) int {
	v := int(2e9)
	for _,x := range a {
		if x == -1 {
			continue
		}
		if v > x {
			v = x
		}
	}
	return v
}
func dfs(n int, f *map[int]int) int {
	if n == 0 {
		return 0
	}
	v, found := (*f)[n]
	if found {
		// fmt.Println("VOVOVOVOVOOVO", n)
		return v
	}
	t := int(2e9)
	if n%2 == 0 {
		t = min(t, dfs(n/2, f)+1)
	}
	if n%3 == 0 {
		t = min(t, dfs(n/3, f)+1)
	}
	if n >= 1 {
		t = min(t, dfs(n-1, f)+1)
	}
	(*f)[n] = t
	return t
}

func do(n int64) ([35][35]int, map[int]int) {
	f := map[int]int{}
	dp := [35][35]int{}
	for i := 0; i < 32; i++ {
		for j := 0; j < 32; j++ {
			dp[i][j] = int(2e9)
		}
	}
	dp[1][0] = 2
	dp[0][1] = 2
	var x int64 = 1;
	for i := 0; i < 32; i++ {
		if i > 0 {
			x = x*2
		}
		var y int64 = 1
		for j := 0; j < 32; j++ {
			if j > 0 {
				y = y*3
			}
			if (x*y > n) {
				break
			}
			// f[int(x*y)] = I{i: i, j: j}
			if i-1 >= 0 {
				dp[i][j] = min(dp[i][j], 1+dp[i-1][j])
			}
			if j-1 >= 0 {
				dp[i][j] = min(dp[i][j], 1+dp[i][j-1])
			}
			f[int(x*y)] = dp[i][j]
		}
	}
	return dp, f
}
func minDays(n int) int {
	if n == 2 || n == 3 {
		return 2
	}
	nn := int64(n)
	_, f := do(nn)
    return dfs(n, &f)
}

func main() {
	fmt.Println(minDays(100000000))
	// fmt.Println(minDays(10))
	// fmt.Println(minDays(182))
}