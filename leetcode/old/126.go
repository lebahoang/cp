package main

import "fmt"

type I struct {
	prev *I
	s    string
	d    int
}

type II struct {
	s   string
	ind int
}

func min(x ...int) int {
	var rs int = 1e9
	for _, a := range x {
		if rs > a {
			rs = a
		}
	}
	return rs
}
func getPath(e *I) []string {
	rs := []string{}
	t := e
	for {
		rs = append(rs, t.s)
		if t.prev == nil {
			break
		}
		t = t.prev
	}
	rs1 := []string{}
	for i := len(rs) - 1; i >= 0; i-- {
		rs1 = append(rs1, rs[i])
	}
	return rs1
}
func diff(a string, b string) int {
	cnt := 0
	for i := 0; i < len(a); i++ {
		if a[i] != b[i] {
			cnt++
		}
	}
	return cnt
}
func findLadders(b string, e string, wl []string) [][]string {
	f := true
	for _, s := range wl {
		if b == s {
			f = false
			break
		}
	}
	if f {
		wl = append(wl, b)
	}
	ne := map[string][]string{}
	for _, s := range wl {
		ne[s] = []string{}
	}
	for _, s := range wl {
		for _, a := range wl {
			if s == a {
				continue
			}
			if diff(s, a) == 1 {
				ne[s] = append(ne[s], a)
				// ne[a] = append(ne[a], s)
			}
		}
	}

	var minV int = 1e9
	q := []*I{&I{nil, b, 1}}
	dist := map[string]int{b: 1}
	count := map[string]int{b: 1}
	prev := map[string][]*I{}
	for {
		if len(q) == 0 {
			break
		}
		it := q[0]
		// fmt.Println(*it, len(q), minV)

		q = q[1:]
		if minV < 1e9 && (it.d > minV || (it.d == minV && it.s != e)) {
			continue
		}
		if it.s == e {
			minV = min(minV, it.d)
			continue
		}
		for _, s := range ne[it.s] {
			_, ok := dist[s]
			if ok {
				if it.d+1 == dist[s] {
					prev[s] = append(prev[s], it)
					count[s] += count[it.s]
				}
			} else {
				prev[s] = append(prev[s], it)
				dist[s] = it.d + 1
				count[s] += count[it.s]
				q = append(q, &I{it, s, it.d + 1})
			}
		}
	}
	// for k, v := range prev {
	// 	fmt.Println(k, count[k])
	// 	for _, i := range v {
	// 		fmt.Print(*i, "   ")
	// 	}
	// 	fmt.Println()
	// }
	rs := make([][]string, count[e])

	currentID := -1
	q1 := []*II{&II{e, 0}}
	level := []*II{}
	for {
		if len(q1) == 0 {
			break
		}
		ii := q1[0]
		q1 = q1[1:]
		if ii.ind > currentID {
			ind := 0
			for _, n := range level {
				for c := 0; c < count[n.s]; c++ {
					rs[ind] = append(rs[ind], n.s)
					ind++
				}
			}
			currentID = ii.ind
			level = []*II{ii}
		} else {
			level = append(level, ii)
		}
		for _, n := range prev[ii.s] {
			q1 = append(q1, &II{n.s, ii.ind + 1})
		}
	}
	if len(level) > 0 {
		ind := 0
		for _, n := range level {
			for c := 0; c < count[n.s]; c++ {
				rs[ind] = append(rs[ind], n.s)
				ind++
			}
		}
	}

	for _, s := range rs {
		i := 0
		j := len(s) - 1
		for {
			if i >= j {
				break
			}
			str := s[i]
			s[i] = s[j]
			s[j] = str
			i++
			j--
		}
	}

	return rs
}

// func dfs(s string, prev map[string][]*I, l []string) [][]string {

// }

