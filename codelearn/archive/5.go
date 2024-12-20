
package main
import (
	"fmt"
	"os"
	"strconv"
	"bufio"
	"strings"
)
func get4Sides(l []string) ([1030][1030]int, [1030][1030]int, [1030][1030]int, [1030][1030]int) {
	left := [1030][1030]int{}
	right := [1030][1030]int{}
	up := [1030][1030]int{}
	down := [1030][1030]int{}
	n := len(l)
	m := len(l[0])
	for i := 0; i < n; i++ {
		for j := 0; j < m; j++ {
			if l[i][j] == '0' {
				continue
			}
			if i == 0 && j == 0 {
				up[i][j] = 1
				left[i][j] = 1	
			}
			if i == 0 {
				up[i][j] = 1
			} else {
				up[i][j] = up[i-1][j]+1
			}

			if j == 0 {
				left[i][j] = 1
			} else {
				left[i][j] = left[i][j-1]+1
			}
		}
	}

	for i := n-1; i >= 0; i-- {
		for j := m-1; j >= 0; j-- {
			if l[i][j] == '0' {
				continue
			}
			if i == n-1 && j == m-1 {
				down[i][j] = 1
				right[i][j] = 1	
			}
			if i == n-1 {
				down[i][j] = 1
			} else {
				down[i][j] = down[i+1][j]+1
			}

			if j == m-1 {
				right[i][j] = 1
			} else {
				right[i][j] = right[i][j+1]+1
			}
		}
	}

	// for i := 0; i < n; i++ {
	// 	for j := 0; j < m; j++ {
	// 		fmt.Println(i,j,left[i][j], right[i][j], up[i][j], down[i][j])
	// 	}
	// }
	// fmt.Println("+++++++++++++++")
	return left, right, up, down
}

func cross1(left, right, up, down *[1030][1030]int, l []string, a, b, c, d int, rs *[1030][1030]int) {
	mid := (b+a)/2
	for i := c; i <= d; i++ {
		minup := -1
		mindown := -1
		for j := i; j <= d; j++ {
			k1 := -1
			if l[mid][j] == '1' && l[a][j] == '1' && up[mid][j] - up[a][j] == mid-a {
				k1 = up[mid][j]-up[a][j]+1
			} else {
				k1 = up[mid][j]
			}
			k2 := -1
			if l[mid][j] == '1' && l[b][j] == '1' && down[mid][j] - down[b][j] == b-mid {
				k2 = down[mid][j]-down[b][j]+1
			} else {
				k2 = down[mid][j]
			}
			if minup == -1 || minup > k1 {
				minup = k1
			}
			if mindown == -1 || mindown > k2 {
				mindown = k2
			}
			for x := 1; x <= minup; x++ {
				for y := 1; y <= mindown-1; y++ {
					// fmt.Println(x,y,x+y,i,j,j-i+1)
					rs[x+y][j-i+1]++
				}
			}
		}
	}
}

func cross2(left, right, up, down *[1030][1030]int, l []string, a, b, c, d int, rs *[1030][1030]int) {
	mid := (d+c)/2
	for i := a; i <= b; i++ {
		minleft := -1
		minright := -1
		for j := i; j <= b; j++ {
			k1 := -1
			k2 := -1
			if l[j][mid] == '1' && l[j][c] == '1' && left[j][mid] - left[j][c] == mid-c {
				k1 = left[j][mid]-left[j][c]+1
			} else {
				k1 = left[j][mid]
			}
			if l[j][mid] == '1' && l[j][d] == '1' && right[j][mid] - right[j][d] == d-mid {
				k2 = right[j][mid]-right[j][d]+1
			} else {
				k2 = right[j][mid]
			}

			if minleft == -1 || minleft > k1 {
				minleft = k1
			}
			if minright == -1 || minright > k2 {
				minright = k2
			}
			for x := 1; x <= minleft; x++ {
				for y := 1; y <= minright-1; y++ {
					// fmt.Println(a,b,c,d,minleft,minright)
					// fmt.Println(i,j,j-i+1,x,y,x+y)
					// fmt.Println("--------")
					rs[j-i+1][x+y]++
				}
			}
		}
	}
}

func do(left, right, up, down *[1030][1030]int, l []string, a, b, c, d int, rs *[1030][1030]int) {
	// fmt.Println(a,b,c,d)
	//printLandMap(rs)
	if b-a+1 == 1 && d-c+1 == 1 {
		if l[a][c] == '1' {
			rs[b-a+1][d-c+1]++
		}
		return
	}
	if (b-a+1) >= (d-c+1) {
		mid := (b+a)/2
		do(left, right, up, down, l, a, mid, c, d, rs)
		do(left, right, up, down, l, mid+1, b, c, d, rs)
		cross1(left, right, up, down, l, a, b, c, d, rs)
	} else {
		mid := (d+c)/2
		do(left, right, up, down, l, a, b, c, mid, rs)
		do(left, right, up, down, l, a, b, mid+1, d, rs)
		cross2(left, right, up, down, l, a, b, c, d, rs)
	}
}

func printLandMap(landMap [1030][1030]int, n int, m int) {
	for i := 1; i <= n; i++ {
		s := ""
		for j := 1; j <= m; j++ {
			s += " " + strconv.Itoa(landMap[i][j])
		}
		s = strings.TrimSpace(s)
		if i == len(landMap)-1 {
			fmt.Print(s)
		} else {
			fmt.Println(s)
		}
		// fmt.Println(landMap[i][1:])
	}
}
func solve(n int, m int, land []string) {
	left, right, up, down := get4Sides(land)
	// landMap := make([][]int, n+1)
	// for i := 0; i < n+1; i++ {
	// 	landMap[i] = make([]int, m+1)
	// }
	landMap := [1030][1030]int{}
	do(&left, &right, &up, &down, land, 0, n-1, 0, m-1, &landMap)
	printLandMap(landMap, n, m)
}
func main() {
	scanner := bufio.NewScanner(os.Stdin)
	i := int64(0)
	var n int64 = 0
	var m int64 = 0
	land := []string{}
	for scanner.Scan() {
        if i > n {
            break
        }
        if i == 0 {
            strs := strings.Split(scanner.Text(), " ")
            n, _ = strconv.ParseInt(strs[0], 10, 64)
            m, _ = strconv.ParseInt(strs[1], 10, 64)
        } else {
            land = append(land, scanner.Text())
        }
        i++ 
	}
	solve(int(n), int(m), land)
}