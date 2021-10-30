#include <cstdio>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>
using namespace std;

// g++ -std=c++14 -Wshadow -Wall -O2 -o s.out -g -fsanitize=address -fsanitize=undefined 5.cpp && ./s.out < x.txt
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

// int solve(int n, int kk, vector<int>& c, vector<vector<int>>& neighbor) {
//     if (kk == 0 || n == 1) return c[1];
//     int root = 1;
//     LCA obj{neighbor, c, root};
//     int m = (int)obj.leaves.size();
//     vector<vector<vector<int>>> dp(m, vector<vector<int>>(kk+1, vector<int>(n+2, -1)));
//     int rs = 0;

//     if (kk == 1 || m <= 2) {
//         for (int i = 0; i < m; i++) {
//             rs = max(rs, obj.gold[obj.leaves[i]]);
//             for (int i_prev = i-1; i_prev >= 0; i_prev--) {
//                 int l = obj.lca(obj.leaves[i], obj.leaves[i_prev]);
//                 if (l == 1) {
//                     rs = max(rs, obj.gold[obj.leaves[i]] + obj.gold[obj.leaves[i_prev]] - c[1]);
//                 }
//             }
//         }
//         return rs;
//     }
//     printf("M %d\n", m);

//     for (int i = 0; i < m; i++) {
//         int node_i = obj.leaves[i];
//         for (int k = 1; k <= kk; k++) {
//             for (int j = i-1; j >= 0; j--) {
//                 int node_j = obj.leaves[j];
//                 int lca_ij = obj.lca(node_i, node_j);
//                 if (k < kk) {
//                     for (int i_prev = j-1; i_prev >= 0; i_prev--) {
//                         int node_i_prev = obj.leaves[i_prev];
//                         int lca_j_iprev = obj.lca(node_j, node_i_prev);
//                         if (k == 1) {
//                             int lca_i_iprev = obj.lca(node_i, node_i_prev);
//                             if (lca_j_iprev == lca_i_iprev) {
//                                 if (lca_i_iprev == lca_ij) {
//                                     dp[i][k][lca_ij] = max(dp[i][k][lca_ij], 
//                                                            obj.gold[node_i_prev] + obj.gold[node_j] - obj.gold[lca_ij] + obj.gold[node_i] - obj.gold[lca_ij]);
//                                 } else {
//                                     dp[i][k][lca_ij] = max(dp[i][k][lca_ij], 
//                                                            obj.gold[node_i_prev] + obj.gold[node_j] - obj.gold[lca_ij] + obj.gold[node_i] - obj.gold[lca_ij] + c[lca_ij]);
//                                 }    
//                             } else {
//                                 dp[i][k][lca_ij] = max(dp[i][k][lca_ij], obj.gold[node_i_prev] + c[node_i]); 
//                             }
//                         } else {
//                             for (int lca_i_prev = 1; lca_i_prev <= n; lca_i_prev++) {
//                                 if (obj.lca(lca_i_prev, node_i_prev) != lca_i_prev) continue;
//                                 if (dp[i_prev][k-1][lca_i_prev] == -1) continue;
//                                 int x = obj.lca(lca_i_prev, node_j);
//                                 if (lca_ij != x && x == lca_i_prev && lca_ij != lca_j_iprev) {
//                                     dp[i][k][lca_ij] = max(dp[i][k][lca_ij], dp[i_prev][k-1][lca_i_prev] + c[node_i]);
//                                 } else {
//                                     if (lca_ij == lca_j_iprev) {
//                                         // printf("%d %d %d %d\n", lca_j_iprev, lca_i_prev, node_j, x);
//                                         // assert(lca_j_iprev == lca_i_prev);
//                                         // assert(lca_i_prev == x);
//                                         dp[i][k][lca_ij] = max(dp[i][k][lca_ij], 
//                                                             dp[i_prev][k-1][lca_i_prev] + obj.gold[node_j] - obj.gold[lca_ij] + obj.gold[node_i] - obj.gold[lca_ij]);
//                                     } else {
//                                         dp[i][k][lca_ij] = max(dp[i][k][lca_ij], 
//                                                             dp[i_prev][k-1][lca_i_prev] + obj.gold[node_j] - obj.gold[lca_ij] + obj.gold[node_i] - obj.gold[lca_ij] + c[lca_ij]);
//                                     }
//                                 }
                                
