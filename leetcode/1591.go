package main

import "fmt"

func min(a ...int) int {
	var k int = 1e9
	for _, x := range a {
		if k > x {
			k = x
		}
	}
	return k
}

func max(a ...int) int {
	var k int = -1e9
	for _, x := range a {
		if k < x {
			k = x
		}
	}
	return k
}

func getColors(g [][]int) ([][]int, int, int, bool) {
	n := len(g)
	m := len(g[0])

	colors := make([][]int, 62)
	for i := 1; i <= 60; i++ {
		// xmin, ymin, xmax, ymax
		colors[i] = []int{1e9, 1e9, -1, -1, 0, 0}
	}
	minCl := int(1e9)
	maxCl := -1
	isAllZeros := true
	for i := 0; i < n; i++ {
		for j := 0; j < m; j++ {
			if g[i][j] == 0 {
				continue
			}
			isAllZeros = false
			colors[g[i][j]][0] = min(colors[g[i][j]][0], i)
			colors[g[i][j]][2] = max(colors[g[i][j]][2], i)
			colors[g[i][j]][1] = min(colors[g[i][j]][1], j)
			colors[g[i][j]][3] = max(colors[g[i][j]][3], j)
			colors[g[i][j]][4] = g[i][j]
			maxCl = max(maxCl, g[i][j])
			minCl = min(minCl, g[i][j])
		}
	}
	return colors, minCl, maxCl, isAllZeros
}

func isDone(g [][]int, colors []int) bool {
	xmin := colors[0]
	ymin := colors[1]
	xmax := colors[2]
	ymax := colors[3]
	color := colors[4]
	for a := xmin; a <= xmax; a++ {
		for b := ymin; b <= ymax; b++ {
			if g[a][b] != 0 && g[a][b] != color {
				return false
			}
		}
	}
	return true
}

func getColorsDone(g [][]int, colors [][]int, minCl int, maxCl int) (int, [][]int) {
	colorsDone := [][]int{}
	for i := minCl; i <= maxCl; i++ {
		if colors[i][4] == 0 {
			continue
		}
		if isDone(g, colors[i]) {
			colors[i][5] = 1
			colorsDone = append(colorsDone, colors[i])
		}
	}
	return len(colorsDone), colorsDone
}

func pp(g [][]int) {
	for _, x := range g {
		fmt.Println(x)
	}
	fmt.Println("----------------")
}
func isPrintable(g [][]int) bool {
	// n := len(g)
	// m := len(g[0])
	for {
		// pp(g)
		colors, minCl, maxCl, isAllZeros := getColors(g)
		// fmt.Println(minCl, maxCl, isAllZeros)
		if isAllZeros {
			return true
		}
		cnt, colorsDone := getColorsDone(g, colors, minCl, maxCl)
		if cnt == 0 {
			return false
		}
		for _, node := range colorsDone {
			for i := node[0]; i <= node[2]; i++ {
				for j := node[1]; j <= node[3]; j++ {
					g[i][j] = 0
				}
			}
		}
	}
}
func main() {
	g := [][]int{
		{1, 1, 1, 1},
		{1, 1, 3, 3},
		{1, 1, 3, 4},
		{5, 5, 1, 4},
	}
	// g := [][]int{
	// 	{1, 1, 1, 1, 1, 2, 2},
	// 	{1, 1, 3, 3, 3, 2, 2},
	// 	{1, 1, 3, 4, 5, 2, 2},
	// 	{1, 1, 3, 4, 4, 2, 2},
	// 	{1, 1, 1, 1, 2, 2, 2},
	// }
	fmt.Println(isPrintable(g))
}
