package main

import (
	"fmt"
)
func abs(x int) int {
	if x < 0 {
		return -x
	}
	return x
}
func max(a ...int) int {
	v := -1
	for _, x := range a {
		if v < x {
			v = x
		}
	}
	return v
}
func min(a ...int) int {
	v := int(1e9)
	for _, x := range a {
		if v > x {
			v = x
		}
	}
	return v
}
func isFinished(g [3][3]string) bool {
	f1 := false
	f2 := false
	for i := 0; i < 3; i++ {
		for j := 0; j < 3; j++ {
			if g[i][j] == "" {
				continue
			}
			c := 1
			for k := i+1; k < 3; k++ {
				if g[k][j] == g[i][j] || g[k][j] == "" {
					c++
				}
			}
			if c == 3 {
				if g[i][j] == "x" {
					f1 = true
				} else {
					f2 = true
				}
				continue
			}
			c = 1
			for k := j+1; k < 3; k++ {
				if g[i][k] == g[i][j] || g[i][k] == "" {
					c++
				}
			}
			if c == 3 {
				if g[i][j] == "x" {
					f1 = true
				} else {
					f2 = true
				}
				continue
			}
			c = 1
			a := i+1
			b := j+1
			for {
				if a >= 3 || b >= 3 {
					break
				}
				if g[a][b] == g[i][j] || g[a][b] == "" {
					c++
				}
				a++
				b++
			}
			if c == 3 {
				if g[i][j] == "x" {
					f1 = true
				} else {
					f2 = true
				}
				continue
			}
			c = 1
			a = i+1
			b = j-1
			for {
				if a >= 3 || b < 0 {
					break
				}
				if g[a][b] == g[i][j] || g[a][b] == "" {
					c++
				}
				a++
				b--
			}
			if c == 3 {
				if g[i][j] == "x" {
					f1 = true
				} else {
					f2 = true
				}
				continue
			}
		}
	}
	if !f1 && !f2 {
		return true
	}
	return false
}
func ticTacToe(s []int) int {
	if len(s) == 0 {
		return -1
	}
	g := [3][3]string{
		{"","",""},
		{"","",""},
		{"","",""},
	}
	for k, x := range s {
		i := ((x-1)-(x-1)%3)/3
		j := (x-1)%3
		if k%2 == 0 {
			g[i][j] = "x"
		} else {
			g[i][j] = "o"
		}
	}
	for i := 0; i < 3; i++ {fmt.Println(g[i])}

	f1 := false
	f2 := false
	for i := 0; i < 3; i++ {
		for j := 0; j < 3; j++ {
			if g[i][j] == "" {
				continue
			}
			c := 1
			for k := i+1; k < 3; k++ {
				if g[k][j] == g[i][j] {
					c++
				}
			}
			if c == 3 {
				if g[i][j] == "x" {
					f1 = true
				} else {
					f2 = true
				}
				continue
			}
			c = 1
			for k := j+1; k < 3; k++ {
				if g[i][k] == g[i][j] {
					c++
				}
			}
			if c == 3 {
				if g[i][j] == "x" {
					f1 = true
				} else {
					f2 = true
				}
				continue
			}
			c = 1
			a := i+1
			b := j+1
			for {
				if a >= 3 || b >= 3 {
					break
				}
				if g[a][b] == g[i][j] {
					c++
				}
				a++
				b++
			}
			if c == 3 {
				if g[i][j] == "x" {
					f1 = true
				} else {
					f2 = true
				}
				continue
			}
			c = 1
			a = i+1
			b = j-1
			for {
				if a >= 3 || b < 0 {
					break
				}
				if g[a][b] == g[i][j] {
					c++
				}
				a++
				b--
			}
			if c == 3 {
				if g[i][j] == "x" {
					f1 = true
				} else {
					f2 = true
				}
				continue
			}
		}
	}
	if f1 && !f2 {
		return 1
	} else if f2 && !f1 {
		return 2
	} else if f1 && f2 {
		return 1
	}
	if isFinished(g) {
		return 0
	}
	if len(g) == 8 {
		return 2
	}
	return -1
}

func main() {
	fmt.Println(ticTacToe([]int{2,1,3,5,6,9}))
}