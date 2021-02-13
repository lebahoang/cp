#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
#include <unordered_map>

using namespace std;
using ll = long long;
const int mod = 1e9+7;

// 0 red, 1 yellow, 2 green
int solve(int n) {
    int nstates = 12;
    int states[15][3] = {
        {0,1,0},
        {0,1,2},
        {0,2,0},
        {0,2,1},
        {1,0,1},
        {1,0,2},
        {1,2,0},
        {1,2,1},
        {2,0,1},
        {2,0,2},
        {2,1,0},
        {2,1,2}
    };
    vector<int> sTransition[15];
    for (int i = 0; i < nstates; i++) {
        for (int j = 0; j < nstates; j++) {
            if (i == j) continue;
            if (states[i][0] != states[j][0] && states[i][1] != states[j][1] && states[i][2] != states[j][2]) {
                sTransition[i].push_back(j);
            }
        }
    }
    ll dp[20];
    ll t[20];
    memset(dp, 0, sizeof(dp));
    memset(t, 0, sizeof(t));
    for (int i = 0; i < nstates; i++) dp[i] = 1;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < nstates; j++) {
            t[j] = 0;
            for (int k = 0; k < (int)sTransition[j].size(); k++) {
                t[j] = (t[j]%mod + dp[sTransition[j][k]]%mod)%mod;
            }
        }
        for (int j = 0; j < nstates; j++) {
            dp[j] = t[j];
        }
    }
    ll rs = 0;
    for (int j = 0; j < nstates; j++) {
        rs = (rs%mod + dp[j]%mod)%mod;
    }
    return (int)rs;
}
int main() {
    int n = 2;
    printf("%d\n", solve(n));
    n = 3;
    printf("%d\n", solve(n));
    n = 5000;
    printf("%d\n", solve(n));
    return 0;
}