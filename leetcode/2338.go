package main

import (
	"fmt"
	"math/big"
)

type P struct {
	prime int
	cnt   int
	s     int
}

func min(a ...int) int {
	var k int = 1e9
	for _, x := range a {
		if k > x {
			k = x
		}
	}
	return k
}

func max(a ...int) int {
	var k int = -1e9
	for _, x := range a {
		if k < x {
			k = x
		}
	}
	return k
}

func primeFactors(n int) (pfs []P) {
	// ps := [2000]int{}
	// Get the number of 2s that divide n
	cnt := 0
	s := 1
	for n%2 == 0 {
		cnt++
		s = s * 2
		n = n / 2
	}
	if cnt > 0 {
		pfs = append(pfs, P{
			prime: 2,
			cnt:   cnt,
			s:     s,
		})
	}
	// n must be odd at this point. so we can skip one element
	// (note i = i + 2)
	for i := 3; i*i <= n; i = i + 2 {
		cnt = 0
		s = 1
		// while i divides n, append i and divide n
		for n%i == 0 {
			cnt++
			s = s * i
			n = n / i
		}
		if cnt > 0 {
			pfs = append(pfs, P{
				prime: i,
				cnt:   cnt,
				s:     s,
			})
		}
	}

	// This condition is to handle the case when n is a prime number
	// greater than 2
	if n > 2 {
		pfs = append(pfs, P{
			prime: n,
			cnt:   1,
			s:     n,
		})
	}
	return
}
func modInverse(b int64, m int64) *big.Int {
	bBig := big.NewInt(b)
	mBig := big.NewInt(m)
	return bBig.Exp(bBig, big.NewInt(m-2), mBig)
}
func cnk(n int64, k int64, m int64, modInverses *[10005]int64) int64 {
	// mBig := big.NewInt(m)
	// rs := big.NewInt(1)
	var rs int64 = 1
	var i int64 = 1
	for {
		if i > k {
			break
		}
		// rs.Mul(rs, big.NewInt(i+n-k))
		// rs.Mod(rs, mBig)
		// rs.Mul(rs, modInverse(i, m)) // (rs * (i + n - k)) / i
		// rs.Mod(rs, mBig)
		// rs.Mul(rs, big.NewInt(i+n-k))
		// rs.Div(rs, big.NewInt(i)) // (rs * (i + n - k)) / i
		x := (rs % m * (i + n - k) % m) % m
		rs = (x % m * modInverses[i] % m) % m
		i++
	}
	// rs.Mod(rs, mBig)
	return rs
}
func idealArrays(n int, maxValue int) int {
	var mod int64 = 1e9 + 7
	var rs int64 = 0
	modInverses := [10005]int64{}
	for i := int64(1); i <= int64(n); i++ {
		modInverses[i] = modInverse(i, mod).Int64()
	}
	// fmt.Println("HEHEH")
	ndist := 15
	// dp := make([][]int64, 16)
	dp := [16][10005]int64{}
	m := [10005][]int{}
	k := 0
	for j := 1; j <= maxValue; j++ {
		dp[0][j] = 1
		k = n - 1
		combi := cnk(int64(1+k-1), int64(k), mod, &modInverses)
		if k >= 0 {
			t := ((combi % mod) * (dp[0][j] % mod)) % mod
			rs = (rs%mod + t%mod) % mod
		}
		x := j + j
		for {
			if x > maxValue {
				break
			}
			m[x] = append(m[x], j)
			x = x + j
		}
	}

	for i := 1; i < ndist; i++ {
		k = n - (i + 1)
		combi := cnk(int64(i+1+k-1), int64(k), mod, &modInverses)
		for j := 1; j <= maxValue; j++ {
			dp[i][j] = 0
			for _, k := range m[j] {
				if j%k == 0 {
					dp[i][j] = (dp[i][j]%mod + dp[i-1][k]%mod) % mod
				}
			}
			if k >= 0 {
				t := ((combi % mod) * (dp[i][j] % mod)) % mod
				rs = (rs%mod + t%mod) % mod
			}
		}
		// fmt.Println(dp[i])
	}
	return int(rs)
}

func main() {
	// fmt.Println(idealArrays(2, 5))
	// fmt.Println(idealArrays(5, 3))
	// fmt.Println(idealArrays(2, 6))
	fmt.Println(idealArrays(9999, 10000)) // 2378615
}
