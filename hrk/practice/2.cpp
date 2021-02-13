#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;
using ll = unsigned long long;

// const int mod = 1e9 + 9;
// const int NMAX = 5005;
// ll dp[NMAX];
// ll c[NMAX][NMAX];
// ll totalUpTo[NMAX];

// void countTrees() {
//     int n = 5000;
//     dp[0] = 1;
//     dp[1] = 1;
//     for (int i = 2; i <= n; i++) {
//         for (int j = 0; j <= i-1; j++) {
//             int k = i-1-j;
//             dp[i] = (dp[i]%mod + (dp[j]%mod*dp[k]%mod)%mod)%mod;
//         }
//        // printf("%d, %lld\n", i, dp[i]);
//     }
// }

// void calculateC() {
//     int n = 5000;
//     c[1][0] = 1;
//     c[1][1] = 1;
//     for (int i = 2; i <= n; i++) {
//         c[i][0] = 1;
//         c[i][i] = 1;
//         for (int j = 1; j < i; j++) {
//             c[i][j] = (c[i-1][j-1]%mod + c[i-1][j]%mod)%mod;
//         }
//     }
// }

// void countTotal() {
//     int n = 5000;
//     for (int i = 1; i <= n; i++) {
//         ll total = 0;
//         for (int j = 1; j <= i; j++) {
//             ll sets = c[i][j];
//             total = (total%mod + (sets%mod*dp[j]%mod)%mod)%mod;
//         }
//         totalUpTo[i] = total;
//         // printf("%d, %lld\n", i, totalUpTo[i]);
//     }
// }
// detect bipartie, return true if bipartie graph
// bool dfs1(vector<vector<int>>& v, vector<int>& colors, vector<int>& visited, int i, int parent) {
//     for (int j = 0; j < v[i].size(); j++) {
//         int k = v[i][j];
//         if (visited[k] == 0) {
//             visited[k] = 1;
//             colors[k] = 1-colors[i];
//             if (!dfs1(v, colors, visited, k, i)) {
//                 return false;
//             }
//         } else if (colors[k] == colors[i] && k != parent) {
//             return false;
//         }
//     }
//     return true;
// }


// // detect cycle, return true if cycled
// bool dfs2(vector<vector<int>>& v, vector<int>& visited, int& l, int i, int parent) {
//     printf("i %d parent %d\n", i, parent);
//     for (int j = 0; j < v[i].size(); j++) {
//         int k = v[i][j];
//         if (visited[k] == 0) {
//             visited[k] = 1;
//             l++;
//             if(dfs2(v, visited, l, k, i)) return true;
//             l--;
//         } else if (k != parent) {
//             return true;
//         }
//     }
//     return false;
// }

// bool solve(int n, vector<vector<int>>& d) {
//     vector<vector<int>> v(n+2, vector<int>{});
//     for (int i = 0; i < d.size(); i++) {
//         int a = d[i][0];
//         int b = d[i][1];
//         v[a].push_back(b);
//         v[b].push_back(a);
//     }
//     vector<int> colors(n+2, -1);
//     vector<int> visited1(n+2, 0);
//     bool f1 = false;
//     for (int i = 1; i <= n; i++) {
//         if (visited1[i] == 1) continue;
//         visited1[i] = 1;
//         colors[1] = 0;
//         f1 = dfs1(v, colors, visited1, i, -1);
//     }
//     printf("f1 %d\n", f1);
//     if (!f1) return false;

//     vector<int> visited2(n+2, 0);
//     bool f2 = false;
//     for (int i = 1; i <= n; i++) {
//         if (visited2[i] == 1) continue;
//         visited2[i] = 1;
//         int l = 1;
//         f2 = dfs2(v, visited2, l, i, -1);
//         printf("f2 loop %d i %d l %d\n", f2, i, l);
//         if (f2 && (l == 1 || l%2 == 0)) f2 = false;
//     }
//     printf("f2 %d\n", f2);
//     if (!f2) return true;
//     return false;
// }

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
};

