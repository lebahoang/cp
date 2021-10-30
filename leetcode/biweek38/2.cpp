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
// int count1(string s, string t, int i, int j) {
//     int rs = 0;
//     int x = i-1;
//     int y = j-1;
//     while (true) {
//         if (x < 0 || y < 0) break;
//         if (s[x] != t[y]) break;
//         rs++;
//         x--;
//         y--;
//     }
//     return rs;
// }
// int count2(string s, string t, int i, int j) {
//     int n = s.length();
//     int m = t.length();
//     int rs = 0;
//     int x = i+1;
//     int y = j+1;
//     while (true) {
//         if (x == n || y == m) break;
//         if (s[x] != t[y]) break;
//         rs++;
//         x++;
//         y++;
//     }
//     return rs;
// }
// int solve(string s, string t) {
//     int rs = 0;
//     int n = s.length();
//     int m = t.length();
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < m; j++) {
//             if (s[i] != t[j]) {
//                 int x = count1(s, t, i, j);
//                 int y = count2(s, t, i, j);
//                 rs += 1 + x + y + x*y;
//             }
//         }
//     }
//     return rs;
// }
void count(vector<string>& w, vector<vector<int>>& mem) {
    for (int i = 0; i < (int)w.size(); i++) {
        for (int j = 0; j < w[i].length(); j++) {
            mem[j][(int)(w[i][j]-'a')]++;
        }
    }
}
int solve(vector<string>& w, string target) {
    const int mod = 1e9 + 7;
    vector<vector<int>> mem(1005, vector<int>(30, 0));
    count(w, mem);
    long long dp[1005][1005];
    memset(dp, 0, sizeof(dp));
    int tl = target.length();
    int m = -1;
    for (string x: w) {
        m = max(m, (int)x.length());
    }
    // for (int j = 0; j < m; j++) {
    //     for (int k = 0; k < 30; k++) {
    //         printf("j %d, char %c, count %d\n", j, (char)('a'+k), mem[j][k]);
    //     }
    // }
    for (int i = 0; i < tl; i++) {
        for (int j = 0; j < m; j++) {
            if (j == 0) {
                if (i == 0)
                    dp[i][j] = mem[j][(int)(target[i]-'a')]%mod;
            } else {
                if (i == 0) {
                    dp[i][j] = (dp[i][j-1]%mod + mem[j][(int)(target[i]-'a')]%mod)%mod;
                } else {
                    dp[i][j] = (dp[i][j-1]%mod + (dp[i-1][j-1]%mod * mem[j][(int)(target[i]-'a')]%mod)%mod)%mod;
                }
            }
        }
    }
    return dp[tl-1][m-1];
}
int main() {
    vector<string> w = {
        "acca","bbbb","caca"
    };
    string t= "aba";
    // vector<string> w = {
    //     "ab"
    // };
    // string t= "ab";
    printf("%d\n", solve(w, t));
    return 0;
}