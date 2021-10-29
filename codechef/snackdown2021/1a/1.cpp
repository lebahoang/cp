#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <queue>
#include <utility>
using namespace std;
using ll = long long;
// g++ -std=c++14 -Wshadow -Wall -o s.out -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined 1.cpp && ./s.out
void pv(vector<ll>& x) {
    for (int k: x) {
        printf("%d ", k);
    }
    printf("\n");
}
ll find_min_cost(vector<ll>& a, vector<ll>& prefix, int s, int e) {
    // if e-s+1 is odd then return by reducing all elements to a[(e+s)/2]
    // else return min(reducing to a[(e+s)/2], reducing to a[(e+s)/2+1])
    ll l = e-s+1;
    if (l%2 == 0) {
        int i = (e+s)/2;
        int j = i+1;
        ll costi = 0;
        ll costj = 0;
        if (s-1 >= 0) {
            costi = abs(a[i]*(ll)(i-s+1) - (prefix[i]-prefix[s-1])) + abs(a[i]*(ll)(e-i) - (prefix[e]-prefix[i]));
            costj = abs(a[j]*(ll)(j-s+1) - (prefix[j]-prefix[s-1])) + abs(a[j]*(ll)(e-j) - (prefix[e]-prefix[j]));
            return min(costi, costj);
        } else {
            costi = abs(a[i]*(ll)(i-s+1) - (prefix[i])) + abs(a[i]*(ll)(e-i) - (prefix[e]-prefix[i]));
            costj = abs(a[j]*(ll)(j-s+1) - (prefix[j])) + abs(a[j]*(ll)(e-j) - (prefix[e]-prefix[j]));
            // printf("costi[%d] %d, costj[%d] %d\n", a[i], costi, a[j], costj);
            return min(costi, costj);
        }
    } else {
        int i = (e+s)/2;
        if (s-1 >= 0) {
            return abs(a[i]*(ll)(i-s+1) - (prefix[i]-prefix[s-1])) + abs(a[i]*(ll)(e-i) - (prefix[e]-prefix[i]));
        } else {
            return abs(a[i]*(ll)(i-s+1) - (prefix[i])) + abs(a[i]*(ll)(e-i) - (prefix[e]-prefix[i]));
        } 
    }
}
ll solve(int n, vector<ll>& a) {
    sort(a.begin(), a.end());
    // pv(a);
    vector<ll> prefix(n, 0);
    for (int i = 0; i < n; i++) {
        if (i == 0) prefix[i] = a[i];
        else {
            prefix[i] = prefix[i-1]+a[i];
        }
    }
    ll rs = 1e17;
    for (int i = 0; i < n-1; i++) {
        ll x = a[i]-a[0];
        ll y = a[n-1]-a[i+1];
        if (x == y) rs = min(rs, 0ll);
        else if (x > y) {
            if (y > 0 || i+1 < n-1) {
                rs = min(rs, (x-y));
            } else {
                // find_min_cost for range [0, i]
                // printf("dsadsa %d\n", find_min_cost(a, prefix, 0, i));
                rs = min(rs, find_min_cost(a, prefix, 0, i));
            }
        } else {
            if (x > 0 || i > 0) {
                rs = min(rs, (y-x));
            } else {
                // find_min_cost for range [i+1, n-1]
                rs = min(rs, find_min_cost(a, prefix, i+1, n-1));
            }
        }
        // printf("x %lld y %lld\n", x, y);
        // printf("RS %d, %lld\n", i, rs);
    }
    return rs;
}


