package main
import (
	"fmt"
)
type m struct {
	a int;
	b int;
}
func dfs1(i int, vs [][]int, visited []bool, d map[m]bool, parent []int) int {

}
func dfs2(j int, d map[m]bool, parent []int) {

}
func criticalConnections(n int, connections [][]int) [][]int {
	d := map[m]bool{}
	visited := make([]bool, n+2)
	vs := make([][]int, n+2)
	parent := make([]int, n+2)
	for i := 0; i < n; i++ {
		visited[i] = false
		parent[i] = -1
	}
	for _, x := range connections {
		it1 := m{a: x[0], b: x[1]}
		it2 := m{a: x[1], b: x[0]}
		d[it1] = true
		d[it2] = true
		vs[x[0]] = append(vs[x[0]], x[1])
		vs[x[1]] = append(vs[x[1]], x[0])
	}
	fmt.Println(d)
	j := dfs1(0, vs, visited, d, parent)
	dfs2(j, d, parent)
	ans := [][]int{}
	for it, b := range d {
		if (!b) {
			ans = append(ans, []int{it.a, it.b})
		}
	}
	return ans
}
func main() {
	criticalConnections(4, [][]int{
		{0,1},
		{1,2},
		{2,0},
		{1,3},
	})
}