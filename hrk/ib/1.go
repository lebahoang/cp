package main
import "fmt"

func main() {
	n := uint(16)
	count := 0
	for k := uint(0); k < n; k++ {
		for i := uint(0); i < 1<<n; i++ {
			j := i
			for j > 0 {
				count ++
				j = i & (j-1)
			}
		}
	}

	fmt.Println(count)
}