#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <utility>

// g++ -std=c++14 -O2 -o s.out 2.cpp && ./s.out < x.txt
// 1473
using namespace std;
int solve(vector<int>& houses, vector<vector<int>>& cost, int m, int n, int target) {
    int dp[104][104][30];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j <= target; j++) {
            for (int k = 0; k < n; k++) {
                dp[i][j][k] = 1e9;
            }
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 1; j <= target; j++) {
            for (int k = 0; k < n; k++) {
                if (i == 0) {
                    if (j == 1) {
                        if (houses[i] == 0) {
                            dp[i][j][k] = cost[i][k];
                        } else {
                            if (k+1 == houses[i]) dp[i][j][k] = 0;
                            else dp[i][j][k] = 1e9;
                        }
                    }
                    continue;
                }
                if (houses[i] == 0) {
                    dp[i][j][k] = min(dp[i][j][k], dp[i-1][j][k] + cost[i][k]);
                    for (int g = 0; g < n; g++) {
                        if (g != k) {
                            dp[i][j][k] = min(dp[i][j][k], dp[i-1][j-1][g] + cost[i][k]);
                        }
                    }
                } else {
                    if (k+1 != houses[i]) {
                        dp[i][j][k] = 1e9;
                    } else {
                        dp[i][j][k] = min(dp[i][j][k], dp[i-1][j][k]);
                        for (int g = 0; g < n; g++) {
                            if (g != k) {
                                dp[i][j][k] = min(dp[i][j][k], dp[i-1][j-1][g]);
                            }
                        }
                    }
                }
            }
        }
    }
    int rs = 1e9;
    for (int k = 0; k < n; k++) {
        rs = min(rs, dp[m-1][target][k]);
    }
    if (rs >= 1e9) return -1;
    return rs;
}
int main() {
    vector<int> houses = {0,0,0,0,0};
    vector<vector<int>> cost = {{1,10},{10,1},{10,1},{1,10},{5,1}};
    int m = 5;
    int n = 2;
    int target = 3;
    printf("%d\n", solve(houses, cost, m, n, target));
    return 0;
}