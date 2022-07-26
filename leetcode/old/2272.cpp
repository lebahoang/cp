#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#include <string>
#include <set>
#include <map>
#include <unordered_map>
#include <vector>
#include <utility>

// g++ -std=c++14 -Wshadow -Wall -o s.out -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined 2272.cpp && ./s.out
using namespace std;
int ind(char c) {
    return c-'a';
}
int solveArr(vector<int>& a) {
    int rs = -1e9;
    int n = (int)a.size();
    vector<int> pref(n, 0);
    vector<int> dp(n, 0);
    int last = -1;
    for(int i = 0; i < n; i++) {
        if (i == 0) pref[i] = a[i];
        else pref[i] = pref[i-1] + a[i];
        if (last >= 0) dp[i] = max(a[i], dp[last] + pref[i] - pref[last]);
        else dp[i] = a[i];
        rs = max(rs, dp[i]);
        if (a[i] >= 0) {
            last = i;
        }
    }
    return rs;
}
int solve(string& s) {
    int n = (int)s.length();
    vector<bool> has(30, false);
    for (int i = 0; i < n; i++) {
        int t = ind(s[i]);
        has[t] = true;
    }
    int rs = 0;
    return rs;
}

int main() {
    // string s = "abcedfghjk";
    string s = "baaabbbaaaaaab";
    // string s = "icexiahccknibwuwgi";
    printf("dsadsad %d %d\n", ind('i'), ind('a'));
    printf("%d\n", solve(s));
    return 0;
}