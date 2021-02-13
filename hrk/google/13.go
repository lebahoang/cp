package main
import (
    "fmt"
)


// func one(s string) bool {
//     stack := []byte{}
//     for i := 0; i < len(s); i++ {
//         if s[i] == ')' {
//             if len(stack) == 0 {
//                 return false
//             }
//             top := stack[len(stack)-1]
//             if top == '(' {
//                 stack = stack[:len(stack)-1]
//             } else {
//                 return false
//             }
//         } else if s[i] == '}' {
//             if len(stack) == 0 {
//                 return false
//             }
//             top := stack[len(stack)-1]
//             if top == '{' {
//                 stack = stack[:len(stack)-1]
//             } else {
//                 return false
//             }
//         } else if s[i] == ']' {
//             if len(stack) == 0 {
//                 return false
//             }
//             top := stack[len(stack)-1]
//             if top == '[' {
//                 stack = stack[:len(stack)-1]
//             } else {
//                 return false
//             }
//         } else {
//             stack = append(stack, s[i])
//         }
//     }

//     if len(s) > 0 {
//         return false
//     }
//     return true
// }

// func solve44(s string, p string) bool {
//     ls := len(s)
//     lp := len(p)
//     if lp == 0 {
//         if ls == 0 {
//             return true
//         }
//         return false
//     }
//     if ls == 0 {
//         f := true
//         for i := 0; i < lp; i++ {
//             if p[i] != '*' {
//                 f = false
//                 break
//             }
//         }
//         return f
//     }
//     dp := make([][]bool, ls)
//     tempPs := make([]bool, lp)
//     allStar := make([]bool, lp)
//     for i := 0; i < ls; i++ {
//         dp[i] = make([]bool, lp)
//         for j := 0; j < lp; j++ {
//             dp[i][j] = false
//             tempPs[j] = false
//             if p[j] == '*' && (j == 0 || allStar[j-1]) {
//                 allStar[j] = true
//             } else {
//                 allStar[j] = false
//             }
//         }
//     }
//     for i := 0; i < ls; i++ {
//         for j := 0; j < lp; j++ {
//             if p[j] == '*' {
//                 if j == 0 {
//                     dp[i][j] = true
//                     tempPs[j] = true
//                 } else if tempPs[j-1] {
//                     dp[i][j] = true
//                     tempPs[j] = true
//                 }
//             } else if p[j] == '?' || s[i] == p[j] {
//                 if j == 0 && i == 0 {
//                     dp[i][j] = true
//                     tempPs[j] = true
//                 } else if j > 0 {
//                     if i == 0 {
//                         if allStar[j-1] {
//                             dp[i][j] = true
//                             tempPs[j] = true
//                         }
//                     } else {
//                         if dp[i-1][j-1] {
//                             dp[i][j] = true
//                             tempPs[j] = true
//                         } 
//                     }
//                 }
//             }
//         }
//     }

//     // for j := 0; j < lp; j++ {
//     //     for i := 0; i < ls; i++ {
//     //         fmt.Println(i,j,dp[i][j])
//     //     }
//     // }
//     return dp[ls-1][lp-1]
// }

// func max(a ...int) int{
//     v := 0
//     for _,vv := range a {
//         if v < vv {
//             v = vv
//         }
//     }
//     return v
// }

// func solve123(p []int) int {
//     n := len(p)
//     minBuy := make([]int, n)
    
//     for i := 0; i < n; i++ {
//         if i == 0 {
//             minBuy[i] = p[i]
//         } else {
//             if p[i] < minBuy[i-1] {
//                 minBuy[i] = p[i]
//             } else {
//                 minBuy[i] = minBuy[i-1]
//             }    
//         }
//     }
//     dp1 := make([]int, n)
//     for i := 1; i < n; i++ {
//         if p[i]-minBuy[i-1] > dp1[i-1] {
//             dp1[i] = p[i]-minBuy[i-1] 
//         } else {
//             dp1[i] = dp1[i-1]
//         }
//     }

