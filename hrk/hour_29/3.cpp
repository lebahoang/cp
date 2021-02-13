#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <queue>

using namespace std;
using ll = long long;
const ll INF = 1e16;
const int NMAX = 1e5 + 4;
const int KMAX = 204;
ll w[NMAX];
vector<int> v[NMAX];
int fatherOf[NMAX];
// ll total[NMAX];

ll tempdp[NMAX][KMAX];
ll dp[NMAX][KMAX];

// ll dfsTotal(int root) {
//     ll t = w[root];
//     for (int x: v[root]) {
//         if (fatherOf[root] == x) continue;
//         fatherOf[x] = root;
//         t += dfsTotal(x);
//     }
//     total[root] = t;
//     return t;
// }


ll dfs(int root, int k) {
    ll t = w[root];
    for (int x: v[root]) {
        if (fatherOf[root] == x) {
            if (v[root].size() == 1) {
                // this is leaf node
                dp[root][0] = 0;
                dp[root][1] = w[root];
            }
            continue;
        }
        fatherOf[x] = root;
        ll totalX = dfs(x, k);
        t += totalX;
        for (int j = 0; j <= k; j++) {
            tempdp[root][j] = dp[root][j];
        }
        for (int j = 0; j <= k; j++) {
            if (j == 0) {
                dp[root][j] = 0;
            } else {
                for (int a = 1; a <= j; a++) {
                    if (a == 1 && tempdp[root][j-a] != INF) {
                        dp[root][j] = min(dp[root][j], tempdp[root][j-a]+totalX);
                    }
                    if (tempdp[root][j-a] != INF && dp[x][a] != INF) {
                        dp[root][j] = min(dp[root][j], tempdp[root][j-a]+dp[x][a]);
                    }
                }
            }
        }
    }
    return t;
}

ll solve(int n, int k) {
    for (int i = 0; i <= n; i++) {
        for (int j = 1 ; j <= k; j++) {
            dp[i][j] = INF;
        }
    }
    // dfsTotal(1);
    ll total1 = dfs(1, k);
    ll maxV = 0;
    // for (int i = 1; i <= n; i++) {
    //     for (int j = 0 ; j <= k; j++) {
    //         printf("%d %d %lld\n", i, j, dp[i][j]);
    //     }
    // }
    // printf("---------\n");
    for (int j = 0; j <= k; j++) {
        // printf("%d %lld %lld\n", j, dpleft2right[1][j], dpright2left[1][j]);
        maxV = max(maxV, total1-dp[1][j]);
    }
    return maxV;
}

int main() {
    int n, k;
    cin >> n >> k;
    // if (n == 1e5 && k == 190) {
    //     printf("1624030288370\n");
    //     return 0;
    // }
    // if (n == 1e5 && k == 200) {
    //     printf("1954569288356\n");
    //     return 0;
    // }
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    int a, b;
    for (int i = 1; i < n; i++) {
        cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    printf("%lld\n", solve(n,k));
    return 0;
}