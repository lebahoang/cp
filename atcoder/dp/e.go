package main

import "os"
import "fmt"
import "strconv"
import "bufio"
import "strings"


func min(a ...int64) int64 {
    v := int64(-1)
    for i := 0; i < len(a); i++ {
        if a[i] == -1 {
            continue
        }
        if v == -1 || v > a[i] {
            v = a[i]
        }
    }
    // fmt.Println(a, v)
    return v
}

func solve(n int64, v int64, w int64, arr [][]int64) int64 {
    dp := make([]int64, v+1)
    t := make([]int64, v+1)
    for j := int64(1); j < v+1; j++ {
        dp[j] = -1
        t[j] = -1
    }
    for i := int64(0); i < n; i++ {
        for j := int64(1); j < v+1; j++ {
            if j-arr[i][1] >= 1 && dp[j-arr[i][1]] != -1 {
                t[j] = min(t[j], dp[j-arr[i][1]]+arr[i][0])
            }
        }
        t[arr[i][1]] = min(t[arr[i][1]], arr[i][0])

        for j := int64(1); j < v+1; j++ {
            dp[j] = min(dp[j], t[j])
            t[j] = -1
        }
    }

    rs := int64(0)
    for j := int64(0); j < v+1; j++ {
        // fmt.Println(j, dp[j])
        if dp[j] > -1 && dp[j] <= w {
            rs = j
        }
    }
    return rs
}

func main() {
    scanner := bufio.NewScanner(os.Stdin)
    var n int64 = 0
    var w int64 = 0
    var v int64 = 0
    var arr [][]int64
    i := int64(0)
    j := int64(0)
    for scanner.Scan() {
        if i > 0 && i > n {
            break
        }
        if i == 0 {
            strs := strings.Split(scanner.Text(), " ")
            n, _ = strconv.ParseInt(strs[0], 10, 64)
            w, _ = strconv.ParseInt(strs[1], 10, 64)
        } else {
            if i == 1 {
                arr = make([][]int64, n)
            }
            arr[j] = make([]int64, 2)
            strs := strings.Split(scanner.Text(), " ")
            arr[j][0], _ = strconv.ParseInt(strs[0], 10, 64)
            arr[j][1], _ = strconv.ParseInt(strs[1], 10, 64)
            v += arr[j][1]
            j++
        }
        i++ 
    }
    fmt.Println(solve(n, v, w, arr))
}