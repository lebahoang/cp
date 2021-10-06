package main

func pow10(n int) int {
	if n == 0 {
		return 1
	}
	rs := 1
	for i := 1; i <= n; i++ {
		rs *= 10
	}
	return rs
}
func Numerals(num int) string {
	units := map[int]string{
		1: "I",
		2: "II",
		3: "III",
		4: "IV",
		5: "V",
		6: "VI",
		7: "VII",
		8: "VIII",
		9: "IX",
	}
	tens := map[int]string{
		10: "X",
		20: "XX",
		30: "XXX",
		40: "XL",
		50: "L",
		60: "LX",
		70: "LXX",
		80: "LXXX",
		90: "XC",
	}
	hundreds := map[int]string{
		100: "C",
		200: "CC",
		300: "CCC",
		400: "CD",
		500: "D",
		600: "DC",
		700: "DCC",
		800: "DCCC",
		900: "CM",
	}
	thousands := map[int]string{
		1000: "M",
		2000: "MM",
		3000: "MMM",
	}
	rs := ""
	arr := []map[int]string{units, tens, hundreds, thousands}
	cnt := 0
	for {
		if num == 0 {
			break
		}
		x := (num % 10) * pow10(cnt)
		if x > 0 {
			rs += arr[cnt][x]
		}
		cnt++
		num = (num - x) / 10
	}

	return rs
}
func main() {

}