//     maxSell := make([]int, n)
//     for i := n-1; i > -1; i-- {
//         if i == n-1 {
//             maxSell[i] = p[i]
//         } else {
//             if p[i] > maxSell[i+1] {
//                 maxSell[i] = p[i]
//             } else {
//                 maxSell[i] = maxSell[i+1]
//             }
//         }
//     }
//     dp2 := make([]int, n)
//     for i := n-2; i > -1; i-- {
//         if maxSell[i+1]-p[i] > dp2[i+1] {
//             dp2[i] = maxSell[i+1]-p[i]
//         } else {
//             dp2[i] = dp2[i+1]
//         }
//     }

//     maxV := 0
//     for i := 0; i < n; i++ {
//         t := 0
//         if i == 0 {
//             t = max(0, dp2[i])
//         } else if i < n-2 {
//             t = max(dp1[i], dp2[i+1], dp1[i]+dp2[i+1])
//         } else if i == n-2 {
//             t = max(dp1[i], dp2[i])
//         } else {
//             t = max(0, dp1[i])
//         }
//         if maxV < t {
//             maxV = t
//         }
//     }
//     return maxV
// }

func max(a ...int64) int64{
    v := int64(-9223372036854775808)
    for _,vv := range a {
        if v < vv {
            v = vv
        }
    }
    return v
}


func foo(a []int, b []int, i,j,l int, dp map[string]int64) int64{
    key := fmt.Sprintf("%s,%s,%s", i, j, l)
    if _, ok := dp[key]; ok {
        return dp[key]
    }
    if i-1 >= 0 {
        dp[key] = foo(a,b,i-1,j,l,dp)
        if l-1 >= 0 {
            dp[key] = max(dp[key], foo(a,b,i-1,j,l-1,dp)*10+a[i-1])
        }
    }
    if j-1 >= 0 {
        dp[key] = max(dp[key], foo(a,b,i,j-1,l,dp))
        if l-1 >= 0 {
            dp[key] = max(dp[key], foo(a,b,i,j-1,l-1,dp)*10+b[j-1])
        }
    }
    return dp[key]
}

func solve321(a []int, b []int, k int) []int {
    n := len(a)
    m := len(b)
    dp := map[string]int64{}
    r := foo(a,b,n,m,k,dp)
    rs := make([]int, k)
    i := k-1
    for {
        t := int(r%10)
        rs[i] = t
        r = (r-t)/10
        if r == 0 {
            break
        }
        i --
    }
    return rs
}

func main() {
    // s := "a"
    // p := "*a"
    // s := "abc"
    // p := "a*??"
    // s := "cc" 
    // p := "?*"
    // s := "mississippi"
    // p := "m??*ss*?i*pi"
    // fmt.Println(solve44(s, p))
    // prices := []int{3,3,5,0,0,3,1,4}
    // prices := []int{1,2,3,4,5}
    // prices := []int{7,6,4,3,1}
    // prices := []int{}
    // fmt.Println(solve123(prices))
    nums1 := []int{7,6,4,0,5,8,2,2,6,8,2,0,5,3,0,8,7,7,7,3,3,2,0,8,4,0,1,2}
    nums2 := []int{1,9,2,3,9,6,1,5,8,7,9,9,1,5,4,1,7,2,2,2,1,1,7,2,8,1,2,6,6,6,5,1,9,9,8,1,4,6,3,3,1,5,0,0,0,5,6,6,2,3,6,6,0,3,5,4,2,4,0,8,2,4,6,1,0,1,1,4,0,3,0,9,2,5,6,3,4,7,0,7,2,4,1,0,6,6,9,6,5,7,2,4,7,5,7,1,9,3,5,8,8,7,2,4,7,9,7,4,5,1,6,3,5,5,8,8,6,2,8,0,9,9,0,3,8,1,3,0,3,5,7,7,6,4,2,5,8,3,3,5}
    k := 140
    fmt.Println(solve321(nums1, nums2, k))
}