#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include <utility>

// g++ -std=c++14 -O2 -o s.out 3.cpp && ./s.out < x.txt
using namespace std;
using ll = long long;
struct I {
    int u;
    int v;
    ll d;
};
struct C {
    int i;
    int j;
    ll p;
};
struct Y {
    set<ll> s;
    priority_queue<pair<ll, ll>, vector<pair<ll,ll>>, greater<pair<ll, ll>>> q;
    vector<pair<ll,ll>> items;

    void getAllItems() {
        while (!q.empty()) {
            auto x = q.top();
            q.pop();
            items.push_back(x);
        }
        reverse(items.begin(), items.end());
    }
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
void collectResult(vector<ll>& rs, Y y, ll add) {
    for (auto x: y.items) {
        rs.push_back(x.first+add);
    }
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
vector<pair<ll,ll>> getTopKsFromA(vector<pair<ll,ll>>& a, vector<pair<ll,ll>>& b, ll add, int k) {
    int n = a.size();
    int m = b.size();
    vector<pair<ll,ll>> rs = {};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if ((int)rs.size() == k) return rs;
            if (i+1 < n && a[i].first+b[j].first < a[i+1].first+b[0].first) break;
            rs.push_back({a[i].first+b[j].first+add, a[i].second|b[j].second});
        }
    }
    return rs;
}
vector<pair<ll,ll>> getTopKs(vector<pair<ll,ll>>& a, vector<pair<ll,ll>>& b, ll add, int k) {
    vector<pair<ll,ll>> rs1 = getTopKsFromA(a,b,add,k);
    vector<pair<ll,ll>> rs2 = getTopKsFromA(b,a,add,k);
    for (int i = 0; i < (int)rs1.size(); i++) {
        if (rs1[i].first > rs2[i].first) return rs1;
    }
    return rs2;
}
ll setBits(ll x, int from, int to) {
    ll y = x;
    for (int i = from; i <= to; i++) {
        y |= 1ll << i;
    }
    return y;
}
ll f(int i, int j, int k,
     vector<ll>& g, vector<ll>& prefix,
     vector<vector<ll>>& intervalAdd,
     vector<vector<ll>>& dp,
     vector<vector<Y>>& m) {
    
    if (dp[i][j] != -1e12) {
        return dp[i][j];
    }
    if (j-i+1 <= 2) {
        Y y{};
        y.s.insert(0);
        y.q.push({0, 0});
        y.getAllItems();
        m[i][j] = y;
        dp[i][j] = 0;
        return dp[i][j];
    }

    Y y{};
    for (int a = i+1; a < j; a++) {
        for (int b = a; b < j; b++) {
            ll p1 = prefix[b]-prefix[a-1];
            ll p2 = intervalAdd[a][b];
            ll dpx = f(i,a-1,k,g,prefix,intervalAdd,dp,m);
            ll dpy = f(b+1,j,k,g,prefix,intervalAdd,dp,m);
            ll candidate = p1+p2+dpx+dpy;
            // printf("calculate dp[%d][%d], p1 %lld p2 %lld dpx[%d][%d] %lld dpy[%d][%d] %lld\n", i, j, p1, p2, i,a-1,dpx, b+1,j,dpy);
            vector<pair<ll,ll>> topKs = getTopKs(m[i][a-1].items, m[b+1][j].items, p1+p2, k);
            for (pair<ll,ll>& t: topKs) {
                ll v = t.first;
                ll bits = t.second;
                bits = setBits(bits, a, b);
                if (y.s.find(bits) == y.s.end()) {
                    if ((int)y.q.size() < k) {
                        y.s.insert(bits);
                        y.q.push({v,bits});
                    } else {
                        ll vq = y.q.top().first;
                        ll qbits = y.q.top().second;
                        if (vq >= v) break;
                        y.s.erase(qbits);
                        y.q.pop();
                        y.s.insert(bits);
                        y.q.push({v,bits});
                    }
                }
            }
            dp[i][j] = max(dp[i][j], candidate);
        }
    }
    if (y.s.find(0) == y.s.end()) {
        if ((int)y.q.size() < k) {
            y.s.insert(0);
            y.q.push({0,0});
        } else {
            ll vq = y.q.top().first;
            ll qbits = y.q.top().second;
            if (vq < 0) {
                y.q.pop();
                y.s.erase(qbits);
                y.s.insert(0);
                y.q.push({0,0});
            };
        }
    }
    
    y.getAllItems();
    m[i][j] = y;
    dp[i][j] = max(dp[i][j], 0ll);
    return dp[i][j];
}
void solve(int n, int m, int k, vector<ll>& g, vector<I>& interval) {
    vector<vector<ll>> dp(n+1, vector<ll>(n+1, -1e12));
    vector<vector<Y>> pqs(n+1, vector<Y>(n+1, Y{}));
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
    vector<C> c = {};
    vector<ll> rs = {prefix[n]+intervalAdd[1][n]};
    // vector<ll> rs = {};
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
                c.push_back(C{a+1, n-b, p});
            } else if (a-1 < 0 && b > 0) {
                f(1,n-b,k,g,prefix,intervalAdd,dp,pqs);
                c.push_back(C{1, n-b, p});
            } else if (a-1 >= 0 && b == 0) {
                f(a+1,n,k,g,prefix,intervalAdd,dp,pqs);
                c.push_back(C{a+1, n, p});
            } else {
                f(1,n,k,g,prefix,intervalAdd,dp,pqs);
                c.push_back(C{1, n, p});
            }
        }
    }
    for (C y: c) {
        collectResult(rs, pqs[y.i][y.j], y.p);
    }
    sort(rs.begin(), rs.end(), [](ll& i, ll& j){
        return i >= j;
    });
    // reverse(rs.begin(), rs.end());
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