//                             }
//                         }    
//                     }
//                 } else {
//                     for (int lca_j = 1; lca_j <= n; lca_j++) {
//                         if (dp[j][k-1][lca_j] == -1) continue;
//                         int x = obj.lca(lca_j, node_i);
//                         if (x != 1) continue;
//                         dp[i][k][lca_ij] = max(dp[i][k][lca_ij], 
//                                                dp[j][k-1][lca_j] + obj.gold[node_i] -  c[1]);
//                     }
//                 }
                
//                 printf("dp[%d][%d][%d]: %d\n", node_i, k, lca_ij, dp[i][k][lca_ij]);
//                 rs = max(rs, dp[i][k][lca_ij]);
//             }
//         }
//     }

//     return rs;
// }

void find_parent_and_leaves(int i, vector<int>& parent, vector<int>& leaves, vector<vector<int>>& neighbor) {
    if ((int)neighbor[i].size() == 1 && i != 1) {
        leaves.push_back(i);
    }
    for (int j: neighbor[i]) {
        if (j == parent[i]) continue;
        parent[j] = i;
        find_parent_and_leaves(j, parent, leaves, neighbor);
    }
}

void dfs(int i, int k, int K, vector<int>& c, vector<int>& parent, vector<vector<int>>& neighbor, vector<vector<vector<vector<int>>>>& dp) {
    int szi = (int)neighbor[i].size();
    if (i != 1) szi--;
    if (dp[i][szi][k][0] != -1e8 && dp[i][szi][k][1] != -1e8 && dp[i][szi][k][2] != -1e8 && dp[i][szi][k][3] != -1e8) {
        return;
    }
    vector<int> nn = {};
    for (int j: neighbor[i]) {
        if (j != parent[i]) {
            nn.push_back(j);
            for (int kk = 0; kk <= K; kk++) {
                dfs(j, kk, K, c, parent, neighbor, dp);
            }
        }
    }

    for (int f = 1; f <= (int)nn.size(); f++) {
        int child_f = nn[f-1];
        int szf = (int)neighbor[child_f].size()-1;
        if (f == 1) {
            dp[i][f][k][0] = max({dp[i][f][k][0],
                                  dp[child_f][szf][k][0],
                                  dp[child_f][szf][k][1],
                                  dp[child_f][szf][k][2],
                                  dp[child_f][szf][k][4],
                                  dp[child_f][szf][k][5]});
            if (k-1 >= 0) {
                dp[i][f][k][1] = max({dp[i][f][k][1],
                                  dp[child_f][szf][k-1][0] + c[i],
                                  dp[child_f][szf][k-1][1] + c[i],
                                  dp[child_f][szf][k-1][2] + c[i],
                                  dp[child_f][szf][k-1][4] + c[i],
                                  dp[child_f][szf][k-1][5] + c[i],
                                  });
            }
            dp[i][f][k][2] = max({dp[i][f][k][2],
                                  dp[child_f][szf][k][1] + c[i],
                                  dp[child_f][szf][k][2] + c[i],
                                  dp[child_f][szf][k][4] + c[i],
                                  });
            dp[i][f][k][3] = max({dp[i][f][k][3],
                                  dp[child_f][szf][k][1] + c[i],
                                  dp[child_f][szf][k][2] + c[i],
                                  dp[child_f][szf][k][4] + c[i]});
            printf("dp[%d][%d][%d][%d] %d\n", i, f, k, 0, dp[i][f][k][0]);
            printf("dp[%d][%d][%d][%d] %d\n", i, f, k, 1, dp[i][f][k][1]);
            printf("dp[%d][%d][%d][%d] %d\n", i, f, k, 2, dp[i][f][k][2]);
            printf("dp[%d][%d][%d][%d] %d\n", i, f, k, 3, dp[i][f][k][3]);
        } else {
            for (int kk = 0; kk <= k; kk++) {
                dp[i][f][k][0] = max({dp[i][f][k][0],
                                      dp[i][f-1][k-kk][0] + dp[child_f][szf][kk][0],
                                      dp[i][f-1][k-kk][0] + dp[child_f][szf][kk][1],
                                      dp[i][f-1][k-kk][0] + dp[child_f][szf][kk][2],
                                      dp[i][f-1][k-kk][0] + dp[child_f][szf][kk][4]});
                if (k-kk-1 >= 0) {
                    dp[i][f][k][1] = max({dp[i][f][k][1],
                                          dp[i][f-1][k-kk-1][0] + dp[child_f][szf][kk][0] + c[i],
                                          dp[i][f-1][k-kk-1][0] + dp[child_f][szf][kk][1] + c[i],
                                          dp[i][f-1][k-kk-1][0] + dp[child_f][szf][kk][2] + c[i],
                                          dp[i][f-1][k-kk-1][0] + dp[child_f][szf][kk][4] + c[i]});
                }
                if (kk-1 >= 0) {
                    dp[i][f][k][1] = max({dp[i][f][k][1],
                                          dp[i][f-1][k-kk][0] + dp[child_f][szf][kk-1][0] + c[i],
                                          dp[i][f-1][k-kk][0] + dp[child_f][szf][kk-1][1] + c[i],
                                          dp[i][f-1][k-kk][0] + dp[child_f][szf][kk-1][2] + c[i],
                                          dp[i][f-1][k-kk][0] + dp[child_f][szf][kk-1][4] + c[i]});
                }
                dp[i][f][k][1] = max({dp[i][f][k][1],
                                      dp[i][f-1][k-kk][1] + dp[child_f][szf][kk][0],
                                      dp[i][f-1][k-kk][1] + dp[child_f][szf][kk][1],
                                      dp[i][f-1][k-kk][1] + dp[child_f][szf][kk][2],
                                      dp[i][f-1][k-kk][1] + dp[child_f][szf][kk][4],
                                      dp[i][f-1][k-kk][1] + dp[child_f][szf][kk][5]});
                dp[i][f][k][2] = max({dp[i][f][k][2],
                                      dp[i][f-1][k-kk][0] + dp[child_f][szf][kk][1] + c[i],
                                      dp[i][f-1][k-kk][0] + dp[child_f][szf][kk][2] + c[i],
                                      dp[i][f-1][k-kk][0] + dp[child_f][szf][kk][4] + c[i],
                                      dp[i][f-1][k-kk][2] + dp[child_f][szf][kk][0],
                                      dp[i][f-1][k-kk][2] + dp[child_f][szf][kk][1],
                                      dp[i][f-1][k-kk][2] + dp[child_f][szf][kk][2],
                                      dp[i][f-1][k-kk][2] + dp[child_f][szf][kk][4],
                                      dp[i][f-1][k-kk][2] + dp[child_f][szf][kk][5]});
                dp[i][f][k][3] = max({dp[i][f][k][3],
                                      dp[i][f-1][k-kk][3] + dp[child_f][szf][kk][1],
                                      dp[i][f-1][k-kk][3] + dp[child_f][szf][kk][2],
                                      dp[i][f-1][k-kk][3] + dp[child_f][szf][kk][4]});
            }

            int x = -1;
            if (f%2 == 0) {
                x = (f/2-1) + 2;
            } else {
                x = (f-1)/2 + 1;
            }
            for (int kk = 0; kk <= k-x+f; kk++) {
                dp[i][f][k][4] = max({dp[i][f][k][4],
                                      dp[i][f-1][k-x+f-kk][3] + dp[child_f][szf][kk][1],
                                      dp[i][f-1][k-x+f-kk][3] + dp[child_f][szf][kk][2],
                                      dp[i][f-1][k-x+f-kk][3] + dp[child_f][szf][kk][4],
                                    });
            }
            if (f%2 == 0) {
                x = f/2;
            } else {
                x = (f-1)/2 + 1;
            }
            for (int kk = 0; kk <= k-x+f; kk++) {
                dp[i][f][k][5] = max({dp[i][f][k][5],
                                      dp[i][f-1][k-x+f-kk][3] + dp[child_f][szf][kk][1],
                                      dp[i][f-1][k-x+f-kk][3] + dp[child_f][szf][kk][2],
                                      dp[i][f-1][k-x+f-kk][3] + dp[child_f][szf][kk][4],
                                    });
            }
            printf("dp[%d][%d][%d][%d] %d\n", i, f, k, 0, dp[i][f][k][0]);
            printf("dp[%d][%d][%d][%d] %d\n", i, f, k, 1, dp[i][f][k][1]);
            printf("dp[%d][%d][%d][%d] %d\n", i, f, k, 2, dp[i][f][k][2]);
            printf("dp[%d][%d][%d][%d] %d\n", i, f, k, 3, dp[i][f][k][3]);
            printf("dp[%d][%d][%d][%d] %d\n", i, f, k, 4, dp[i][f][k][4]);
            printf("dp[%d][%d][%d][%d] %d\n", i, f, k, 5, dp[i][f][k][5]);
        }
        
    }
    
}

