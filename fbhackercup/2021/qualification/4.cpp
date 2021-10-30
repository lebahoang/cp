#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>
using namespace std;
struct LCA {
    vector<int> height, gold, euler, first, segtree;
    vector<int> leaves;
    vector<bool> visited;
    int n;

    LCA(vector<vector<int>> &adj, vector<int>& c, int root = 0) {
        n = adj.size();
        height.resize(n);
        gold.resize(n);
        first.resize(n);
        euler.reserve(n * 2);
        visited.assign(n, false);
        dfs(adj, c, root, 0, c[root]);
        int m = euler.size();
        segtree.resize(m * 4);
        build(1, 0, m - 1);
    };

    void dfs(vector<vector<int>> &adj, vector<int>& c, int node, int h = 0, int gold_val = 0) {
        if ((int)adj[node].size() == 1) leaves.push_back(node);
        visited[node] = true;
        height[node] = h;
        gold[node] = gold_val;
        first[node] = euler.size();
        euler.push_back(node);
        for (auto to : adj[node]) {
            if (!visited[to]) {
                dfs(adj, c, to, h + 1, gold_val+c[to]);
                euler.push_back(node);
            }
        }
    };

    void build(int node, int b, int e) {
        if (b == e) {
            segtree[node] = euler[b];
        } else {
            int mid = (b + e) / 2;
            build(node << 1, b, mid);
            build(node << 1 | 1, mid + 1, e);
            int l = segtree[node << 1], r = segtree[node << 1 | 1];
            segtree[node] = (height[l] < height[r]) ? l : r;
        }
    };

    int query(int node, int b, int e, int L, int R) {
        if (b > R || e < L)
            return -1;
        if (b >= L && e <= R)
            return segtree[node];
        int mid = (b + e) >> 1;

        int left = query(node << 1, b, mid, L, R);
        int right = query(node << 1 | 1, mid + 1, e, L, R);
        if (left == -1) return right;
        if (right == -1) return left;
        return height[left] < height[right] ? left : right;
    };

    int lca(int u, int v) {
        int left = first[u], right = first[v];
        if (left > right)
            swap(left, right);
        return query(1, 0, euler.size() - 1, left, right);
    };
};

int solve(int n, vector<int>& c, vector<vector<int>>& neighbor) {
    if (n == 1) return c[1];
    int root = 1;
    LCA obj{neighbor, c, root};
    int kk = 1;
    vector<vector<int>> dp((int)obj.leaves.size(), vector<int>(kk+1, 0));
    int rs = 0;
    for (int i = 0; i < (int)obj.leaves.size(); i++) {
        int l = obj.leaves[i];
        dp[i][0] = obj.gold[l];
        rs = max(rs, dp[i][0]);
    }
    for (int i = 1; i < (int)obj.leaves.size(); i++) {
        int l1 = obj.leaves[i];
        for (int k = 1; k <= kk; k++) {
            for (int j = 0; j < i; j++) {
                int l2 = obj.leaves[j];
                int lca = obj.lca(l1, l2);
                if (k == kk) {
                    if (lca == 1) {
                        dp[i][k] = max(dp[i][k], dp[j][k-1] + obj.gold[l1] - obj.gold[lca]);
                    }
                } else {
                    dp[i][k] = max(dp[i][k], dp[j][k-1] + obj.gold[l1] - obj.gold[lca]);
                }
            }
            rs = max(rs, dp[i][k]);
        }
    }
    return rs;
}


int main() {
    int t;
    cin >> t;
    for (int cs = 0; cs < t; cs++) {
        int n;
        cin >> n;
        vector<int> c(n+2, -1);
        for (int i = 1; i <= n; i++) cin >> c[i];
        vector<vector<int>> adj(n+2, vector<int>{});
        for (int i = 0; i < n-1; i++) {
            int x, y;
            cin >> x >> y;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        printf("Case #%d: %d\n", cs+1, solve(n, c, adj));
        
    }
    return 0;
}