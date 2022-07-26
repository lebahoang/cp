#include <cstdio>
#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>

using namespace std;
using ll = long long;

const int mod = 1e9 + 7;

ll dp[2000][50];
ll total[2000];

ll solve(vector<vector<int>>& hats) {
    memset(dp, 0, sizeof(dp));
    memset(total, 0, sizeof(total));
    int n = (int)hats.size();
    vector<vector<int>> h(50, vector<int>{});
    int nh = -1;
    for (int i = 0; i < (int)hats.size(); i++) {
        for (int j = 0; j < (int)hats[i].size(); j++) {
            h[hats[i][j]].push_back(i);
            if (nh < hats[i][j]) nh = hats[i][j];
        }
    }
    // for (int i = 1; i <= nh; i++) {
    //     bool c = false;
    //     for (int j = 0; j < h[i].size(); j++) {
    //         c = true;
    //         printf("%d ", h[i][j]);
    //     }
    //     if (c) {
    //         printf("\n%d\n", i);
    //         printf("--------\n");
    //     }
    // }
    for (int j = 1; j <= nh; j++) {
        for (int i = 1; i < (1<<n); i++) {
            for (int k = 0; k < h[j].size(); k++) {
                int x = h[j][k];
                if ((i & (1<<x)) != 0) {
                    int ii = i & (~(1<<x));
                    if (ii == 0) {
                        dp[i][j] = (dp[i][j]%mod + 1%mod)%mod;
                    } else {
                        dp[i][j] = (dp[i][j]%mod + total[ii]%mod)%mod;
                    }
                }
            }
            // printf("%d %d %lld, total %lld\n", i, j, dp[i][j], total[i]);
        }

        for (int i = 1; i < (1<<n); i++) {
            total[i] = (total[i]%mod + dp[i][j]%mod)%mod;
        }
    }
    return total[(1<<n)-1];
}
int main() {
    // vector<vector<int>> hats = {
    //     {3,4},{4,5},{5}
    // };
    vector<vector<int>> hats = {{3,5,1},{3,5}};
    // vector<vector<int>> hats = {
    //     {1,2,3,4},
    //     {1,2,3,4},
    //     {1,2,3,4},
    //     {1,2,3,4}
    // };
    printf("xxxxx %lld\n", solve(hats));
    return 0;
}