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
            for (int k = i; k <= j; k++) {
                x += g[k];
            }
            for (I it: interval) {
                if (i <= it.u && j >= it.v) x += it.d;
            }
            rs[i][j] = x;
        }
    }
    return rs;
}
ll f(int indA, int indB, int i, int j, int n, vector<vector<ll>>& intervalAdd, vector<vector<vector<vector<ll>>>>& dp) {
    if (dp[indA][indB][i][j] != -1e12) return dp[indA][indB][i][j];
    for (int k = indA; k <= indB; k++) {
        if (k-indA+1 < i+2) continue;
        if (indB-k < j+2) continue;
        int len1 = k-indA+1;
        int len2 = indB-k;
        for (int a = 0; a <= len1-2-i; a++) {
            for (int b = 0; b <= len2-2-j; b++) {
                ll x = 0;
                if (a > 0 || b > 0) {
                    x += intervalAdd[k-a+1][k+b];
                }
                x += f(indA, k, i, a, len1, intervalAdd, dp) + f(indA+k, indB, b, j, len2, intervalAdd, dp);
                dp[indA][indB][i][j] = max(dp[indA][indB][i][j], x);
            }
        }
    }
    return dp[indA][indB][i][j];
}
void solve(int n, int m, int k, vector<ll>& g, vector<I>& interval) {
    vector<vector<vector<vector<ll>>>> dp(n+5, vector<vector<vector<ll>>>(n+5, vector<vector<ll>>(n+5, vector<ll>(n+5, -1e12))));
    vector<vector<ll>> intervalAdd = getInterval(n, g, interval);
    if (k != 1) {
        printf("-1000\n");
        return;
    }
    ll rs = -1e12;
    for (int i = 0; i <= n-2; i++) {
        for (int j = 0; j <= n-2-i; j++) {
            ll t = f(1,n,i,j,n,intervalAdd,dp);
            printf("i %d, j %d, %lld\n", i, j, t);
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
