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
    for (int i = 1; i <= n; i++) {
        if (i == 1) prefix[i] = g[i];
        else prefix[i] = prefix[i-1]+g[i];
    }
    return prefix;
}
ll f(int indA, int indB, int i, int j, int n, 
     vector<ll>& g, vector<ll>& prefix, vector<vector<ll>>& intervalAdd,
     vector<vector<vector<vector<ll>>>>& dp, ll& count) {
    
    // if (n == 4) {
    //     printf("indA %d indB %d i %d j %d xxxx\n", indA, indB, i, j);
    //     count++;
    // }
    if (dp[indA][indB][i][j] != -1e12) {
        return dp[indA][indB][i][j];
    }
    if (i == 0 && j == 0 && n == 1) {
        dp[indA][indB][i][j] = 0;
        return dp[indA][indB][i][j];
    }
    if (i == 1 && j == 0 && n <= 2) {
        if (indA == 1) dp[indA][indB][i][j] = g[indA] + intervalAdd[indA][indA];
        else dp[indA][indB][i][j] = g[indA];
        return dp[indA][indB][i][j];
    }
    if (i == 0 && j == 1 && n <= 2) {
        if (indB == (int)g.size()-1) dp[indA][indB][i][j] = g[indB] + intervalAdd[indB][indB];
        else dp[indA][indB][i][j] = g[indB];
        return dp[indA][indB][i][j];
    }
    if (n-1 == i+j) {
        ll p1 = 0;
        ll p3 = 0;
        if (i > 0) {
            if (indA-1 >= 1) p1 = prefix[indA+i-1]-prefix[indA-1];
            else p1 = prefix[indA+i-1];
            if (indA == 1) p3 = intervalAdd[indA][indA+i-1];
        }
        ll p2 = 0;
        ll p4 = 0;
        if (j > 0) {
            if (indB-j >= 1) p2 = prefix[indB]-prefix[indB-j];
            else p2 = prefix[indB];
            if (indB == (int)g.size()-1) p4 = intervalAdd[indB-j+1][indB];
        }
        dp[indA][indB][i][j] = max(dp[indA][indB][i][j], p1+p2+p3+p4);
        // printf("dp[%d][%d][%d][%d] %lld, p1 %lld p2 %lld p3 %lld p4 %lld\n", indA, indB, i, j, dp[indA][indB][i][j], p1, p2, p3, p4);
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
                ll p0 = 0;
                if (a > 0 && b > 0) {
                    p0 += intervalAdd[k-a+1][k+b];
                } else if (a == 0 && b > 0) {
                    p0 += intervalAdd[k+1][k+b];
                } else if (a > 0 && b == 0) {
                    p0 += intervalAdd[k-a+1][k];
                }
                ll p1 = 0;
                if (i > 0) {
                    if (indA-1 >= 1) {
                        p1 = prefix[indA+i]-prefix[indA-1];
                    } else {
                        p1 = prefix[indA+i];
                    }
                }
                ll p2 = 0;
                if (j > 0) {
                    if (indB-j >= 1) {
                        p2 = prefix[indB]-prefix[indB-j];
                    } else {
                        p2 = prefix[indB];
                    }
                }
                
                ll x = p0 +\
                     f(indA, k, i, a, len1, g, prefix, intervalAdd, dp, count) +\
                     f(k+1, indB, b, j, len2, g, prefix, intervalAdd, dp, count);
                if (indA == 1 && indB == 4) count++;
                // printf("p0 %lld\n", p0);
                // printf("calcualte dp[%d][%d][%d][%d] by dp[%d][%d][%d][%d] %lld and dp[%d][%d][%d][%d] %lld\n", \
                //         indA, indB, i, j, indA, k, i, a, dp[indA][k][i][a], k+1, indB, b, j, dp[k+1][indB][b][j]);
                dp[indA][indB][i][j] = max(dp[indA][indB][i][j], x);
            }
        }
    }
    // printf("indA %d indB %d i %d j %d dp %lld\n", indA, indB, i, j, dp[indA][indB][i][j]);
    return dp[indA][indB][i][j];
}
vector<pair<ll,ll>> bf(int n, int m, int k, vector<ll>& g, vector<ll>& prefix, vector<I>& interval) {
    vector<pair<ll,ll>> rs = {};
    for (int i = 0; i < (1 << n); i++) {
        ll t = 0;
        vector<int> x(n+1, 0);
        for (int j = 0; j < n; j++) {
            if ((i & (1 << j)) != 0) {
                t += g[j+1];
                x[j+1] = 1;
            }
        }
        for (I it: interval) {
            bool f = true;
            for(int c = it.u; c <= it.v; c++) {
                if (x[c] != 1) {
                    f = false;
                    break;
                }
            }
            if (f) t += it.d;
        }
        rs.push_back({t, i});
    }
    sort(rs.begin(), rs.end(), [](pair<ll,ll>& a, pair<ll,ll>& b) {
        return a.first >= b.first;
    });
    return rs;
}
void solve(int n, int m, int k, vector<ll>& g, vector<I>& interval) {
    vector<vector<vector<vector<ll>>>> dp(n+5, vector<vector<vector<ll>>>(n+5, vector<vector<ll>>(n+5, vector<ll>(n+5, -1e12))));
    vector<vector<ll>> intervalAdd = getInterval(n, g, interval);
    vector<ll> prefix = getPrefix(n, g);
    if (n < 19) {
        vector<pair<ll,ll>> rs = bf(n,m,k,g,prefix,interval);
        for (int i = 0; i < k; i++) {
            printf("%lld (i %lld) ", rs[i].first, rs[i].second);
            // printf("%lld ", rs[i].first);
        }
        printf("\n");
        return;
    } else if (n >= 19 && k > 1) {
        printf("-1000\n");
        return;
    }
    ll count = 0;
    ll rs = max(0ll, prefix[n]+intervalAdd[1][n]);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n-1-i; j++) {
            ll t = f(1,n,i,j,n,g,prefix,intervalAdd,dp,count);
            // printf("i %d, j %d, %lld\n", i, j, t);
            rs = max(rs, t);
        }
    }
    // for (int indA = 1; indA <= n; indA++) {
    //     for (int indB = 1; indB <= n; indB++) {
    //         for (int i = 0; i < n; i++) {
    //             for (int j = 0; j < n-i; j++) {
    //                 if (dp[indA][indB][i][j] == -1e12) continue;
    //                 printf("indA %d indB %d i %d j %d, dp %lld\n", indA, indB, i, j, dp[indA][indB][i][j]);
    //             }
    //         }
    //     }
    // }
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
