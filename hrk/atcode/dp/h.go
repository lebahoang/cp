package main

import "os"
import "fmt"
import "strconv"
import "bufio"
import "strings"


func solve(h int64, w int64, grid []string) int64 {
    var mod int64 = 1e9+7
    // dp := make([][]int64, h)
    // for i := int64(0); i < h; i++ {
    //     for j := int64(0); j < w; j++ {
    //         dp[i] = make([]int64, w)
    //     }
    // }
    dp := [1000][1000]int64{}

    dp[0][0] = 1
    for i := int64(0); i < h; i++ {
        for j := int64(0); j < w; j++ {
            if i == 0 && j == 0 {
                continue
            }
            if i-1 >= 0 && grid[i-1][j] == '.' {
                dp[i][j] += dp[i-1][j]
            }
            if j-1 >= 0 && grid[i][j-1] == '.' {
                dp[i][j] += dp[i][j-1]
            }
            dp[i][j] = dp[i][j] % mod
        }
    }
    return dp[h-1][w-1]
}
func main() {
    scanner := bufio.NewScanner(os.Stdin)
    var h int64 = 0
    var w int64 = 0
    var i int64 = 0
    var grid []string
    for scanner.Scan() {
        if i > 0 && i > h {
            break
        }
        if i == 0 {
            strs := strings.Split(scanner.Text(), " ")
            h, _ = strconv.ParseInt(strs[0], 10, 64)
            w, _ = strconv.ParseInt(strs[1], 10, 64)
        } else {
            if i == 1 {
                grid = make([]string, h)
            }
            grid[i-1] = scanner.Text()
        }
        i++
    }

    fmt.Println(solve(h,w,grid))
}