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

// g++ -std=c++14 -stdlib=libc++ -O2 -o s.out 3.cpp && ./s.out < x.txt
// https://codeforces.com/problemset/problem/1363/E
using namespace std;
using ll = long long;
const int nax = 200005;
ll cost[nax];
ll a[nax];
ll b[nax];
vector<int> vs[nax];
struct I {
    ll zeros;
    ll ones;
};
struct Y {
    I need;
    I have;
};
Y dfs(int v, int parent, ll minV, ll& total) {
    I have= {};
    if (a[v] == 0) have.zeros++;
    else have.ones++;
    I need= {};
    if (b[v] == 0) need.zeros++;
    else need.ones++;
    if (have.ones == need.ones || have.zeros == need.zeros) {
        have.ones = 0;
        have.zeros = 0;
        need.ones = 0;
        need.zeros = 0;
    }
    Y t = Y{need, have};
    for (auto x: vs[v]) {
        if (x == parent) continue;
        Y tx = dfs(x, v, min(minV, cost[v]), total);
        t.have.zeros += tx.have.zeros;
        t.have.ones += tx.have.ones;
        t.need.zeros += tx.need.zeros;
        t.need.ones += tx.need.ones;
    }
    // if (t.have.zeros == t.need.zeros && t.have.ones == t.need.ones) {
    //     total += min(cost[v], minV)*(t.need.zeros + t.need.ones);
    //     // printf("vertex %d, have zeros %d ones %d, need zeros %d ones %d, total %lld\n", v, t.have.zeros, t.have.ones, t.need.zeros, t.need.ones, total);
    //     t = Y{{0,0}, {0,0}};
    // } else {
    //     // printf("vertex %d, have zeros %d ones %d, need zeros %d ones %d, total %lld\n", v, t.have.zeros, t.have.ones, t.need.zeros, t.need.ones, total);
    // }
    ll x = min(t.have.zeros, t.need.zeros);
    ll y = min(t.have.ones, t.need.ones);
    total += min(cost[v], minV)*(x+y);
    t.have.zeros -= x;
    t.need.zeros -= x;
    t.have.ones -= y;
    t.need.ones -= y;
    return t;
}
ll solve() {
    ll total = 0;
    Y t = dfs(1, -1, 2e9, total);
    if (t.have.zeros == t.need.zeros && t.have.ones == t.need.ones) {
        return total;
    }
    return -1;
}
int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> cost[i] >> a[i] >> b[i];
    }
    for (int i = 1; i < n; i++) {
        int x,y;
        cin >> x >> y;
        vs[x].push_back(y);
        vs[y].push_back(x);
    }
    printf("%lld\n", solve());
    return 0;
}