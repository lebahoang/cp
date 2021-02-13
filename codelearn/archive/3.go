package main

import (
	"fmt"
	"strconv"
)

func getC() [15][15]int64 {
    fac := [15]int64{}
    fac[0] = int64(1)
    for i := 1; i <= 10; i++ {
        fac[i] = fac[i-1]*int64(i)
    }
    c := [15][15]int64{}
    for i := 1; i <= 10; i++ {
        for j := 0; j <= i; j++ {
            c[i][j] = fac[i]/(fac[j]*fac[i-j])
            c[i][j] = c[i][j] * fac[j]
        }
    }
    return c
}
func isUnique(a []int, s int, e int) bool {
    count := 0
    m := [15]int{}
    for i := s; i <= e; i++{
        m[a[i]]++
        if m[a[i]] == 1 {
            count++
        }
    }
    if count == e-s+1 {
        return true
    }
    return false
}

func getGreaterOrEqual(s string, c [15][15]int64) int64 {
    if len(s) > 10 {
        return 0
    }
    a := make([]int, len(s))
    for i := 0; i < len(s); i++ {
        a[i] = int(s[i]-'0')
    }
    rs := int64(0)
    if isUnique(a, 0, len(a)-1) {
        // fmt.Println(a[0:len(a)])
        rs++
    }
    for i := len(a)-1; i >= 0; i-- {
        for j := a[i]+1; j < 10; j++ {
            t := a[i]
            a[i] = j
            if isUnique(a, 0, i) {
                // fmt.Println(a[0:i+1], c[10-(i+1)][len(a)-(i+1)])
                rs += c[10-(i+1)][len(a)-(i+1)]
            }
            a[i] = t
        }
    }
    return rs
}

func getLessOrEqual(s string, c [15][15]int64) int64 {
    if len(s) > 10 {
        return 0
    }
    a := make([]int, len(s))
    for i := 0; i < len(s); i++ {
        a[i] = int(s[i]-'0')
    }
    rs := int64(0)
    if isUnique(a, 0, len(a)-1) {
        // fmt.Println(a[0:len(a)])
        rs++
    }
    for i := len(a)-1; i >= 0; i-- {
        for j := a[i]-1; j >= 0; j-- {
            if i == 0 && j == 0 {
                continue
            }
            t := a[i]
            a[i] = j
            if isUnique(a, 0, i) {
                // fmt.Println(a[0:i+1], c[10-(i+1)][len(a)-(i+1)])
                rs += c[10-(i+1)][len(a)-(i+1)]
            }
            a[i] = t
        }
    }
    return rs
}


func differentiateNumber(L int64, R int64) int64 {
    c := getC()
    s := strconv.FormatInt(L, 10)
    d := strconv.FormatInt(R, 10)
    if len(s) == len(d) {
        x := strconv.FormatInt(L-1, 10)
        if x == "0" || len(x) < len(s) {
            return getLessOrEqual(d, c)
        }
        return getLessOrEqual(d, c) - getLessOrEqual(x, c)
    }
    var rs int64 = getGreaterOrEqual(s, c)
    for i := len(s)+1; i < len(d); i++ {
        if i > 10 {
            continue
        }
        // fmt.Println(i, c[10][i] - c[9][i-1])
        rs += c[10][i] - c[9][i-1]
    }
    rs += getLessOrEqual(d, c)
    return rs
}

func main() {
    // c := getC()
    // fmt.Println(getLessOrEqual("0", c))
    // fmt.Println(getLessOrEqual("999", c))
    // fmt.Println("------------")
    // fmt.Println(getGreaterOrEqual("97", c))
    // fmt.Println(differentiateNumber(1, 5))
    fmt.Println(differentiateNumber(0, 10))
}
