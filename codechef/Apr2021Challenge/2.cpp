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

// g++ -std=c++14 -O2 -o s.out 2.cpp && ./s.out < x.txt
using namespace std;
using ll = long long;

bool isBigger(string a, string b) {
    if (a.length() > b.length()) return true;
    else if (a.length() < b.length()) return false;
    return a >= b;
}
string bin(int k) {
    if (k == 0) return "0";
    string x = "";
    while (k > 0) {
        x += to_string(k%2);
        k = (k-(k%2))/2;
    }
    reverse(x.begin(), x.end());
    return x;
}
bool isSubSeq(string x, string s) {
    int n = s.length();
    int m = x.length();
    if (m > n) return false;
    vector<vector<bool>> dp(n, vector<bool>(m, false));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s[i] == x[j]) {
                if (j-1 < 0 || (i-1 >= 0 && j-1 >= 0 && dp[i-1][j-1])) {
                   dp[i][j] = true; 
                }
            } else {
                if (i-1 >= 0 && dp[i-1][j]) dp[i][j] = true;
            }
        }
    }
    return dp[n-1][m-1];
}
pair<string, int> bf(string s) {
    string rs = "";
    int prev = -1;
    for (int i = 0; i <= 3000; i++) {
        string x = bin(i);
        if (!isSubSeq(x, s)) {
            if (rs == "" || isBigger(rs, x)) {
                rs = x;
                prev = i-1;
            }
        }
    }
    return {rs, prev};
}

string solve(string s) {
    if (s == "0") return "1";
    int n = s.length();
    vector<int> prefix_ones(n, 0);
    vector<int> prefix_zeros(n, 0);
    vector<int> zeros(n, 0);
    for (int i = 0; i < n; i++) {
        int t = 0;
        if (s[i] == '1') {
            t = 1;
        }
        if (i > 0) {
            t += prefix_ones[i-1];
        }
        prefix_ones[i] = t;
        int tt = 0;
        if (s[i] == '0') {
            tt = 1;
        }
        if (i > 0) {
            tt += prefix_zeros[i-1];
        }
        prefix_zeros[i] = tt;
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
    if (prefix_ones[n-1] == n) rs = "0";
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            string t = "1";
            if (prefix_ones[i]-1 > 0 && prefix_ones[i]-1 < prefix_zeros[i]) {
                t.append(prefix_ones[i]-1, '1');
            } else {
                t.append(prefix_zeros[i], '0');
            }
            if (i+1 < n) {
                t.append(zeros[i+1]+1, '0');
            } else {
                t.append(1, '0');
            }
            if (rs == "" || isBigger(rs, t)) rs = t;
        }
    }
    return rs;
}

// string addOne(string x) {
//     char add = '1';
//     int n = x.length();
//     vector<char> rs(n+1, '\0');
//     for (int i = n-1; i >= 0; i--) {
//         if (x[i] == '0' && add == '1') {
//             rs[i+1]
//         }
//     }
// }

string solve2(string s) {
    int n = s.length();
    string t = "";
    char cur = '\0';
    for (int i = 0; i < n; i++) {
        if (cur == '\0' || cur != s[i]) {
            if (cur != '\0') t.append(1, cur);
            cur = s[i];
        }
    }
    t.append(1, cur);
    string k = "";
    for (int i = n-t.length(); i < n; i++) {
        if (i == n-t.length() && s[i] == '0') continue;
        k.append(1, s[i]);
    }
    return t;
}

int main() {
    int t;
    cin >> t;
    for (int cs = 0; cs < t; cs++) {
        string s;
        cin >> s;
        auto t = bf(s);
        // printf("prev %s, bf %s, solve %s\n", bin(t.second).c_str(), t.first.c_str(), solve(s).c_str());
        printf("%s\n", t.first.c_str());
    }
    return 0;
}
