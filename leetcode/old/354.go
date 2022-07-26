package main
import (
	"sort"
	"fmt"
    // "strconv"
    "strings"
)

type sortXNode [][]int
func (s sortXNode) Len() int{
    return len(s)
}

func (s sortXNode) Swap(i int, j int) {
    s[i], s[j] = s[j], s[i]
}

func (s sortXNode) Less(i int, j int) bool {
	if s[i][0] <= s[j][0] {
		return true
	}
	return false
}
func maxEnvelopes(envelopes [][]int) int {
    e := envelopes
    sort.Sort(sortXNode(e))
    n := len(e)
    if n == 0 {
    	return 0
    }
    mv := 1
    dp := make([]int, len(e))
    dp[0] = 1
    for i := 1; i < n; i++ {
        dp[i] = 1
        for j := 0; j < i; j++ {
            if e[i][0] > e[j][0] && e[i][1] > e[j][1] {
                if dp[j]+1 > dp[i] {
                    dp[i] = dp[j]+1
                }
            }
        }
        if mv < dp[i] {
            mv = dp[i]
        }
    }
    return mv
}

func min(a ...int) int{
    v := 1000000
    for _,vv := range a {
        if v > vv {
            v = vv
        }
    }
    return v
}

// func do(i int, j int, s1 []string, s2 []string, dp map[string]string) string{
//     key := strconv.Itoa(i) + "," + strconv.Itoa(j)
//     if v,ok := dp[key]; ok {
//         return v
//     }
//     if i < 0 {
//         return strings.Join(s2[:j+1], "")
//     }
//     if j < 0 {
//         return strings.Join(s1[:i+1], "")
//     }
//     if s1[i] == s2[j] {
//         dp[key] = do(i-1, j-1, s1, s2, dp) + s1[i]
//         return dp[key]
//     }
//     x := do(i-1,j, s1, s2, dp) + s1[i]
//     y := do(i, j-1, s1, s2, dp) + s2[j]
//     // z := do(i-1, j-1, s1, s2, dp) + s1[i] + s2[j]
//     // v := min(len(x), len(y), len(z))
//     // if v == len(x) {
//     //     dp[key] = x
//     // } else if v == len(y) {
//     //     dp[key] = y
//     // } else {
//     //     dp[key] = z
//     // }
//     // return dp[key]

//     if len(x) < len(y) {
//         dp[key] = x
//     } else {
//         dp[key] = y
//     }
//     return dp[key]
// }

func do(i int, j int, s1 []string, s2 []string, dp [][]string) string{
    if i < 0 {
        return strings.Join(s2[:j+1], "")
    }
    if j < 0 {
        return strings.Join(s1[:i+1], "")
    }
    if dp[i][j] != "" {
        return dp[i][j]
    }
    if s1[i] == s2[j] {
        dp[i][j] = do(i-1, j-1, s1, s2, dp) + s1[i]
        return dp[i][j]
    }
    x := do(i-1,j, s1, s2, dp) + s1[i]
    y := do(i, j-1, s1, s2, dp) + s2[j]
    if len(x) < len(y) {
        dp[i][j] = x
    } else {
        dp[i][j] = y
    }
    return dp[i][j]
}
func three(s1 string, s2 string) string{
    n := len(s1)
    m := len(s2)
    dp := make([][]string, n)
    for i := 0; i < n; i++ {
        dp[i] = make([]string, m)
        for j := 0; j < m; j++ {
            dp[i][j] = ""
        }
    }
    as1 := make([]string, n)
    as2 := make([]string, m)
    for i := 0; i < n; i++ {
        as1[i] = string(s1[i])
    }
    for i := 0; i < m; i++ {
        as2[i] = string(s2[i])
    }
    rs := do(n-1, m-1, as1, as2, dp)
    fmt.Println(len(rs))
    fmt.Println(len(dp))
    return rs
}

