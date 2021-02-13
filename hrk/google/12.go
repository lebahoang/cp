package main
// import (
// 	"fmt"
// 	"sort"
// 	"strings"
// )

// type sortString []string

// func isLetters(s string) bool {
// 	nums := []byte{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}
// 	for i := 0; i < len(s); i++ {
// 		for j := 0; j < len(nums); j++ {
// 			if s[i] == nums[j] {
// 				return false
// 			}
// 		}
// 	}
// 	return true
// }

// func (s sortString) Len() int {
// 	return len(s)
// }


// func (s sortString) Swap(i, j int) {
// 	s[i], s[j] = s[j], s[i]
// }

// func (s sortString) Less(i, j int) bool {
// 	a := strings.Join(strings.Split(s[i], " ")[1:], " ")
// 	b := strings.Join(strings.Split(s[j], " ")[1:], " ") 
// 	if isLetters(a) && !isLetters(b) {
// 		return true
// 	}
// 	if !isLetters(a) && isLetters(b) {
// 		return false
// 	}

// 	if isLetters(a) && isLetters(b) {
// 		if a == b {
// 			return strings.Split(s[i], " ")[0] < strings.Split(s[j], " ")[0]
// 		}
// 		return a < b
// 	}
// 	return false
// }



// func solve(logs []string) []string {
// 	rs1 := []string{}
// 	rs2 := []string{}
// 	for _, str := range logs {
// 		a := strings.Join(strings.Split(str, " ")[1:], " ")
// 		if !isLetters(a) {
// 			rs2 = append(rs2, str)
// 		} else {
// 			rs1 = append(rs1, str)
// 		}
// 	}
// 	sort.Sort(sortString(rs1))
// 	rs1 = append(rs1, rs2...)
// 	return rs1
// }

import "fmt"

func isValid(s string) bool{
    stack := []string{}
    count := 0
    for _, c := range s {
        if c == '(' {
            stack = append(stack, string(c))
            count ++
        } else if c == ')' {
            if count > 0 {
                stack = stack[:count]
                count --
            } else {
                return false    
            }
        }
    }

    if count != 0 {
        return false
    }
    return true
}

func generateAll(temp string, i int, m int, rs []string) []string {
	if i == m {
		rs = append(rs, temp)
		return rs
	}
	rs = generateAll(temp+"(", i+1, m, rs)
	rs = generateAll(temp+")", i+1, m, rs)
	return rs
}
func solve(n int) []string {
	m := 2*n
	rs := []string{}
	rs = generateAll("", 0, m, rs)
	rs1 := []string{}
	for _, s := range rs {
		if isValid(s) {
			rs1 = append(rs1, s)
		}
	}
	return rs1
}



func main() {
	n := 0
	fmt.Println(solve(n))
}