func main() {
	b := "aaaaa"
	e := "ggggg"
	wl := []string{"aaaaa", "caaaa", "cbaaa", "daaaa", "dbaaa", "eaaaa", "ebaaa", "faaaa", "fbaaa", "gaaaa", "gbaaa", "haaaa", "hbaaa", "iaaaa", "ibaaa", "jaaaa", "jbaaa", "kaaaa", "kbaaa", "laaaa", "lbaaa", "maaaa", "mbaaa", "naaaa", "nbaaa", "oaaaa", "obaaa", "paaaa", "pbaaa", "bbaaa", "bbcaa", "bbcba", "bbdaa", "bbdba", "bbeaa", "bbeba", "bbfaa", "bbfba", "bbgaa", "bbgba", "bbhaa", "bbhba", "bbiaa", "bbiba", "bbjaa", "bbjba", "bbkaa", "bbkba", "bblaa", "bblba", "bbmaa", "bbmba", "bbnaa", "bbnba", "bboaa", "bboba", "bbpaa", "bbpba", "bbbba", "abbba", "acbba", "dbbba", "dcbba", "ebbba", "ecbba", "fbbba", "fcbba", "gbbba", "gcbba", "hbbba", "hcbba", "ibbba", "icbba", "jbbba", "jcbba", "kbbba", "kcbba", "lbbba", "lcbba", "mbbba", "mcbba", "nbbba", "ncbba", "obbba", "ocbba", "pbbba", "pcbba", "ccbba", "ccaba", "ccaca", "ccdba", "ccdca", "cceba", "cceca", "ccfba", "ccfca", "ccgba", "ccgca", "cchba", "cchca", "cciba", "ccica", "ccjba", "ccjca", "cckba", "cckca", "cclba", "cclca", "ccmba", "ccmca", "ccnba", "ccnca", "ccoba", "ccoca", "ccpba", "ccpca", "cccca", "accca", "adcca", "bccca", "bdcca", "eccca", "edcca", "fccca", "fdcca", "gccca", "gdcca", "hccca", "hdcca", "iccca", "idcca", "jccca", "jdcca", "kccca", "kdcca", "lccca", "ldcca", "mccca", "mdcca", "nccca", "ndcca", "occca", "odcca", "pccca", "pdcca", "ddcca", "ddaca", "ddada", "ddbca", "ddbda", "ddeca", "ddeda", "ddfca", "ddfda", "ddgca", "ddgda", "ddhca", "ddhda", "ddica", "ddida", "ddjca", "ddjda", "ddkca", "ddkda", "ddlca", "ddlda", "ddmca", "ddmda", "ddnca", "ddnda", "ddoca", "ddoda", "ddpca", "ddpda", "dddda", "addda", "aedda", "bddda", "bedda", "cddda", "cedda", "fddda", "fedda", "gddda", "gedda", "hddda", "hedda", "iddda", "iedda", "jddda", "jedda", "kddda", "kedda", "lddda", "ledda", "mddda", "medda", "nddda", "nedda", "oddda", "oedda", "pddda", "pedda", "eedda", "eeada", "eeaea", "eebda", "eebea", "eecda", "eecea", "eefda", "eefea", "eegda", "eegea", "eehda", "eehea", "eeida", "eeiea", "eejda", "eejea", "eekda", "eekea", "eelda", "eelea", "eemda", "eemea", "eenda", "eenea", "eeoda", "eeoea", "eepda", "eepea", "eeeea", "ggggg", "agggg", "ahggg", "bgggg", "bhggg", "cgggg", "chggg", "dgggg", "dhggg", "egggg", "ehggg", "fgggg", "fhggg", "igggg", "ihggg", "jgggg", "jhggg", "kgggg", "khggg", "lgggg", "lhggg", "mgggg", "mhggg", "ngggg", "nhggg", "ogggg", "ohggg", "pgggg", "phggg", "hhggg", "hhagg", "hhahg", "hhbgg", "hhbhg", "hhcgg", "hhchg", "hhdgg", "hhdhg", "hhegg", "hhehg", "hhfgg", "hhfhg", "hhigg", "hhihg", "hhjgg", "hhjhg", "hhkgg", "hhkhg", "hhlgg", "hhlhg", "hhmgg", "hhmhg", "hhngg", "hhnhg", "hhogg", "hhohg", "hhpgg", "hhphg", "hhhhg", "ahhhg", "aihhg", "bhhhg", "bihhg", "chhhg", "cihhg", "dhhhg", "dihhg", "ehhhg", "eihhg", "fhhhg", "fihhg", "ghhhg", "gihhg", "jhhhg", "jihhg", "khhhg", "kihhg", "lhhhg", "lihhg", "mhhhg", "mihhg", "nhhhg", "nihhg", "ohhhg", "oihhg", "phhhg", "pihhg", "iihhg", "iiahg", "iiaig", "iibhg", "iibig", "iichg", "iicig", "iidhg", "iidig", "iiehg", "iieig", "iifhg", "iifig", "iighg", "iigig", "iijhg", "iijig", "iikhg", "iikig", "iilhg", "iilig", "iimhg", "iimig", "iinhg", "iinig", "iiohg", "iioig", "iiphg", "iipig", "iiiig", "aiiig", "ajiig", "biiig", "bjiig", "ciiig", "cjiig", "diiig", "djiig", "eiiig", "ejiig", "fiiig", "fjiig", "giiig", "gjiig", "hiiig", "hjiig", "kiiig", "kjiig", "liiig", "ljiig", "miiig", "mjiig", "niiig", "njiig", "oiiig", "ojiig", "piiig", "pjiig", "jjiig", "jjaig", "jjajg", "jjbig", "jjbjg", "jjcig", "jjcjg", "jjdig", "jjdjg", "jjeig", "jjejg", "jjfig", "jjfjg", "jjgig", "jjgjg", "jjhig", "jjhjg", "jjkig", "jjkjg", "jjlig", "jjljg", "jjmig", "jjmjg", "jjnig", "jjnjg", "jjoig", "jjojg", "jjpig", "jjpjg", "jjjjg", "ajjjg", "akjjg", "bjjjg", "bkjjg", "cjjjg", "ckjjg", "djjjg", "dkjjg", "ejjjg", "ekjjg", "fjjjg", "fkjjg", "gjjjg", "gkjjg", "hjjjg", "hkjjg", "ijjjg", "ikjjg", "ljjjg", "lkjjg", "mjjjg", "mkjjg", "njjjg", "nkjjg", "ojjjg", "okjjg", "pjjjg", "pkjjg", "kkjjg", "kkajg", "kkakg", "kkbjg", "kkbkg", "kkcjg", "kkckg", "kkdjg", "kkdkg", "kkejg", "kkekg", "kkfjg", "kkfkg", "kkgjg", "kkgkg", "kkhjg", "kkhkg", "kkijg", "kkikg", "kkljg", "kklkg", "kkmjg", "kkmkg", "kknjg", "kknkg", "kkojg", "kkokg", "kkpjg", "kkpkg", "kkkkg", "ggggx", "gggxx", "ggxxx", "gxxxx", "xxxxx", "xxxxy", "xxxyy", "xxyyy", "xyyyy", "yyyyy", "yyyyw", "yyyww", "yywww", "ywwww", "wwwww", "wwvww", "wvvww", "vvvww", "vvvwz", "avvwz", "aavwz", "aaawz", "aaaaz"}
	// b := "red"
	// e := "tax"
	// wl := []string{"ted", "tex", "red", "tax", "tad", "den", "rex", "pee"}

	fmt.Println(findLadders(b, e, wl))
}
