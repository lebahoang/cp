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

// g++ -std=c++17 -O2 -o s.out 4.cpp && ./s.out < x.txt
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
    ll bits;
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
            items.push_back({x.first, x.second});
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
void collectResult(vector<pair<ll, ll>>& rs, Y y, ll bits, ll add) {
    for (auto x: y.items) {
        rs.push_back({x.first+add, bits|x.second});
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
bool addToQueue(ll v, ll bits, int k, Y& y) {
    if (y.s.find(bits) == y.s.end()) {
        if ((int)y.q.size() < k) {
            y.s.insert(bits);
            y.q.push({v,bits});
            return true;
        }
        ll vq = y.q.top().first;
        ll qbits = y.q.top().second;
        if (vq > v) return false;
        y.s.erase(qbits);
        y.q.pop();
        y.s.insert(bits);
        y.q.push({v,bits});
        return true;
    }
    return true;
}
ll setBits(ll x, int from, int to) {
    ll y = x;
    ll a = ((1ll << (to))-1) ^ ((1ll << (from-1))-1);
    return y | a;
}
void getTopKs(vector<pair<ll,ll>>& a, vector<pair<ll,ll>>& b, ll add, int k, int fromBit, int toBit, Y& y) {
    int n = a.size();
    int m = b.size();
    set<pair<int, int>> s;
    priority_queue<pair<ll, pair<int, int>>, vector<pair<ll, pair<int, int>>>> q;
    s.insert({0,0});
    q.push({a[0].first+b[0].first+add, {0, 0}});
    int cnt = 0;
    while (cnt < k && !q.empty()) {
        auto v = q.top();
        int i = v.second.first;
        int j = v.second.second;
        bool f1 = true;
        if (s.find({i+1, j}) == s.end() && i+1 < n) {
            ll t1 = a[i+1].first + b[j].first + add;
            s.insert({i+1, j});
            q.push({t1, {i+1, j}});
        } else {
            f1 = false;
        }
        bool f2 = true;
        if (s.find({i, j+1}) == s.end() && j+1 < m) {
            ll t2 = a[i].first + b[j+1].first + add;
            s.insert({i, j+1});
            q.push({t2, {i, j+1}});
        } else {
            f2 = false;
        }
        if (!f1 && !f2) {
            q.pop();
            // rs.push_back({v.first, a[i].second|b[j].second});
            cnt++;
            bool continued = addToQueue(v.first, setBits(a[i].second|b[j].second, fromBit, toBit), k, y);
            if (!continued) break;
        }
    }
}
ll f(int i, int j, int k, ll addedBits,
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
        y.q.push({0,0});
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
            ll dpx = f(i,a-1,k,addedBits,g,prefix,intervalAdd,dp,m);
            ll dpy = f(b+1,j,k,addedBits,g,prefix,intervalAdd,dp,m);
            ll candidate = p1+p2+dpx+dpy;
            // printf("calculate dp[%d][%d], p1 %lld p2 %lld dpx[%d][%d] %lld dpy[%d][%d] %lld\n", i, j, p1, p2, i,a-1,dpx, b+1,j,dpy);
            getTopKs(m[i][a-1].items, m[b+1][j].items, p1+p2, k, a, b, y);
            // if (i == 1 && j == (int)g.size()-1 && a == 9 && b == 9) {
            //     for (auto e: m[i][a-1].items) {
            //         printf("i %d a-1 %d %lld %lld\n", i, a-1, e.first, e.second);
            //     }

            //     for (auto e: m[b+1][j].items) {
            //         printf("b+1 %d j %d %lld %lld\n", b+1, j, e.first, e.second);
            //     }

            //     printf("----------- %d\n", k);
            //     for (auto t: topKs) {
            //         printf("%lld %lld\n", t.first-p1-p2, t.second);
            //     }
            // }
            dp[i][j] = max(dp[i][j], candidate);
        }
    }
    addToQueue(0, 0, k, y);
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
    vector<C> c = {};
    vector<pair<ll, ll>> rs = {{prefix[n]+intervalAdd[1][n], (1ll << n)-1}};
    int cnt = 0;
    for (int a = 0; a < n; a++) {
        for (int b = 0; b < n-a; b++) {
            cnt++;
            ll bits = 0;
            ll p1 = 0;
            ll p2 = 0;
            if (a-1 >= 0) {
                bits = setBits(bits, 1, a);
                p1 = prefix[a];
                p2 = intervalAdd[1][a]; 
            }
            ll p3 = 0;
            ll p4 = 0;
            if (b > 0) {
                bits = setBits(bits, n-b+1, n);
                p3 = prefix[n]-prefix[n-b];
                p4 = intervalAdd[n-b+1][n];
            }
            ll p = p1+p2+p3+p4;
            if (a-1 >= 0 && b > 0) {
                f(a+1,n-b,k,bits,g,prefix,intervalAdd,dp,pqs);
                c.push_back(C{a+1, n-b, bits, p});
            } else if (a-1 < 0 && b > 0) {
                f(1,n-b,k,bits,g,prefix,intervalAdd,dp,pqs);
                c.push_back(C{1, n-b, bits, p});
            } else if (a-1 >= 0 && b == 0) {
                f(a+1,n,k,bits,g,prefix,intervalAdd,dp,pqs);
                c.push_back(C{a+1, n, bits, p});
            } else {
                f(1,n,k,bits,g,prefix,intervalAdd,dp,pqs);
                c.push_back(C{1, n, bits, p});
            }
        }
    }
    for (C y: c) {
        collectResult(rs, pqs[y.i][y.j], y.bits, y.p);
    }
    sort(rs.begin(), rs.end(), [](pair<ll,ll>& i, pair<ll,ll>& j){
        return i.first >= j.first;
    });
    for (int i = 0; i < k; i++) {
        // printf("%lld (%lld) ", rs[i].first, rs[i].second);
        printf("%lld ", rs[i].first);
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
