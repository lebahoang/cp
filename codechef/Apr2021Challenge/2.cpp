#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <utility>

// g++ -std=c++14 -stdlib=libc++ -O2 -o s.out 2.cpp && ./s.out < x.txt
using namespace std;
using ll = long long;

bool isBigger(string a, string b) {
    if (a.length() > b.length()) return true;
    else if (a.length() < b.length()) return false;
    return a >= b;
}
string solve(string s) {
    if (s == "0") return "1";
    int n = s.length();
    vector<int> ones(n, 0);
    vector<int> zeros(n, 0);
    for (int i = 0; i < n; i++) {
        int t = 0;
        if (s[i] == '1') {
            t = 1;
        }
        if (i > 0) {
            t += ones[i-1];
        }
        ones[i] = t;
    }
    for (int i = n-1; i >= 0; i--) {
        int t = 0;
        if (s[i] == '0') {
            t = 1;
        }
        if (i < n-1) {
            t += zeros[i+1];
        }
        zeros[i] = t;
    }
    string rs = "";
    if (ones[n-1] == n) rs = "0";
    for (int i = 0; i < n-1; i++) {
        if (s[i] == '1') {
            string t = "";
            t.append(ones[i], '1');
            t.append(zeros[i+1]+1, '0');
            if (rs == "" || isBigger(rs, t)) rs = t;
        }
    }
    return rs;
}

int main() {
    int t;
    cin >> t;
    for (int cs = 0; cs < t; cs++) {
        string s;
        cin >> s;
        printf("%s\n", solve(s).c_str());
    }
    return 0;
}
