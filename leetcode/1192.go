package main

import "fmt"

type I struct {
	a int
	b int
}

func traceBackward(node int, tracebackNodes *[]int, strongC *map[I]bool) {
	end := node
	for i := len(*tracebackNodes) - 1; i >= 0; i-- {
		if (*tracebackNodes)[i] != node {
			if end > (*tracebackNodes)[i] {
				// strongC[fmt.Sprintf("%d,%d", tracebackNodes[i], end)] = true
				(*strongC)[I{a: (*tracebackNodes)[i], b: end}] = true
			} else {
				// strongC[fmt.Sprintf("%d,%d", end, tracebackNodes[i])] = true
				(*strongC)[I{a: end, b: (*tracebackNodes)[i]}] = true
			}
		} else {
			break
		}
		end = (*tracebackNodes)[i]
	}
	// fmt.Println(node, "asds", tracebackNodes)
}
func dfs(n int, parent int, node int,
	tracebackNodes *[]int, neighs *[][]int,
	visited *[]bool, strongC *map[I]bool) {
	// fmt.Println(node, visited[node])
	if (*visited)[node] {
		traceBackward(node, tracebackNodes, strongC)
		// fmt.Println("after traceback", strongC)
	} else {
		(*visited)[node] = true
		(*tracebackNodes) = append((*tracebackNodes), node)
		for _, i := range (*neighs)[node] {
			if i == parent {
				continue
			}
			dfs(n, node, i, tracebackNodes, neighs, visited, strongC)
		}
		(*visited)[node] = false
		*tracebackNodes = (*tracebackNodes)[:len(*tracebackNodes)-1]
	}
}
func criticalConnections(n int, connections [][]int) [][]int {
	rs := [][]int{}
	visited := make([]bool, n)
	strongC := map[I]bool{}
	neighs := make([][]int, n)
	for _, conn := range connections {
		a := conn[0]
		b := conn[1]
		neighs[a] = append(neighs[a], b)
		neighs[b] = append(neighs[b], a)
	}
	tracebackNodes := []int{}
	dfs(n, -1, 0, &tracebackNodes, &neighs, &visited, &strongC)
	// fmt.Println("FINAL,", strongC)
	for _, conn := range connections {
		a := conn[0]
		b := conn[1]
		x := I{}
		if a < b {
			x = I{a: a, b: b}
		} else {
			x = I{a: b, b: a}
		}
		_, ok := strongC[x]
		if !ok {
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
