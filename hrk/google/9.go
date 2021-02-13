package main
import "fmt"

func find_min(nums []int, startInd int) int {
    minV := -1
    ind := -1
    for i := startInd; i < len(nums); i++ {
        if minV == -1 || minV > nums[i] {
            minV = nums[i]
            ind = i
        }
    }
    return ind
}
func nextPermutation(nums []int)  {
    ind := -1
    iind := -1
    for i := 0; i < len(nums); i++ {
        f := -1
        for j := 0; j < i; j++ {
            if nums[i] > nums[j] {
                f = j
            }
        }
        if f != -1 && (f > ind || (f == ind && nums[i] < nums[iind])) {
            ind = f
            iind = i
        }
    }
    i := 0
    if ind != -1 {
        t := nums[iind]
        for i := iind-1; i >= ind; i-- {
            nums[i+1] = nums[i]
        }
        nums[ind] = t
        i = ind+1
    }

    for {
        t := find_min(nums, i)
        x := nums[i]
        nums[i] = nums[t]
        nums[t] = x
        i++
        if i == len(nums) {
            break
        }
    }
}

func main() {
    nums := []int{5,4,7,5,3,2}
    nextPermutation(nums)
    fmt.Println(nums)
}