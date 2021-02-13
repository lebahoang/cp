package main


import (
	"fmt"
)

func readLineManyInt(numberOfParams int, params ...int) {
	for i := 0; i < numberOfParams; i++ {
		fmt.Scanf("%d", &params[i])
	}
}

func readLineManyInt64(numberOfParams int, params ...int64) {
	for i := 0; i < numberOfParams; i++ {
		fmt.Scanf("%d", &params[i])
	}
}

func readLineManyFloat64(numberOfParams int, params ...float64) {
	for i := 0; i < numberOfParams; i++ {
		fmt.Scanf("%s", &params[i])
	}
}

func readLineManyString(numberOfParams int, params ...string) {
	for i := 0; i < numberOfParams; i++ {
		fmt.Scanf("%s", &params[i])
	}
}

func main() {
	var n int = 10
	fmt.Scanf("%d", &n)
	doors := make([]int, n)
	readLineManyInt(n, doors...)

	total := 0
	min := 0
	c := 0
	for _,char := range doors {
		if char == 0 {
			if c % 2 == 1 {
				min += c/2 + 1
			} else {
				min += c/2
			}
			c = 0
		} else {
			c += 1
			total += 1
		}
	}
	if c > 0 {
		if c % 2 == 1 {
			min += c/2 + 1
		} else {
			min += c/2
		}
	}
	fmt.Println(min, total)
}