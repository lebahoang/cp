package main

import "fmt"

func nextIndex(maxInd int32, x int32, n int32) int32 {
    if maxInd >= x {
        return maxInd-x
    }
    x = x - maxInd
    // fmt.Println("xxx", x)
    return n - x
}
func solve1(a []int32, rotate []int32) []int32 {
    n := int32(len(a))
    maxInd := int32(-1)
    max := int32(-1)
    for i := int32(0); i < n; i++ {
        if max == -1 || max < a[i] {
            max = a[i]
            maxInd = i
        }
    }
    rs := []int32{}
    m := int32(len(rotate))
    for i := int32(0); i < m; i++ {
        x := rotate[i]%n
        rs = append(rs, nextIndex(maxInd, x, n))
    }
    return rs
}

func main() {
    // a := []int32{1,2,3}
    // rotate := []int32{1,2,3,4}
    a := []int32{1,2,4,3}
    rotate := []int32{1,3}
    fmt.Println(solve1(a, rotate))
}