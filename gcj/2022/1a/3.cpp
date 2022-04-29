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

int go(int i, int j, int e, int w, vector<vector<int>>& es, vector<vector<int>>& common, vector<vector<int>>& dp) {
    if (dp[i][j] < 1e9) return dp[i][j];
    if (i == j) {
        dp[i][j] = 2*common[i][j];
        return dp[i][j];
    }
    for (int k = i; k < j; k++) {
        dp[i][j] = min(dp[i][j], go(i,k,e,w,es,common,dp) + go(k+1,j,e,w,es,common,dp));
    }
    dp[i][j] -= 2*common[i][j];
    return dp[i][j];
}

int main() {
    int t;
    cin >> t;
    for (int cs = 1; cs <= t; cs++) {
        int e, w;
        cin >> e >> w;
        vector<vector<int>> es(e, vector<int>(w, 0));
        for (int i = 0; i < e; i++) {
            for (int j = 0; j < w; j++) {
                cin >> es[i][j];
            }
        }
        vector<vector<vector<int>>> wcommon(w, vector<vector<int>>(e, vector<int>(e, 0)));
        vector<vector<int>> common(e, vector<int>(e, 0));
        vector<vector<int>> dp(e, vector<int>(e, 1e9));
        for (int k = 0; k < w; k++) {
            for (int i = 0; i < e; i++) {
                wcommon[k][i][i] = es[i][k];
                for (int j = i+1; j < e; j++) {
                    wcommon[k][i][j] = min(wcommon[k][i][j-1], es[j][k]);
                }
            }
        }
        for (int i = 0; i < e; i++) {
            for (int j = i; j < e; j++) {
                for (int k = 0; k < w; k++) {
                    common[i][j] += wcommon[k][i][j];
                }
                // printf("common[%d][%d]: %d\n", i, j, common[i][j]);
            }
        }
        go(0, e-1, e, w, es, common, dp);
        // for (int i = 0; i < e; i++) {
        //     for (int j = i; j < e; j++) {
        //         printf("dp[%d][%d] %d\n", i, j, dp[i][j]);
        //     }
        // }
        printf("Case #%d: %d\n", cs, dp[0][e-1]);
    }
    return 0;
}