package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func min(a ...int64) int64 {
	v := int64(-1)
	for i := 0; i < len(a); i++ {
		if a[i] == 0 {
			continue
		}
		if v == -1 || v > a[i] {
			v = a[i]
		}
	}
	return v
}

func do(i int64, j int64, arr []int64, total [405][405]int64, dp [405][405]int64) int64 {
	fmt.Println(i, j)
	if i == j {
		return 0
	}
	if i == j-1 {
		dp[i][j] = arr[i] + arr[j]
		return dp[i][j]
	}
	if dp[i][j] > 0 {
		return dp[i][j]
	}
	for k := i; k < j; k++ {
		x := do(i, k, arr, total, dp)
		xx := total[i][k]
		y := do(k+1, j, arr, total, dp)
		yy := total[k+1][j]
		// fmt.Println(i,k,j,x+y+xx+yy)
		dp[i][j] = min(dp[i][j], x+y+xx+yy)
	}
	// fmt.Println(i,j,dp[i][j])
	return dp[i][j]
}
func solve(n int64, arr []int64) int64 {
	dp := [405][405]int64{}
	total := [405][405]int64{}
	for i := int64(0); i < n; i++ {
		for j := i; j < n; j++ {
			if j-1 >= i {
				total[i][j] = total[i][j-1] + arr[j]
			} else {
				total[i][j] = arr[j]
			}
		}
	}
	for j := int64(0); j < n; j++ {
		for i := int64(0); i < n; i++ {
			if i+j >= n {
				break
			}
			if j == 0 {
				dp[i][i+j] = 0
			} else if j == 1 {
				dp[i][i+j] = arr[i] + arr[i+j]
			} else {
				for k := i; k < i+j; k++ {
					dp[i][i+j] = min(dp[i][i+j], dp[i][k]+dp[k+1][i+j]+total[i][k]+total[k+1][i+j])
				}
			}
		}
	}
	return dp[0][n-1]
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	var n int64 = 0
	var arr = []int64{}
	var i int64 = 0
	for scanner.Scan() {
		if i > 1 {
			break
		}
		if i == 0 {
			n, _ = strconv.ParseInt(scanner.Text(), 10, 64)
		} else {
			strs := strings.Split(scanner.Text(), " ")
			for j := int64(0); j < n; j++ {
				x, _ := strconv.ParseInt(strs[j], 10, 64)
				arr = append(arr, x)
			}
		}
		i++
	}

	fmt.Println(solve(n, arr))
}
