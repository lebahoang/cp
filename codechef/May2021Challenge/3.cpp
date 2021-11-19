#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#include <string>
#include <set>
#include <map>
#include <unordered_map>
#include <vector>
#include <utility>

// g++ -std=c++14 -Wshadow -Wall -o s.out -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined 3.cpp && ./s.out < x.txt
using namespace std;
using ll = long long;
const ll mod = 1000000007;
vector<int> nodes[500001];
string vector2String(vector<int> a) {
    string x = "";
    for (int i: a) x += to_string(i) + " ";
    return x;
}
int child_2_nodes(int x) {
    return x*(x+1)/2;
}

ll dfs(int i, int parent) {
    vector<ll> s = {};
    for (int j: nodes[i]) {
        if (j == parent) continue;
        ll t = dfs(j, i);
        s.push_back(t);
    }
    sort(s.begin(), s.end());
    // for (auto j: s) {
    //     printf("I %d, n_child %d n_nodes %d\n", j.i, j.n_child, j.n_nodes);
    // }
    // printf("-----------\n");
    ll rs = 1;
    ll val = (ll)s.size();
    for (ll k: s) {
        rs += val * k;
        val--;
    }
    return rs;
}
ll solve(int n, ll x) {
    ll t = dfs(1, -1);
    ll rs = (t%mod * x%mod)%mod;
    return rs;
}
int main() {
    int t;
    cin >> t;
    for (int cs = 1; cs <= t; cs++) {
        int n;
        ll x;
        cin >> n >> x;
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            nodes[u].push_back(v);
            nodes[v].push_back(u);
        }
        printf("%lld\n", solve(n, x));
        for (int i = 1; i <= n; i++) nodes[i].clear();
    }
    return 0;
}