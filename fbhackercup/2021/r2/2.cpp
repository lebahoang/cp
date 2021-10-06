#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
using namespace std;
// g++ -std=c++14 -Wshadow -Wall -o s.out -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined 2.cpp && ./s.out

struct LCA {
    vector<int> height, euler, first, segtree;
    vector<int> leaves;
    vector<bool> visited;
    int n;

    LCA(vector<vector<int>> &adj, int root = 0) {
        n = adj.size();
        height.resize(n);
        first.resize(n);
        euler.reserve(n * 2);
        visited.assign(n, false);
        dfs(adj, root, 0);
        int m = euler.size();
        segtree.resize(m * 4);
        build(1, 0, m - 1);
    };

    void dfs(vector<vector<int>> &adj, int node, int h = 0) {
        if ((int)adj[node].size() == 1) leaves.push_back(node);
        visited[node] = true;
        height[node] = h;
        first[node] = euler.size();
        euler.push_back(node);
        for (auto to : adj[node]) {
            if (!visited[to]) {
                dfs(adj, to, h + 1);
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

int dfs(int i, int parent, vector<int>& node_sum, vector<vector<int>>& adj) {
    int sum = 0;
    sum++;
    for (int j: adj[i]) {
        if (j == parent) continue;
        int s = dfs(j, i, node_sum, adj);
        sum += s;
    }
    node_sum[i] += sum;
    return node_sum[i];
}
int solve(int n, vector<vector<int>>& adj, vector<int>& fs) {
    LCA obj = LCA(adj, 1);
    unordered_map<int, vector<int>> m;
    for (int i = 1; i <= n; i++) {
        if (m.find(fs[i]) == m.end()) {
            m[fs[i]] = {i};
        } else {
            m[fs[i]].push_back(i);
        }
    }
    vector<int> node_sum(n+3, 0);
    for (auto i = m.begin(); i != m.end(); i++) {
        if (i->second.size() > 1) {
            int t = obj.lca(i->second[0], i->second[1]);
            for (int j = 2; j < (int)i->second.size(); j++) {
                t = obj.lca(t, i->second[j]);
            }
            int k = (int)(-i->second.size());
            node_sum[t] += k; 
            // printf("LCA process node %d %d\n", t, node_sum[t]);
        } else {
            node_sum[i->second[0]] += -1;
            // printf("LCA process node %d %d\n", i->second[0], node_sum[i->second[0]]);
        }
    }
    dfs(1, -1, node_sum, adj);
    int rs = 0;
    for (int i = 1; i <= n; i++) {
        // printf("i %d, %d\n", i, node_sum[i]);
        if (node_sum[i] == 0 && i != 1) rs++;
    }
    return rs;
}
int main() {
    int t;
    cin >> t;
    for (int cs = 1; cs <= t; cs++) {
        int n;
        cin >> n;
        vector<vector<int>> adj(n+3, vector<int>{});
        int a, b;
        for (int i = 1; i < n; i++) {
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        vector<int> fs(n+3, 0);
        for (int i = 1; i <= n; i++) cin >> fs[i];
        printf("Case #%d: %d\n", cs, solve(n, adj, fs));
    }
    return 0;
}