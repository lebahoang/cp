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
struct Y {
    int i;
    int j;
    ll p;
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
vector<ll> bf(int n, int m, int k, vector<ll>& g, vector<ll>& prefix, vector<I>& interval) {
    vector<ll> rs = {};
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
        rs.push_back(t);
    }
    sort(rs.begin(), rs.end(), [](ll& a, ll& b) {
        return a >= b;
    });
    return rs;
}
void collectResult(vector<ll>& rs, priority_queue<ll, vector<ll>, greater<ll>>& pq, ll add) {
    while (!pq.empty()) {
        ll x = pq.top();
        pq.pop();
        rs.push_back(x+add);
    }
}
ll f(int i, int j, int k,
     vector<ll>& g, vector<ll>& prefix,
     vector<vector<ll>>& intervalAdd,
     vector<vector<ll>>& dp,
     vector<vector<priority_queue<ll, vector<ll>, greater<ll>>>>& m) {
    
    if (dp[i][j] != -1e12) {
        return dp[i][j];
    }
    if (j-i+1 <= 2) {
        m[i][j].push(0);
        dp[i][j] = 0;
        return dp[i][j];
    }

    for (int a = i+1; a < j; a++) {
        for (int b = a; b < j; b++) {
            ll p1 = prefix[b]-prefix[a-1];
            ll p2 = intervalAdd[a][b];
            ll dpx = f(i,a-1,k,g,prefix,intervalAdd,dp,m);
            ll dpy = f(b+1,j,k,g,prefix,intervalAdd,dp,m);
            ll candidate = p1+p2+dpx+dpy;
            // printf("calculate dp[%d][%d], p1 %lld p2 %lld dpx[%d][%d] %lld dpy[%d][%d] %lld\n", i, j, p1, p2, i,a-1,dpx, b+1,j,dpy);
            if ((int)m[i][j].size() < k) m[i][j].push(candidate);
            else {
                ll t = m[i][j].top();
                if (t < candidate) {
                    m[i][j].pop();
                    m[i][j].push(candidate);
                }
            }
            dp[i][j] = max(dp[i][j], candidate);
        }
    }
    if ((int)m[i][j].size() < k) m[i][j].push(0);
    else {
        ll t = m[i][j].top();
        if (t < 0) {
            m[i][j].pop();
            m[i][j].push(0);
        }
    }
    dp[i][j] = max(dp[i][j], 0ll);
    return dp[i][j];
}
void solve(int n, int m, int k, vector<ll>& g, vector<I>& interval) {
    vector<vector<ll>> dp(n+1, vector<ll>(n+1, -1e12));
    vector<vector<priority_queue<ll, vector<ll>, greater<ll>>>> pqs(n+1, vector<priority_queue<ll, vector<ll>, greater<ll>>>(n+1, priority_queue<ll, vector<ll>, greater<ll>>{}));
    vector<vector<ll>> intervalAdd = getInterval(n, g, interval);
    vector<ll> prefix = getPrefix(n, g);
    // if (n < 19) {
    //     vector<ll> rs = bf(n,m,k,g,prefix,interval);
    //     for (int i = 0; i < k; i++) {
    //         printf("%lld ", rs[i]);
    //     }
    //     printf("\n");
    //     return;
    // } else if (n >= 19 && k > 1) {
    //     printf("-1000\n");
    //     return;
    // }

    // ll rs = max(0ll, prefix[n]+intervalAdd[1][n]);
    vector<ll> rs = {prefix[n]+intervalAdd[1][n]};
    vector<Y> c = {};
    for (int a = 0; a < n; a++) {
        for (int b = 0; b < n-a; b++) {
            ll p1 = 0;
            ll p2 = 0;
            if (a-1 >= 0) {
                p1 = prefix[a];
                p2 = intervalAdd[1][a]; 
            }
            ll p3 = 0;
            ll p4 = 0;
            if (b > 0) {
                p3 = prefix[n]-prefix[n-b];
                p4 = intervalAdd[n-b+1][n];
            }
            // if (a-1 >= 0 && b > 0) {
            //     rs = max(rs, p1+p2+p3+p4+f(a+1,n-b,k,g,prefix,intervalAdd,dp,pqs));
            // } else if (a-1 < 0 && b > 0) {
            //     rs = max(rs, p1+p2+p3+p4+f(1,n-b,k,g,prefix,intervalAdd,dp,pqs));
            // } else if (a-1 >= 0 && b == 0) {
            //     rs = max(rs, p1+p2+p3+p4+f(a+1,n,k,g,prefix,intervalAdd,dp,pqs));
            // } else {
            //     rs = max(rs, p1+p2+p3+p4+f(1,n,k,g,prefix,intervalAdd,dp,pqs));
            // }
            ll p = p1+p2+p3+p4;
            if (a-1 >= 0 && b > 0) {
                f(a+1,n-b,k,g,prefix,intervalAdd,dp,pqs);
                c.push_back(Y{a+1, n-b, p});
            } else if (a-1 < 0 && b > 0) {
                f(1,n-b,k,g,prefix,intervalAdd,dp,pqs);
                c.push_back(Y{1, n-b, p});
            } else if (a-1 >= 0 && b == 0) {
                f(a+1,n,k,g,prefix,intervalAdd,dp,pqs);
                c.push_back(Y{a+1, n, p});
            } else {
                f(1,n,k,g,prefix,intervalAdd,dp,pqs);
                c.push_back(Y{1, n, p});
            }
        }
    }
    for (Y y: c) {
        collectResult(rs, pqs[y.i][y.j], y.p);
    }
    sort(rs.begin(), rs.end(), [](ll& i, ll& j){
        return i >= j;
    });
    // for (int i = 1; i <= n; i++) {
    //     for (int j = i; j <= n; j++) {
    //         printf("dp[%d][%d] %lld\n", i, j, dp[i][j]);
    //     }
    // }
    for (int i = 0; i < k; i++) {
        printf("%lld ", rs[i]);
    }
    printf("\n");
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
