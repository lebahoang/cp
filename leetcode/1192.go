package main

import "fmt"

// func traceBackward(node int, tracebackNodes []int,
// 	strongC [][]bool) [][]bool {
// 	end := node
// 	for i := len(tracebackNodes) - 1; i >= 0; i-- {
// 		if tracebackNodes[i] != node {
// 			strongC[tracebackNodes[i]][end] = true
// 			strongC[end][tracebackNodes[i]] = true
// 		} else {
// 			break
// 		}
// 		end = tracebackNodes[i]
// 	}
// 	// fmt.Println(node, "asds", tracebackNodes)
// 	return strongC
// }
// func dfs(n int, parent int, node int,
// 	tracebackNodes []int, neighs [][]int,
// 	visited []bool, strongC [][]bool) ([]bool, [][]bool, []int) {
// 	// fmt.Println(node, visited[node])
// 	if visited[node] {
// 		strongC = traceBackward(node, tracebackNodes, strongC)
// 		// fmt.Println("after traceback", strongC)
// 	} else {
// 		visited[node] = true
// 		tracebackNodes = append(tracebackNodes, node)
// 		for _, i := range neighs[node] {
// 			if i == parent {
// 				continue
// 			}
// 			visited, strongC, tracebackNodes = dfs(n, node, i, tracebackNodes, neighs, visited, strongC)
// 		}
// 		visited[node] = false
// 		tracebackNodes = tracebackNodes[:len(tracebackNodes)-1]
// 	}
// 	return visited, strongC, tracebackNodes
// }
// func criticalConnections(n int, connections [][]int) [][]int {
// 	rs := [][]int{}
// 	visited := make([]bool, n)
// 	strongC := [][]bool{}
// 	neighs := make([][]int, n)
// 	for _, conn := range connections {
// 		a := conn[0]
// 		b := conn[1]
// 		neighs[a] = append(neighs[a], b)
// 		neighs[b] = append(neighs[b], a)
// 		strongC[a] = append(strongC[a])
// 	}
// 	tracebackNodes := []int{}
// 	_, strongC, _ = dfs(n, -1, 0, tracebackNodes, neighs, visited, strongC)
// 	fmt.Println("FINAL,", strongC)
// 	for _, conn := range connections {
// 		a := conn[0]
// 		b := conn[1]
// 		ok1 := strongC[a][b]
// 		ok2 := strongC[b][a]
// 		if !ok1 && !ok2 {
// 			rs = append(rs, []int{a, b})
// 		}
// 	}
// 	return rs
// }

func primeFactors(n int) ([]int, int) {
	pfs := []int{}
	// Get the number of 2s that divide n
	for n%2 == 0 {
		pfs = append(pfs, 2)
		n = n / 2
	}

	// n must be odd at this point. so we can skip one element
	// (note i = i + 2)
	for i := 3; i*i <= n; i = i + 2 {
		// while i divides n, append i and divide n
		for n%i == 0 {
			pfs = append(pfs, i)
			n = n / i
		}
	}

	// This condition is to handle the case when n is a prime number
	// greater than 2
	if n > 2 {
		pfs = append(pfs, n)
	}

	rs := []int{}
	c := 0
	for i, x := range pfs {
		if i > 0 && pfs[i-1] != x {
			rs = append(rs, c)
			c = 1
		} else {
			c++
		}
	}
	rs = append(rs, c)
	fmt.Println(pfs)
	return rs, len(pfs)
}

func calculateC(mod int) [10050][20]int {
	c := [10050][20]int{}
	n := 10030
	m := 17
	c[1][0] = 1
	c[1][1] = 1
	for i := 2; i <= n; i++ {
		c[i][0] = 1
		for j := 1; j <= m; j++ {
			c[i][j] = (c[i-1][j-1]%mod + c[i-1][j]%mod) % mod
		}
	}
	return c
}
func waysToFillArray(queries [][]int) []int {
	rs := []int{}
	var mod int = 1e9 + 7
	cs := calculateC(mod)
	// n := 10000
	// m := 17
	// dp := compute(n, m, mod)
	for _, q := range queries {
		if q[1] == 1 {
			rs = append(rs, 1)
			continue
		}
		n := q[0]
		a, _ := primeFactors(q[1])
		t := 1
		for _, x := range a {
			fmt.Println(n+x-1, x, cs[n+x-1][x])
			t = (t % mod * cs[n+x-1][x] % mod) % mod
		}
		// t = (t % mod * cs[n-k+k+1-1][n-k] % mod) % mod
		rs = append(rs, t)
	}
	return rs
}
func main() {
	fmt.Println(waysToFillArray([][]int{
		// {2, 6}, {5, 1}, {73, 660},
		// {2, 6},
		{9999, 5728}, {9995, 4224},
	}))
}
