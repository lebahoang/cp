#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <map>
#include <set>
using namespace std;
using ll = long long;
const int mod = 1e9+7;
// g++ -std=c++17 -Wshadow -Wall -o s.out -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined 3.cpp && ./s.out

struct F {
    ll s;
    ll val;
};

F dfs(int inode, vector<vector<int>>& nei, vector<ll>& f) {
    int n = nei[inode].size();
    if (n == 0) {
        // printf("INode %d, sum %lld val %lld\n", inode, (ll)0, f[inode]);
        return F{0, f[inode]};
    }
    
    ll totalSum = 0;
    ll totalV = 0;
    ll v = -1;
    for (int i = 0; i < n; i++) {
        F t = dfs(nei[inode][i], nei, f);
        if (v == -1 || v > t.val) {
            v = t.val;
        }
        totalSum += t.s;
        totalV += t.val;
    }
    ll sum = 0;
    if (n == 1) {
        sum = totalSum;
    } else {
        sum = totalSum + totalV - v;
    }
    ll inodeV = max(f[inode], v);
    // printf("INode %d, sum %lld val %lld\n", inode, sum, inodeV);
    return F{sum, inodeV};
}
int main() {
    int t;
    cin >> t;
    for (int cs = 1; cs <= t; cs++) {
        int n;
        cin >> n;
        vector<ll> f(n+5, 0);
        vector<vector<int>> nei(n+5, vector<int>{});
        for (int i = 1; i <= n; i++) cin >> f[i];
        int root = 0;
        int x;
        for (int i = 1; i <= n; i++) {
            cin >> x;
            nei[x].push_back(i);
        }
        F rs = dfs(root, nei, f);
        printf("Case #%d: %lld\n", cs, rs.s + rs.val);
    }
    return 0;
}