void dfs(TreeNode* root, int& a, int& b, int& c, int& isLeaf) {
    if (root->left == NULL && root->right == NULL) {
        a = 0;
        b = 1;
        c = 0;
        isLeaf = 1;
        // printf("node %d a %d b %d c %d\n", root->val, a, b, c);
        return;
    }
    int x1 = -1, y1 = -1, t1 = 0, z1 = -1, x2 = -1, y2 = -1, t2 = 0, z2 = -1;
    if (root->left != NULL) {
        dfs(root->left, x1, y1, t1, z1);
    }
    if (root->right != NULL) {
        dfs(root->right, x2, y2, t2, z2);
    }
    int x11 = 0, x22 = 0;
    if (z1 == 1) x11 = 1;
    if (z2 == 1) x22 = 1;
    if (x1 == -1 && y1 == -1) {
        a = y2;
        if (z2 == 1) c = a;
        else c = x2;
        b = min({x2, y2, t2}) + 1;
    } else if (x2 == -1 && y2 == -1) {
        a = y1;
        if (z1 == 1) c = a;
        else c = x1;
        b = min({x1, y1, t1}) + 1;
    } else {
        a = min({x1+y2+x11, x2+y1+x22, y1+y2});
        // c = min({a, x1+x11+x2+x22});
        c = x1+x11+x2+x22;
        // b = min({y1+y2, x2+y1, x1+x2, x1+y2, t1+t2})+1;
        b = min({x1,y1,t1}) + min({x2,y2,t2}) + 1;
    }
    // printf("%d %d %d %d node %d a %d b %d c %d\n", x1, y1, x2, y2, root->val, a, b, c);
    return;
}
int main() {
    // calculateC();
    // countTrees();
    // countTotal();
    // int t, n;
    // cin >> t;
    // for (int cc = 0; cc < t; cc++) {
    //     cin >> n;
    //     printf("%lld\n", totalUpTo[n]);
    // }
    // int n = 4;
    // vector<vector<int>> d = {{1,2},{1,3},{2,4}};
    // vector<vector<int>> d = {{1,2},{2,3},{3,4},{4,5},{1,5}};
    // vector<vector<int>> d = {{1,2},{2,3},{3,4}, {4,1}};
    // bool rs = solve(n, d);
    // if (rs) printf("true\n");
    // else printf("false\n");


    // TreeNode* root = new TreeNode{1, NULL, NULL};
    // TreeNode* a = new TreeNode{2, NULL, NULL};
    // TreeNode* b = new TreeNode{3, NULL, NULL};
    // TreeNode* c = new TreeNode{4, NULL, NULL};
    // TreeNode* d = new TreeNode{5, NULL, NULL};
    // TreeNode* e = new TreeNode{6, NULL, NULL};
    // TreeNode* f = new TreeNode{7, NULL, NULL};
    // TreeNode* g = new TreeNode{8, NULL, NULL};
    // root->left = a;
    // root->right = b;
    // a->left = e;
    // b->left = c;
    // b->right = d;
    // c->left = f;
    // d->left = g;


    // TreeNode* root = new TreeNode{1, NULL, NULL};
    // TreeNode* a = new TreeNode{2, NULL, NULL};
    // TreeNode* b = new TreeNode{3, NULL, NULL};
    // TreeNode* c = new TreeNode{4, NULL, NULL};
    // TreeNode* d = new TreeNode{5, NULL, NULL};
    // TreeNode* e = new TreeNode{6, NULL, NULL};
    // root->left = a;
    // a->left = b;
    // b->left = c;
    // c->left = d;
    // d->left = e;


    TreeNode* root = new TreeNode{1, NULL, NULL};
    TreeNode* a = new TreeNode{2, NULL, NULL};
    TreeNode* b = new TreeNode{3, NULL, NULL};
    TreeNode* c = new TreeNode{4, NULL, NULL};
    TreeNode* d = new TreeNode{5, NULL, NULL};
    TreeNode* e = new TreeNode{6, NULL, NULL};
    root->left = a;
    root->right = b;
    a->right = c;
    c->right = d;
    b->right = e;

    if (root->left == NULL && root->right == NULL) {
        printf("1\n");
    } else {
        int x = 0, y = 0, z = 0, isLeaf = 0;
        dfs(root, x, y, z, isLeaf);
        printf("%d\n", min(x,y));
    }
    
    return 0;
}