int solve(int n, int kk, vector<int>& parent, vector<int>& leaves, vector<int>& c, vector<vector<int>>& neighbor) {
    parent[1] = -1;
    find_parent_and_leaves(1, parent, leaves, neighbor);
    if (kk == 0 || n == 1) return c[1];
    vector<vector<vector<vector<int>>>> dp(n+3, vector<vector<vector<int>>>(
        n+3, vector<vector<int>>(kk+3, vector<int>(10, -1e8))
    ));
    for (int i: leaves) {
        dp[i][0][1][1] = c[i];
        dp[i][0][0][0] = 0;
        dp[i][0][0][2] = -1e9;
        dp[i][0][0][3] = -1e9;
        dp[i][0][0][4] = -1e9;
        dp[i][0][0][5] = -1e9;

    }
    int rs = -1;
    int sz_root = (int)neighbor[1].size();
    for (int k = 0; k <= kk; k++) {
        dfs(1, k, kk, c, parent, neighbor, dp);
        rs = max({rs, dp[1][sz_root][k][1], dp[1][sz_root][k][2], dp[1][sz_root][k][4], dp[1][sz_root][k][5]});
    }
    // printf("jjjj %d\n", dp[1][2][2][2]);
    // printf("jjjj %d\n", dp[1][2][1][2]);
    // printf("jjjj %d %d %d\n", dp[8][2][1][1], dp[8][2][1][2], dp[8][2][1][3]);
    return rs;
}


int main() {
    int t;
    cin >> t;
    for (int cs = 0; cs < t; cs++) {
        int n, k;
        cin >> n >> k;
        vector<int> c(n+2, -1);
        vector<int> parent(n+2, -1);
        vector<int> leaves = {};
        for (int i = 1; i <= n; i++) cin >> c[i];
        vector<vector<int>> adj(n+2, vector<int>{});
        for (int i = 0; i < n-1; i++) {
            int x, y;
            cin >> x >> y;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        for (int i = 1; i <= n; i++) {
            sort(adj[i].begin(), adj[i].end());
        }
        int rs = solve(n, k, parent, leaves, c, adj);
        printf("Case #%d: %d\n", cs+1, rs);
    }
    return 0;
}
