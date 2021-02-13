package main

import "fmt"

func solve(sx int, sy int, tx int, ty int) bool {
	// x,y ----> x,x+y OR x+y,y
	mx := tx
	my := ty
	for {
		fmt.Println(mx,my)
		if mx == sx && my == sy {
			return true
		}
		if mx == 0 || my == 0 || mx == my {
			return false
		}
		if mx == sx {
			if my > mx && my > sy {
				if my%mx == 0 && sx == sy {
					return true
				} else if (my-sy)%mx == 0 {
					return true
				}
				return false
			}
			return false
		} else if my == sy {
			if mx > my && mx > sx {
				if mx%my == 0 && sx == sy {
					return true
				} else if (mx-sx)%my == 0 {
					return true
				}
				return false
			}
			return false
		} else {
			if mx < my {
				my = my%mx
			} else {
				mx = mx%my
			}
		}
	}
}

func main() {
	// sx := 2
	// sy := 5
	// tx := 15
	// ty := 58
	sx := 9
	sy := 5
	tx := 8
	ty := 12
	// sx := 1
	// sy := 8
	// tx := 4
	// ty := 15
	fmt.Println(solve(sx,sy,tx,ty))
}