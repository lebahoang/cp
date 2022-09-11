package main

import "os"
import "fmt"
import "bufio"

func max(a ...int) int {
    v := int(-1)
    for i := 0; i < len(a); i++ {
        if a[i] == -1 {
            continue
        }
        if v == -1 || v < a[i] {
            v = a[i]
        }
    }
    return v
}


func solve(n int, m int, a, b string) string {
    dp := make([][]string, n)
    for i := 0; i < n; i++ {
        dp[i] = make([]string, m)
        for j := 0; j < m; j++ {
            if a[i] == b[j] {
                if i-1 >= 0 && j-1 >= 0 {
                    dp[i][j] = dp[i-1][j-1] + string(a[i])
                } else {
                    dp[i][j] = string(a[i])
                }
            } else {
                x := 0
                strx := ""
                if i-1 >= 0 {
                    x = len(dp[i-1][j])
                    strx = dp[i-1][j]
                }
                y := 0
                stry := ""
                if j-1 >= 0 {
                    y = len(dp[i][j-1])
                    stry = dp[i][j-1]
                }
                if x > y {
                    dp[i][j] = strx
                } else {
                    dp[i][j] = stry
                }
            }
        }
    }
    return dp[n-1][m-1]
}

func main() {
    scanner := bufio.NewScanner(os.Stdin)
    i := 0
    arr := make([]string, 2)
    for scanner.Scan() {
        if i > 1 {
            break
        }
        arr[i] = scanner.Text()
        i++
    }
    n := len(arr[0])
    m := len(arr[1])
    fmt.Println(solve(n, m, arr[0], arr[1]))
}
