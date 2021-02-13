package main
import (
    "fmt"
)

func subarraySum(nums []int, k int) int {
    total := 0
    m := map[int]int{}
    c := 0
    for i := 0; i < len(nums); i++ {
        c += nums[i]
        if c == k {
            fmt.Println(c)
            total ++
        }
        count, ok := m[c-k]
        if ok {
            total += count
        }
        _, ok = m[c]
        if !ok {
            m[c] = 1
        } else {
            m[c] += 1
        }
    }
    return total
}

func max(a ...int) int {
    v := 0
    for i := 0; i < len(a); i++ {
        if v < a[i] {
            v = a[i]
        }
    }
    return v
}

func do(bl int, br int, a []int, i int, j int, dp [][]int) int{
    if dp[i][j] != 0 {
        return dp[i][j]
    }
    for k := i; k <= j; k++ {
        x := 0
        if k > i {
            x = do(bl, a[k], a, i, k-1, dp)
        }
        y := 0
        if k < j {
            y = do(a[k], br, a, k+1, j, dp)
        }
        dp[i][j] = max(dp[i][j], x+y+a[k]*bl*br)
    }
    return dp[i][j]
}

func maxCoins(a []int) int {
    n := len(a)
    dp := make([][]int, n)
    for i := 0; i < n; i++ {
        dp[i] = make([]int, n)
    }
    rs := do(1, 1, a, 0, n-1, dp)
    // for i := 0; i < n; i++ {
    //     for j := 0; j < n; j++ {
    //         fmt.Println(i,j,dp[i][j])
    //     }
    // }     
    return rs
}

func main() {
    // nums := []int{1,1,1}
    // k := 2
    // fmt.Println(subarraySum(nums, k))
    // nums := []int{3,1,5,8}
    // nums := make([]int, 500)
    // for i := 0; i < 500; i++ {
    //     nums[i] = 3
    // }
    // nums := []int{1,5,8,2,2}
    // fmt.Println(maxCoins(nums))
}