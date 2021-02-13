package main
import (
	"fmt"
)


// type TreeNode struct {
//     Val int
//     Left *TreeNode
//     Right *TreeNode
// }


// func max(a ...int) int{
//     v := -9223372036854775808
//     for _,vv := range a {
//         if v < vv {
//             v = vv
//         }
//     }
//     return v
// }

// func solve(root *TreeNode, fnV *int) int{
//     maxLeft := 0
//     if root.Left != nil {
//         maxLeft = solve(root.Left, fnV)
//     }
//     maxRight := 0
//     if root.Right != nil {
//         maxRight = solve(root.Right, fnV)
//     }
//     *fnV = max(*fnV, root.Val, root.Val+maxLeft, root.Val+maxRight, root.Val+maxLeft+maxRight)
//     return max(root.Val, root.Val+maxLeft, root.Val+maxRight)
// }


// func main() {
//     a := &TreeNode{
//         Val: -1,
//         Left: nil,
//         Right: nil,
//     }
//     b := &TreeNode{
//         Val: -7,
//         Left: nil,
//         Right: nil,
//     }
//     c := &TreeNode{
//         Val: -20,
//         Left: a,
//         Right: b,
//     }
//     d := &TreeNode{
//         Val: -9,
//         Left: nil,
//         Right: nil,
//     }
//     e := &TreeNode{
//         Val: -10,
//         Left: d,
//         Right: c,
//     }
//     // fnV := math.MinInt64
//     fnV := -9223372036854775808
//     solve(e, &fnV)
//     fmt.Println(fnV)
// }

// func min(a ...int) int{
//     v := -1
//     for _,vv := range a {
//         if v == -1 || v > vv {
//             v = vv
//         }
//     }
//     return v
// }

// func solve(s string) int{
//     n := len(s)
//     dp := make([][]int, n)
//     for i := 0; i < n; i++ {
//         dp[i] = make([]int, n)
//     }
//     for i := 0; i < n; i++ {
//         if s[i] != '(' && s[i] != ')' {
//             dp[i][i] = 0
//         } else {
//             dp[i][i] = 1
//         }
//     }
//     for i := 0; i < n-1; i++ {
//         if (s[i] == '(' && s[i+1] == ')') || (s[i] != '(' && s[i] != ')' && s[i+1] != '(' && s[i+1] != ')') {
//             dp[i][i+1] = 0 
//         } else {
//             if (s[i] != '(' && s[i] != ')') || (s[i+1] != '(' && s[i+1] != ')') {
//                 dp[i][i+1] = 1
//             } else {
//                 dp[i][i+1] = 2    
//             }
//         }
//     }
//     for j := 2; j < n; j++ {
//         for i := 0; i < n; i++ {
//             if i+j < n {
//                 minV := -1
//                 for k := i; k < i+j; k++ {
//                     if minV == -1 || minV > dp[i][k]+dp[k+1][i+j] {
//                         minV = dp[i][k]+dp[k+1][i+j]
//                     }
//                 }
//                 c := dp[i+1][i+j-1]+2
//                 if (s[i] == '(' && s[i+j] == ')') || (s[i] != '(' && s[i] != ')' && s[i+j] != '(' && s[i+j] != ')') {
//                     c = c-2
//                 } 
//                 dp[i][i+j] = min(minV,c)
//             }
//         }
//     }
//     return dp[0][n-1]
// }


// func isValid(s string) bool{
//     stack := []string{}
//     count := 0
//     for _, c := range s {
//         if c == '(' {
//             stack = append(stack, string(c))
//             count ++
//         } else if c == ')' {
//             if count > 0 {
//                 stack = stack[:count]
//                 count --
//             } else {
//                 return false    
//             }
//         }
//     }

//     if count != 0 {
//         return false
//     }
//     return true
// }

// func getString(s string, ind int, returnedString string, rs map[string]int) map[string]int{
//     if ind == len(s) {
//         if returnedString != "" && isValid(returnedString) {
//             // fmt.Println(returnedString, isValid(returnedString),  "ssss")
//             // rs = append(rs, returnedString)
//             if _, ok := rs[returnedString]; !ok {
//                 rs[returnedString] = 1
//             }
//         }
//         return rs
//     }
//     if s[ind] != '(' && s[ind] != ')' {
//         rs = getString(s, ind+1, returnedString + string(s[ind]), rs)
//     } else {
//         rs = getString(s, ind+1, returnedString + string(s[ind]), rs)
//         rs = getString(s, ind+1, returnedString, rs)
//     }
//     return rs
// }

// func solve(s string) []string{
//     rs := map[string]int{}
//     rs = getString(s, 0, "", rs)
//     rs1 := []string{}
//     maxV := 0
//     for str, _ := range rs {
//         if maxV < len(str) {
//             maxV = len(str)
//             rs1 = []string{str}
//         } else if maxV == len(str) {
//             rs1 = append(rs1, str)
//         }
//     }
//     if len(rs1) == 0 {
//         rs1 = append(rs1, "")
//     }
//     return rs1
// }

type State struct {
    Sum int
    Indices [3]int
}

func less(a [3]int, b [3]int) bool {
    n := len(a)
    for i := 0; i < n; i++ {
        if a[i] < b[i] {
            return true
        }
    }
    return false 
}

func solve689(nums []int, k int) []int {
    n := len(nums)
    m := 3
    sumFrom := make([]int, n)
    for i := 0; i < k; i++ {
        sumFrom[0] += nums[i]
    }
    
    for i := k; i < n; i++ {
        sumFrom[i-k+1] = sumFrom[i-k]-nums[i-k]+nums[i]
    }
    dp := make([][]State, n)
    for i := 0; i < n; i++ {
      dp[i] = make([]State, m+1)
      for j := 0; j < m+1; j++ {
        dp[i][j] = State{Sum: 0, Indices: [3]int{}}
      }
    }
    for i := 0; i < n; i++ {
        if i < k-1 {
            continue
        }
        for j := 1; j < 4; j++ {
            if i-k >= 0 && j-1 > 0 && dp[i-k][j-1].Sum == 0 {
                continue
            }
            x := 0
            a := [3]int{}
            if i-k >= 0 {
                x = dp[i-1][j].Sum
                a = dp[i-1][j].Indices
            }
            y := sumFrom[i-k+1]
            b := [3]int{}
            if i-k >= 0 {
                y += dp[i-k][j-1].Sum
                b = dp[i-k][j-1].Indices
            }
            b[j-1] = i-k+1
            if x > y {
                dp[i][j] = State{Sum: x, Indices: a}
            } else if x < y {
                dp[i][j] = State{Sum: y, Indices: b}
            } else {
                if less(a, b) {
                    dp[i][j] = State{Sum: x, Indices: a}
                } else {
                    dp[i][j] = State{Sum: y, Indices: b}
                }
            }
        }
    }

    // for i := 0; i < n; i++ {
    //     for j := 1; j < 4; j++ {
    //         fmt.Println(i, j, dp[i][j].Sum, dp[i][j].Indices)
    //     }
    // }
    
    rs := []int{}
    for _, v := range dp[n-1][m].Indices {
        rs = append(rs, v)
    }
    return rs
}

func main() {
    // rs := solve("(a)(abb))(dsad)kkk")
    // rs := solve(")(")
    // rs := solve("akkk()))(())))h")
    // fmt.Println(rs)

    // nums := []int{1,2,1,2,6,7,5,1}
    // k := 2
    nums := []int{1,2,1,2,1111,2,5}
    k := 2
    // nums := []int{1,2,3,4}
    // k := 1
    fmt.Println(solve689(nums, k))
}