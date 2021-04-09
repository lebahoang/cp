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

// g++ -std=c++14 -O2 -o s.out 3.cpp && ./s.out < x.txt
using namespace std;
using ll = long long;
struct I {
    int u;
    int v;
    ll d;
};
vector<vector<ll>> getInterval(int n, vector<ll>& g, vector<I>& interval) {
    vector<vector<ll>> rs(n+5, vector<ll>(n+5, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            ll x = 0;
            for (I it: interval) {
                if (i <= it.u && j >= it.v) x += it.d;
            }
            rs[i][j] = x;
        }
    }
    return rs;
}
vector<ll> getPrefix(int n, vector<ll>& g) {
    vector<ll> prefix(n+1, 0);
    for (int i = 0; i < n; i++) {
        if (i == 0) prefix[i] = g[i];
        else prefix[i] = prefix[i-1]+g[i];
    }
    return prefix;
}
ll f(int indA, int indB, int i, int j, int n, vector<ll>& g, vector<ll>& prefix, vector<vector<ll>>& intervalAdd, vector<vector<vector<vector<ll>>>>& dp) {
    if (dp[indA][indB][i][j] != -1e12) {
        // printf("dsadasdas %lld\n", dp[indA][indB][i][j]);
        return dp[indA][indB][i][j];
    }
    if (i == 0 && j == 0 && n == 2) {
        dp[indA][indB][i][j] = 0;
        return dp[indA][indB][i][j];
    }
    if (i == 1 && j == 0 && n == 2) {
        dp[indA][indB][i][j] = g[indA] + intervalAdd[indA][indA];
        return dp[indA][indB][i][j];
    }
    if (i == 0 && j == 1 && n == 2) {
        dp[indA][indB][i][j] = g[indB] + intervalAdd[indB][indB];
        return dp[indA][indB][i][j];
    }
    if (i == 0 && j == 0 && n == 1) {
        dp[indA][indB][i][j] = 0;
        return dp[indA][indB][i][j];
    }
    for (int k = indA; k <= indB; k++) {
        if (k-indA+1 < i+1) continue;
        if (indB-k < j+1) continue;
        int len1 = k-indA+1;
        int len2 = indB-k;
        // printf("indA %d k %d indB %d i %d j %d, len1 %d len2 %d\n", indA, k, indB, i, j, len1, len2);
        for (int a = 0; a <= len1-1-i; a++) {
            for (int b = 0; b <= len2-1-j; b++) {
                ll x = 0;
                if (a > 0 || b > 0) {
                    x += intervalAdd[k-a+1][k+b];
                }
                ll p1 = 0;
                if (indA-1 >= 0) {
                    p1 = prefix[indA+i]-prefix[indA-1];
                } else {
                    p1 = prefix[indA+i];
                }
                ll p2 = 0;
                if (indB-j >= 0) {
                    p2 = prefix[indB]-prefix[indB-j];
                } else {
                    p2 = prefix[indB];
                }
                x +=  p1 + p2 +\
                     f(indA, k, i, a, len1, g, prefix, intervalAdd, dp) +\
                     f(k+1, indB, b, j, len2, g, prefix, intervalAdd, dp);
                // printf("x %lld\n", x);
                dp[indA][indB][i][j] = max(dp[indA][indB][i][j], x);
            }
        }
    }
    // ll p1 = 0;
    // if (indA-1 >= 0) {
    //     p1 = prefix[indB]-prefix[indA-1];
    // } else {
    //     p1 = prefix[indB];
    // }

    // dp[indA][indB][i][j] = max(dp[indA][indB][i][j], p1+intervalAdd[indA][indB]);
    printf("indA %d indB %d i %d j %d dp %lld\n", indA, indB, i, j, dp[indA][indB][i][j]);
    return dp[indA][indB][i][j];
}
void solve(int n, int m, int k, vector<ll>& g, vector<I>& interval) {
    vector<vector<vector<vector<ll>>>> dp(n+5, vector<vector<vector<ll>>>(n+5, vector<vector<ll>>(n+5, vector<ll>(n+5, -1e12))));
    vector<vector<ll>> intervalAdd = getInterval(n, g, interval);
    vector<ll> prefix = getPrefix(n, g);
    if (k != 1) {
        printf("-1000\n");
        return;
    }
    ll rs = -1e12;
    for (int i = 0; i <= n-2; i++) {
        for (int j = 0; j <= n-2-i; j++) {
            ll t = f(1,n,i,j,n,g,prefix,intervalAdd,dp);
            // printf("i %d, j %d, %lld\n", i, j, t);
            rs = max(rs, t);
        }
    }
    printf("%lld\n", rs);
}
int main() {
    int t;
    cin >> t;
    for (int cs = 0; cs < t; cs++) {
        int n,m,k;
        cin >> n >> m >> k;
        vector<ll> g(n+1, 0);
        vector<I> interval = {};
        for (int i = 1; i <= n; i++) cin >> g[i];
        for (int i = 0; i < m; i++) {
            int u,v;
            ll d;
            cin >> u >> v >> d;
            I it = {u,v,d};
            interval.push_back(it);
        }
        solve(n,m,k,g,interval);
    }
    return 0;
}
