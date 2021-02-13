package main
import (
	"fmt"
)
func max(a ...int) int {
	v := -1
	for _, x := range a {
		if v < x {
			v = x
		}
	}
	return v
}
func abs(x int) int {
	if x < 0 {
		return -x
	}
	return x
}
func bruteForce(a []int, b []int) int {
	maxV := -1
	for i := 0; i < len(a)-1; i++ {
		for j := i+1; j < len(a); j++ {
			t := abs(a[i]-a[j]) + abs(b[i]-b[j]) + abs(j-i)
			maxV = max(maxV, t)
			fmt.Println(maxV, a[i], a[j], b[i], b[j], t)
		}
	}
	return maxV
}

// a1[i]-a1[j] + a2[i]-a2[j] + i-j
// -a1[i]+a1[j]+ a2[i]-a2[j] + i-j
// a1[i]-a1[j] - a2[i]+a2[j] + i-j
// -a1[i]+a1[j]- a2[i]+a2[j] + i-j
func maxPrefix(a1, a2 []int) ([]int, []int, []int, []int) {
	x := []int{-a1[0]-a2[0]}
	y := []int{a1[0]-a2[0]}
	z := []int{-a1[0]+a2[0]}
	p := []int{a1[0]+a2[0]}
	for i := 1; i < len(a1); i++ {
		tt := -a1[i]-a2[i]-i
		if tt > x[i-1] {
			x = append(x, tt)
		} else {
			x = append(x, x[i-1])
		}

		tt = a1[i]-a2[i]-i
		if tt > y[i-1] {
			y = append(y, tt)
		} else {
			y = append(y, y[i-1])
		}

		tt = -a1[i]+a2[i]-i
		if tt > z[i-1] {
			z = append(z, tt)
		} else {
			z = append(z, z[i-1])
		}

		tt = a1[i]+a2[i]-i
		if tt > p[i-1] {
			p = append(p, tt)
		} else {
			p = append(p, p[i-1])
		}	
	}
	return x,y,z,p
}

// a1[i]-a1[j] + a2[i]-a2[j] + i-j
// -a1[i]+a1[j]+ a2[i]-a2[j] + i-j
// a1[i]-a1[j] - a2[i]+a2[j] + i-j
// -a1[i]+a1[j]- a2[i]+a2[j] + i-j
func maxAbsValExpr(arr1 []int, arr2 []int) int {
	maxV := -1
	x,y,z,p := maxPrefix(arr1, arr2)
	for i := 1; i < len(arr1); i++ {
		a := arr1[i]+arr2[i]+i+x[i-1]
		b := -arr1[i]+arr2[i]+i+y[i-1]
		c := arr1[i]-arr2[i]+i+z[i-1]
		d := -arr1[i]-arr2[i]+i+p[i-1]
		maxV = max(maxV, a, b, c, d)
	}
	return maxV
}
func main() {
	// fmt.Println(maxAbsValExpr(
	// 	[]int{1,-2,-5,0,10},
	// 	[]int{0,-2,-1,-7,-4},
	// ))
	// fmt.Println(bruteForce(
	// 	[]int{-5,1,4,-10,-7,-5,-2,-7,-2,10,1,-8,-8,-8,2,-3,-5,-3,-4,3},
	// 	[]int{3,9,-6,6,-8,-2,8,8,-6,7,5,0,-4,5,-10,-5,-9,-10,8,10},
	// ))
	// fmt.Println("-----------------")
	fmt.Println(maxAbsValExpr(
		[]int{-5,1,4,-10,-7,-5,-2,-7,-2,10,1,-8,-8,-8,2,-3,-5,-3,-4,3},
		[]int{3,9,-6,6,-8,-2,8,8,-6,7,5,0,-4,5,-10,-5,-9,-10,8,10},
	))
	// fmt.Println(minMaxPrefix(
	// 	[]int{5,5,6,5},
	// ))
}