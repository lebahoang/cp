#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <map>
#include <stack>
#include <queue>
#include <vector>
#include <utility>

// g++ -std=c++14 -stdlib=libc++ -O2 -o s.out 3.cpp && ./s.out < x.txt
using namespace std;
using ll = long long;
const int nax = 3e5 + 7;
const ll mod = 1l << 32;
vector<int> e[nax];
vector<ll> w = {0};
int parent[nax];
map<pair<int, int>, ll> m; 

void findParent(int node, int parentOfNode) {
    for (int x: e[node]) {
        if (x == parentOfNode) continue;
        // printf("node %d x %d\n", node, x);
        parent[x] = node;
        findParent(x, node);
    }
}
ll dfs(int u, int v) {
    if (u > v) {
        ll t = v;
        v = u;
        u = t;
    }
    auto it = m.find({u, v});
    if (it != m.end()) {
        return it->second;
    }
    if (u == -1 && v == -1) {
        return 0;
    }
    ll x = dfs(parent[u], parent[v]);
    ll rs = (x + (w[u]%mod * w[v]%mod)%mod)%mod;
    m[{u, v}] = rs;
    return rs;
}
int main() {
    int n, q;
    cin >> n >> q;
    ll weight = 0;
    for (int i = 1; i <= n; i++) {
        cin >> weight;
        w.push_back(weight);
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    // for (int i = 1; i <= n; i++) {
    //     printf("I %d\n", i);
    //     for (auto x: e[i]) {
    //         printf("%d ", x);
    //     }
    //     printf("\n");
    // }
    parent[1] = -1;
    findParent(1, -1);
    ll u = -1;
    ll v = -1;
    for (int i = 0; i < q; i++) {
        cin >> u >> v;
        printf("%lld\n", dfs(u, v));
    }
    return 0;
}