func main() {
	// envelopes := [][]int{}
	// fmt.Println(maxEnvelopes(envelopes))
    // s1 := "abac"
    // s2 := "cab"
    // s1 := "atdznrqfwlfbcqkezrltzyeqvqemikzgghxkzenhtapwrmrovwtpzzsyiwongllqmvptwammerobtgmkpowndejvbuwbporfyroknrjoekdgqqlgzxiisweeegxajqlradgcciavbpgqjzwtdetmtallzyukdztoxysggrqkliixnagwzmassthjecvfzmyonglocmvjnxkcwqqvgrzpsswnigjthtkuawirecfuzrbifgwolpnhcapzxwmfhvpfmqapdxgmddsdlhteugqoyepbztspgojbrmpjmwmhnldunskpvwprzrudbmtwdvgyghgprqcdgqjjbyfsujnnssfqvjhnvcotynidziswpzhkdszbblustoxwtlhkowpatbypvkmajumsxqqunlxxvfezayrolwezfzfyzmmneepwshpemynwzyunsxgjflnqmfghsvwpknqhclhrlmnrljwabwpxomwhuhffpfinhnairblcayygghzqmotwrywqayvvgohmujneqlzurxcpnwdipldofyvfdurbsoxdurlofkqnrjomszjimrxbqzyazakkizojwkuzcacnbdifesoiesmkbyffcxhqgqyhwyubtsrqarqagogrnaxuzyggknksrfdrmnoxrctntngdxxechxrsbyhtlbmzgmcqopyixdomhnmvnsafphpkdgndcscbwyhueytaeodlhlzczmpqqmnilliydwtxtpedbncvsqauopbvygqdtcwehffagxmyoalogetacehnbfxlqhklvxfzmrjqofaesvuzfczeuqegwpcmahhpzodsmpvrvkzxxtsdsxwixiraphjlqawxinlwfspdlscdswtgjpoiixbvmpzilxrnpdvigpccnngxmlzoentslzyjjpkxemyiemoluhqifyonbnizcjrlmuylezdkkztcphlmwhnkdguhelqzjgvjtrzofmtpuhifoqnokonhqtzxmimp"
    // s2 := "xjtuwbmvsdeogmnzorndhmjoqnqjnhmfueifqwleggctttilmfokpgotfykyzdhfafiervrsyuiseumzmymtvsdsowmovagekhevyqhifwevpepgmyhnagjtsciaecswebcuvxoavfgejqrxuvnhvkmolclecqsnsrjmxyokbkesaugbydfsupuqanetgunlqmundxvduqmzidatemaqmzzzfjpgmhyoktbdgpgbmjkhmfjtsxjqbfspedhzrxavhngtnuykpapwluameeqlutkyzyeffmqdsjyklmrxtioawcrvmsthbebdqqrpphncthosljfaeidboyekxezqtzlizqcvvxehrcskstshupglzgmbretpyehtavxegmbtznhpbczdjlzibnouxlxkeiedzoohoxhnhzqqaxdwetyudhyqvdhrggrszqeqkqqnunxqyyagyoptfkolieayokryidtctemtesuhbzczzvhlbbhnufjjocporuzuevofbuevuxhgexmckifntngaohfwqdakyobcooubdvypxjjxeugzdmapyamuwqtnqspsznyszhwqdqjxsmhdlkwkvlkdbjngvdmhvbllqqlcemkqxxdlldcfthjdqkyjrrjqqqpnmmelrwhtyugieuppqqtwychtpjmloxsckhzyitomjzypisxzztdwxhddvtvpleqdwamfnhhkszsfgfcdvakyqmmusdvihobdktesudmgmuaoovskvcapucntotdqxkrovzrtrrfvoczkfexwxujizcfiqflpbuuoyfuoovypstrtrxjuuecpjimbutnvqtiqvesaxrvzyxcwslttrgknbdcvvtkfqfzwudspeposxrfkkeqmdvlpazzjnywxjyaquirqpinaennweuobqvxnomuejansapnsrqivcateqngychblywxtdwntancarldwnloqyywrxrganyehkglbdeyshpodpmdchbcc"
    // fmt.Println(three(s1, s2))
}