ll solve1(int n, vector<ll>& a) {
    sort(a.begin(), a.end());
    // pv(a);
    if (n == 2) return 0;
    if (n == 3) {
        return min(abs(a[0]-a[1]), abs(a[1]-a[2]));
    }
    ll rs = 1e17;
    unordered_map<ll, int> m;
    for (ll k: a) {
        if (m.find(k) != m.end()) {
            m[k]++;
        } else {
            m[k] = 1;
        }
    }
    for (int i = 1; i < n-1; i++) {
        ll x = a[i]-a[0];
        ll y = a[n-1]-x;
        auto it = m.find(y);
        if (it != m.end()) {
            if ((it->second > 1 && a[i] == a[n-1]) || \
                (a[i] != it->first && a[i] != a[n-1]) || \
                (it->second > 1 && a[i] == it->first)) {
                // printf("a[%d] %lld x %lld y %lld \n", i, a[i], x, y);
                return 0;
            }
        }
    }
    ///////
    vector<pair<ll, int>> b = {};
    for (int i = n-2; i > 0; i--) {
        b.push_back({a[n-1]-a[i], i});
    }
    // printf("B ------\n");
    // for (auto x: b) {
    //     printf("{%lld, %d} ", x.first, x.second);
    // }
    // printf("\n");

    for (int i = 1; i < n-1; i++) {
        ll x = a[i]-a[0];
        int l = 0;
        int r = (int)b.size()-1;
        if (x <= b[0].first) {
            if (i == b[0].second) continue;
            rs = min(rs, abs(b[0].first-x));
        } else if (x >= b[r].first) {
            if (i == b[r].second) continue;
            rs = min(rs, abs(b[r].first-x));
        } else {
            while (l <= r) {
                int mid = (l+r)/2;
                if (b[mid].first >= x && b[mid-1].first < x) {
                    if (b[mid].second == i) {
                        rs = min(rs, abs(b[mid-1].first-x));
                    } else if (b[mid-1].second == i) {
                        rs = min(rs, abs(b[mid].first-x));
                    } else {
                        rs = min(rs, abs(b[mid].first-x));
                        rs = min(rs, abs(b[mid-1].first-x));
                    }
                    break;
                } else if (x > b[mid].first) {
                    l = mid+1;
                } else {
                    r = mid-1;
                }
            }
        }
        // printf("i %d, x %lld, RS %lld\n", i, x, rs);
    }
    return rs;
}


ll bf(int n, vector<ll>& a) {
    ll rs = 1e17;
    vector<ll> x;
    vector<ll> y;
    for (int i = 1; i < (1 << n)-1; i++) {
        for (int j = 0; j < n; j++) {
            if ((i & (1 << j)) != 0) {
                x.push_back(a[j]);
            } else {
                y.push_back(a[j]);
            }
        }
        sort(x.begin(), x.end());
        sort(y.begin(), y.end());
        // for (int k: x) {
        //     printf("%d ", k);
        // }
        // printf("\n");
        // for (int k: y) {
        //     printf("%d ", k);
        // }
        // printf("\n");
        // printf("-----------\n");
        int sx = (int)x.size();
        int sy = (int)y.size();
        if (sx > 1 && sy > 1) {
            rs = min(rs, abs(x[sx-1]-x[0]-(y[sy-1]-y[0])));
        } else if (sy == 1) {
            vector<ll> prefix(sx, 0);
            for (int k = 0; k < sx; k++) {
                if (k == 0) prefix[k] = x[k];
                else prefix[k] = prefix[k-1]+x[k];
            }
            rs = min(rs, find_min_cost(x, prefix, 0, sx-1));
        } else {
            vector<ll> prefix(sy, 0);
            for (int k = 0; k < sy; k++) {
                if (k == 0) prefix[k] = y[k];
                else prefix[k] = prefix[k-1]+y[k];
            }
            rs = min(rs, find_min_cost(y, prefix, 0, sy-1));
        }
        // printf("RS %lld\n", rs);
        // if (rs == 258965305) break;
        x.clear();
        y.clear();
    }
    return rs;
}

int main() {
    int t;
    cin >> t;
    for (int cs = 0; cs < t; cs++) {
        int n;
        cin >> n;
        vector<ll> a(n, 0);
        for (int i = 0; i < n; i++) cin >> a[i];
        printf("%lld\n", min(solve(n, a), solve1(n, a)));
        // printf("%lld\n", solve(n, a));
        // printf("%lld\n", solve1(n, a));
        // printf("%lld\n", bf(n, a));
        // printf("+++++++++\n");

        // if (solve1(n, a) != bf(n, a)) {
        //     pv(a);
        // }

        // if (min(solve(n, a), solve1(n, a)) != bf(n, a)) {
        //     pv(a);
        // }
    }
    return 0;
}