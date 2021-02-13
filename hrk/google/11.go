package main
import (
    "fmt"
    "sort"
)


// func min(a ...int) int{
//     v := -1
//     for _,vv := range a {
//         if v == -1 || v > vv {
//             v = vv
//         }
//     }
//     return v
// }

// func solve410(nums []int, m int) int {
//     n := len(nums)
//     if n < m {
//         return -1
//     }
//     dp := make([][]int, n)
//     sumOf := make([]int, n)
//     for i := 0; i < n; i++ {
//         dp[i] = make([]int, m)
//     }

//     curSum := 0
//     for i := 0; i < n; i++ {
//         curSum += nums[i]
//         dp[i][0] = curSum
//         sumOf[i] = curSum
//     }
//     for j := 1; j < m; j++ {
//         for i := 1; i < n; i++ {
//             if j > i {
//                 continue
//             }

//             minV := 0
//             for ii := 0; ii < i; ii++ {
//                 a := 0
//                 if dp[ii][j-1] > sumOf[i] - sumOf[ii] {
//                     a = dp[ii][j-1]
//                 } else {
//                     a = sumOf[i] - sumOf[ii]
//                 }
//                 if minV == 0 || minV > a {
//                     minV = a
//                 }
//             }
//             dp[i][j] = minV
//         }
//     }
//     return dp[n-1][m-1]
// }

// func main() {
//     nums := make([]int, 1000)
//     for i := 0; i < 1000; i++ {
//         nums[i] = 0
//     }
//     m := 50
//     fmt.Println(solve410(nums, m))
// }

type TreeNode struct {
    Val int
    Left *TreeNode
    Right *TreeNode
}

type XNode struct {
    Node *TreeNode
    X int
    Y int
}

type sortXNode []XNode


func (s sortXNode) Len() int{
    return len(s)
}

func (s sortXNode) Swap(i int, j int) {
    s[i], s[j] = s[j], s[i]
}

func (s sortXNode) Less(i int, j int) bool {
    if s[i].X < s[j].X {
        return true
    }
    if s[i].X > s[j].X {
        return false
    }
    if s[i].Y > s[j].Y {
        return true
    }
    if s[i].Y < s[j].Y {
        return false
    }
    if s[i].Node.Val < s[j].Node.Val {
        return true
    }
    return false
}


func solve987(root *TreeNode) [][]int {
    if root == nil {
        return [][]int{}
    }
    queue := []XNode{
        XNode{
            Node: root,
            X: 0,
            Y: 0,
        },
    }
    count := 1
    nodes := []XNode{}
    for {
        if count <= 0 {
            break
        }
        it := queue[0]
        queue = queue[1:count]
        count --
        nodes = append(nodes, it)
        if it.Node.Left != nil {
            queue = append(queue, XNode{
                Node: it.Node.Left,
                X: it.X-1,
                Y: it.Y-1,
            })
            count ++
        }
        if it.Node.Right != nil {
            queue = append(queue, XNode{
                Node: it.Node.Right,
                X: it.X+1,
                Y: it.Y-1,
            })
            count ++
        }
    }

    sort.Sort(sortXNode(nodes))
    rs := [][]int{}
    t := []XNode{}
    for i, node := range nodes {
        if i == 0 || node.X > nodes[i-1].X {
            tt := []int{}
            for _, x := range t {
                tt = append(tt, x.Node.Val)
            }
            if len(tt) > 0 {
                rs = append(rs, tt)
            }
            t = []XNode{node}
        } else {
            t = append(t, node)
        }
    }
    tt := []int{}
    for _, x := range t {
        tt = append(tt, x.Node.Val)
    }
    if len(tt) > 0 {
        rs = append(rs, tt)
    }
    return rs
}

func main() {
    a := &TreeNode{
        Val: 9,
        Left: nil,
        Right: nil,
    }
    b := &TreeNode{
        Val: 15,
        Left: nil,
        Right: nil,
    }
    c := &TreeNode{
        Val: 7,
        Left: nil,
        Right: nil,
    }
    d := &TreeNode{
        Val: 20,
        Left: b,
        Right: c,
    }
    root := &TreeNode{
        Val: 3,
        Left: a,
        Right: d,
    }
    fmt.Println(solve987(root))
}