package main

import (
	"fmt"
	// "strings"
)


func main() {
	var n int
	fmt.Scanln(&n)
	for i := 0; i < n; i++ {
		var t string
		fmt.Scanln(&t)
		a := ""
		b := ""
		for i := 0; i < 5; i++ {
			if i == len(t) {
				break
			}
			a += string(t[i]);
		}
		for i := len(t)-2; i < len(t); i++ {
			if i == len(t) {
				break
			}
			b += string(t[i]);
		}
		if a == "hydro" && b == "ic" {
			fmt.Println("non-metal acid")
		} else if b == "ic" {
			fmt.Println("polyatomic acid")
		} else {
			fmt.Println("not an acid")
		}

		// if strings.HasPrefix(t, "hydro") && strings.HasSuffix(t, "ic") {
		// 	fmt.Println("non-metal acid")
		// } else if strings.HasSuffix(t, "ic") {
		// 	fmt.Println("polyatomic acid")
		// } else {
		// 	fmt.Println("not an acid")
		// }
	}
}