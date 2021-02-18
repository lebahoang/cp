package main

import "fmt"

func traceBackward(node int, tracebackNodes []int, strongNodes []bool) []bool {
	strongNodes[node] = true
	for i := len(tracebackNodes) - 1; i >= 0; i-- {
		if tracebackNodes[i] != node {
			strongNodes[tracebackNodes[i]] = true
		} else {
			break
		}
	}
	// fmt.Println(node, "asds", tracebackNodes)
	return strongNodes
}
func dfs(n int, parent int, node int, tracebackNodes []int, neighs [][]int, visited []bool, strongNodes []bool) ([]bool, []bool) {
	// fmt.Println(node)
	if visited[node] {
		strongNodes = traceBackward(node, tracebackNodes, strongNodes)
		// fmt.Println("after traceback", strongNodes)
	} else {
		visited[node] = true
		tracebackNodes = append(tracebackNodes, node)
		for _, i := range neighs[node] {
			if i == parent {
				continue
			}
			visited, strongNodes = dfs(n, node, i, tracebackNodes, neighs, visited, strongNodes)
		}
		tracebackNodes = tracebackNodes[:len(tracebackNodes)-1]
	}
	visited[node] = false
	return visited, strongNodes
}
func criticalConnections(n int, connections [][]int) [][]int {
	rs := [][]int{}
	visited := make([]bool, n)
	strongNodes := make([]bool, n)
	neighs := make([][]int, n)
	for _, conn := range connections {
		a := conn[0]
		b := conn[1]
		neighs[a] = append(neighs[a], b)
		neighs[b] = append(neighs[b], a)
	}
	tracebackNodes := []int{}
	_, strongNodes = dfs(n, -1, 0, tracebackNodes, neighs, visited, strongNodes)
	for _, conn := range connections {
		a := conn[0]
		b := conn[1]
		if !strongNodes[a] || !strongNodes[b] {
			rs = append(rs, []int{a, b})
		}
	}
	return rs
}
func main() {
	fmt.Println(criticalConnections(4, [][]int{
		{0, 1},
		{1, 2},
		{2, 0},
		{1, 3},
	}))
}
