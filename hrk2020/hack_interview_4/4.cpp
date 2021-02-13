#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <cstring>
#include <utility>

using namespace std;
using ll = long long;
const int mod = 1e9 + 7;
const int NMAX = 104;

// dp[0-9][n][k] is number of numbers have length n, exactly k non-zero, starts with i in [0-9]
ll dp[11][NMAX][NMAX];

ll bruteForce(string l, string r, int k) {
    int n = l.length();
    int m = r.length();
    int a = 0;
    int b = 0;
    for (int i = 0; i < n; i++) {
        a = a*10 + (l[i]-'0');
    }
    for (int i = 0; i < m; i++) {
        b = b*10 + (r[i]-'0');
    }
    ll rs = 0;
    for (int i = a+1; i <= b; i++) {
        int c = 0;
        int t = i;
        while (t > 0) {
            int x = t%10;
            if (x > 0) c++;
            t = (t-x)/10;
        }
        if (c == k) rs++;
    }
    // printf("dsadasdasd %lld\n", rs);
    return rs;
}

ll calculateOnce(string l, string r, int k, int n, int m) {
    ll rs = 0;
    int i = 0;
    int kk = k;
    int nn = n;
    while (i < m) {
        for (int p = 0; p < (l[i]-'0'); p++) {
            if (i == 0 && p == 0) continue;
            rs = (rs%mod + dp[p][nn][kk]%mod)%mod;
        }
        i++;
        if (i-1 >= 0 && l[i-1] > '0') {
            kk--;
        }
        if (kk < 0) break;
        nn--;
    }
    int c = 0;
    for (int i = 0; i < m; i++) {
        if (l[i] > '0') c++;
    }
    if (c == k) rs = (rs%mod + 1%mod)%mod;
    // printf("QQQQ %lld\n", rs);

    ll rs2 = 0;
    i = 0;
    kk = k;
    nn = m;
    while (i < m) {
        for (int p = 0; p < (r[i]-'0'); p++) {
            if (i == 0 && p == 0) continue;
            // printf("%d %d %d %lld\n", p, nn, kk, dp[p][nn][kk]);
            rs2 = (rs2%mod + dp[p][nn][kk]%mod)%mod;
        }
        i++;
        if (i-1 >= 0 && r[i-1] > '0') {
            kk--;
        }
        if (kk < 0) break;
        nn--;
    }
    c = 0;
    for (int i = 0; i < m; i++) {
        if (r[i] > '0') c++;
    }
    if (c == k) rs2 = (rs2%mod + 1%mod)%mod;
    // printf("WWWW %lld\n", rs2);
    return (rs2%mod - rs%mod)%mod;
}

ll solve(string l, string r, int k) {
    if (l == r) return 0;
    int n = (int)l.length();
    int m = (int)r.length();
    // dp[0][1][0] = 1;
    for (int i = 1; i <= m; i++) dp[0][i][0] = 1;
    for (int p = 1; p <= 9; p++) dp[p][1][1] = 1;
    for (int i = 2; i <= m; i++) {
        for (int j = 0; j <= k; j++) {
            for (int p = 0; p <= 9; p++) {
                for (int b = 0; b <= 9; b++) {
                    if (p > 0) {
                        if (j-1 < 0) continue;
                        dp[p][i][j] = (dp[p][i][j]%mod + dp[b][i-1][j-1]%mod)%mod;
                    } else {
                        if (j == 0) continue;
                        dp[p][i][j] = (dp[p][i][j]%mod + dp[b][i-1][j]%mod)%mod;
                    }
                }
            }
        }
    }
    // for (int i = 1; i <= m; i++) printf("ooo %lld\n", dp[0][i][0]);
    // for (int i = 2; i <= m; i++) {
    //     for (int j = 0; j <= k; j++) {
    //         for (int p = 0; p <= 9; p++) {
    //             if (dp[p][i][j] < 0) {
    //                 printf("%d %d %d %lld\n", p, i, j ,dp[p][i][j]);
    //             }
    //         }
    //     }
    // }
    if (n == m) {
        return calculateOnce(l, r, k, n, m);
    }

    ll rs =0;
    for (int p = 1; p <= 9; p++) {
        for (int i = n+1; i < m; i++) {
            rs = (rs%mod + dp[p][i][k])%mod;
        }
    }
    // printf("A %lld\n", rs);
    int i = 0;
    int kk = k;
    int nn = n;
    while (i < n) {
        for (int p = (l[i]-'0')+1; p <= 9; p++) {
            if (i == 0 && p == 0) continue;
            // printf("%d %d %d %lld\n", p, nn, kk, dp[p][nn][kk]);
            rs = (rs%mod + dp[p][nn][kk]%mod)%mod;
        }
        i++;
        if (i-1 >= 0 && l[i-1] > '0') {
            kk--;
        }
        if (kk < 0) break;
        nn--;
    }
    // printf("B %lld\n", rs);
    i = 0;
    kk = k;
    nn = m;
    while (i < m) {
        for (int p = 0; p < (r[i]-'0'); p++) {
            if (i == 0 && p == 0) continue;
            // printf("%d %d %d %lld\n", p, nn, kk, dp[p][nn][kk]);
            rs = (rs%mod + dp[p][nn][kk]%mod)%mod;
        }
        i++;
        if (i-1 >= 0 && r[i-1] > '0') {
            kk--;
        }
        if (kk < 0) break;
        nn--;
    }
    int c = 0;
    for (int i = 0; i < m; i++) {
        if (r[i] > '0') c++;
    }
    if (c == k) rs = (rs%mod + 1%mod)%mod;
    return rs;
}

int main() {
    string l, r;
    int k;
    cin >> l;
    cin >> r;
    cin >> k;

    printf("%lld\n", solve(l ,r, k));


    // int t;
    // cin >> t;
    // for (int tc = 0; tc < t; tc++) {
    //     printf("Test case %d\n", tc+1);
    //     string l, r;
    //     int k;
    //     cin >> l;
    //     cin >> r;
    //     cin >> k;

    //     ll rs1 = bruteForce(l,r,k);
    //     memset(dp, 0, sizeof(dp));
    //     ll rs2 = solve(l,r,k);
    //     if (rs1 != rs2) {
    //         printf("brute force %lld\n", rs1);
    //         printf("DP %lld\n", rs2);
    //         printf("+++++++++++++++++++++++++++++++\n");
    //     }
        
    // }
    return 0;
}