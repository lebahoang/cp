package main

import "fmt"

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

func primeFactors(n int) (pfs []int) {
	ps := [2000]int{}
	// Get the number of 2s that divide n
	for n%2 == 0 {
		if ps[2] == 0 {
			ps[2] = 1
			pfs = append(pfs, 2)
		}
		n = n / 2
	}

	// n must be odd at this point. so we can skip one element
	// (note i = i + 2)
	for i := 3; i*i <= n; i = i + 2 {
		// while i divides n, append i and divide n
		for n%i == 0 {
			if ps[i] == 0 {
				ps[i] = 1
				pfs = append(pfs, i)
			}
			n = n / i
		}
	}

	// This condition is to handle the case when n is a prime number
	// greater than 2
	if n > 2 {
		pfs = append(pfs, n)
	}
	return
}

func idealArrays(n int, maxValue int) int {
	var mod int64 = 1e9 + 7
	primesOfNumber := [10003][]int{}
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
			dpn[j] = 0
			for _, p := range primesOfNumber[j] {
				dpn[j] = (dpn[j]%mod + dpn[j/p]%mod) % mod
				if len(primesOfNumber[j]) > 1 && dpn[j/p] > 1 {
					dpn[j] -= 1
				}
			}
			dpn[j] = (dpn[j]%mod + dp[j]%mod) % mod
			if len(primesOfNumber[j]) > 1 {
				dpn[j] = (dpn[j]%mod + 1%mod) % mod
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
	fmt.Println(idealArrays(1000, 1000))
}
