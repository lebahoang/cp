package main

import "os"
import "fmt"
import "strconv"
import "bufio"
import "strings"
import "math"

// func sum(m []int) int {
//     s := 0
//     for _, c := range m {
//         s += c
//     }
//     return s
// }
// func solve(m []int) int {
//     if sum(m)%len(m) != 0 {
//         return -1
//     }
//     return 0
// }
type Key struct {
    H int64
    R int64
    G int64
}

type Key1 struct {
    H int64
    R int64
}

// var dp = map[Key]int64{}
// var dp = map[Key1]int64{}
var dp = [2e5+5]int64{}
var temp = [2e5+5]int64{}

func max(a, b int64) int64 {
    if a > b {
        return a
    }
    return b
}

func getH(c int64, a int64) int64 {
    var i int64 = 1
    t := 2*a-1
    for {
        if i*(i+t) > c {
            i--
            break
        } else if i*(i+t) == c {
            break
        }
        i++
    }
    // fmt.Println("i c", i, c)
    return i
}

func getBlock(a int64, d int64, n int64) int64 {
    return a + (n-1)*d
}

func getTotal(a int64, d int64, n int64) int64 {
    return n*(2*a + (n-1)*d)/2
}   


func do(h int64, r int64, g int64, rTotal int64, gTotal int64, maxH int64, dp map[Key]int64, mod int64) int64 {
    if h > maxH {
        return 0
    }
    k := Key{H: h, R:r, G:g}
    if v,ok := dp[k]; ok {
        return v
    }
    var rs int64 = 0
    if getBlock(1,1,h)+r <= rTotal {
        rs = (rs%mod + do(h+1,getBlock(1,1,h)+r,g,rTotal,gTotal,maxH,dp,mod) % mod ) % mod
    }
    if getBlock(1,1,h)+g <= gTotal {
        rs = (rs%mod + do(h+1,r,getBlock(1,1,h)+g,rTotal,gTotal,maxH,dp,mod) % mod ) % mod
    }
    dp[k] = rs
    return rs
}


// func do1(h int64, r int64, g int64, rTotal int64, gTotal int64, maxH int64, mod int64) int64 {
//     if h > maxH {
//         return 0
//     }
//     // k := Key1{H: h, R:r}
//     // if v,ok := dp[k]; ok {
//     //  return v
//     // }
//     if dp[h][r] > 0 {
//         return dp[h][r]
//     }
//     var rs int64 = 0
//     if getBlock(1,1,h)+r <= rTotal {
//         rs = (rs%mod + do1(h+1,getBlock(1,1,h)+r,g,rTotal,gTotal,maxH,mod) % mod ) % mod
//     }
//     if getBlock(1,1,h)+g <= gTotal {
//         rs = (rs%mod + do1(h+1,r,getBlock(1,1,h)+g,rTotal,gTotal,maxH,mod) % mod ) % mod
//     }
//     dp[h][r] = rs
//     return rs
// }


func solve(r int64, g int64) int64 {
    var mod int64 = 1e9 + 7
    hr := int64(math.Floor(math.Sqrt(float64(2*r))))
    hg := int64(math.Floor(math.Sqrt(float64(2*g))))
    var h int64 = 0

    tg := getH(2*g, hr+1)
    tr := getH(2*r, hg+1)
    if hr + tg > hg + tr {
        h = hr + tg
    } else {
        h = hg + tr
    }
    t := getBlock(1,1,h)
    // k1 := Key{H:h, R: r-t, G: g}
    // k2 := Key{H:h, R: r, G: g-t}
    // k1 := Key1{H:h, R: r-t}
    // k2 := Key1{H:h, R: r}
    if g-t >= 0 {
        temp[r] = 1
    }
    if r-t >= 0 {
        temp[r-t] = 1
    }
    // tt := r+g-getTotal(1,1,h)
    // var rs int64 = 0
    // for i := int64(0); i <= tt; i++ {
    //  rs = (rs%mod + do1(1,i,tt-i,r,g,h,mod)%mod) % mod
    // }
    // fmt.Println(dp)
    for i := h-1; i >= 1; i-- {
        for j := int64(0); j <= r; j++ {
            if j+i <= r {
                dp[j] = (dp[j]%mod + temp[j+i]%mod) % mod
            }
            gleft := g-(getTotal(i,1,h-i+1)-(r-j))
            if gleft+i <= g {
                dp[j] = (dp[j]%mod + temp[j]%mod) % mod
            }
        }
        for j := int64(0); j <= 2e5; j++ {
            temp[j] = dp[j]
            dp[j] = 0
        }
    }
    tt := r+g-getTotal(1,1,h)
    var rs int64 = 0
    for i := int64(0); i <= tt; i++ {
        // fmt.Println(i, temp[i])
        rs = (rs%mod + temp[i]%mod) % mod
    }
    return rs
}

func main() {
    scanner := bufio.NewScanner(os.Stdin)
    i := 0
    var r int64 = 0
    var g int64 = 0
    for scanner.Scan() {
        if i == 1 {
            break
        }
        strs := strings.Split(scanner.Text(), " ")
        r, _ = strconv.ParseInt(strs[0], 10, 64)
        g, _ = strconv.ParseInt(strs[1], 10, 64)
        i++
    }
    fmt.Println(solve(r,g))
}