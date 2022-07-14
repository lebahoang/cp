package main

import "fmt"

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

func idealArrays(n int, maxValue int) int {
	var mod int64 = 1e9 + 7
	primesOfNumber := [10003][]P{}
	for j := 1; j <= maxValue; j++ {
		primesOfNumber[j] = primeFactors(j)
	}
	// dp := [10003]int{}
	// dpn := [10003]int{}
	dp := make([]int64, maxValue+5)
	dpn := make([]int64, maxValue+5)
	for j := 1; j <= maxValue; j++ {
		dp[j] = 1
	}
	for i := 1; i < n; i++ {
		for j := 1; j <= maxValue; j++ {
			l := int64(len(primesOfNumber[j]))
			dpn[j] = 0
			m := 1
			dpn[j] = (dpn[j]%mod + dp[j]%mod) % mod
			for _, p := range primesOfNumber[j] {
				m = m * (p.s / p.prime)
				dpn[j] = (dpn[j]%mod + dpn[j/p.prime]%mod) % mod
			}

			for i := int64(1); i <= l; i++ {
				if l-1-i >= 0 {
					// C(i, len(primesOfNumber))
					//
				}
			}

			if l >= 1 {
				dpn[j] = (dpn[j]%mod - ((l-1)*dpn[m])%mod) % mod
			}
			dp[j] = dpn[j]
		}
	}
	// fmt.Println(dp)
	// fmt.Println(dpn)
	var rs int64 = 0
	for j := 1; j <= maxValue; j++ {
		rs = (rs%mod + dp[j]%mod) % mod
	}
	return int(rs)
}

func main() {
	// fmt.Println(idealArrays(2, 5))
	// fmt.Println(idealArrays(5, 3))
	// fmt.Println(idealArrays(2, 6))
	fmt.Println(idealArrays(20, 100)) // 2378615

}
