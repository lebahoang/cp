#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

// Write any include statements here
void propagate1(int i, int val, vector<int>& L, vector<int>& dp) {
    dp[i] = val;
    int j = L[i];
    while (j != i) {
        dp[j] = val;
        j = L[j];
    }
}

int propagate2(int i, vector<int>& L, vector<int>& dp) {
    if (dp[i] != -1) {
        return dp[i];
    }
    dp[i] = propagate2(L[i], L, dp) + 1;
    return dp[i];
}

int dfs(int i, int cur, vector<int>& L, vector<int>& dist, vector<int>& dp, int& val) {
    if (dp[i] > -1) {
        return i;
    }
    if (dist[L[i]] > 0) {
        val = cur - dist[L[i]] + 1;
        return L[i];
    }
    dist[i] = cur;
    return dfs(L[i], cur+1, L, dist, dp, val);
}
int getMaxVisitableWebpages(int N, vector<int> L) {
    // Write your code here
    L.insert(L.begin(), 0);
    vector<int> dp(N+5, -1);
    vector<int> dist(N+5, 0);
    int val = -1;
    int rs = -1;
    for (int i = 1; i <= N; i++) {
        if (dp[i] > -1) {
            printf("dp[%d] = %d\n", i, dp[i]);
            rs = max(rs, dp[i]);
            continue;
        }
        int ind = dfs(i, 1, L, dist, dp, val);
        if (dp[ind] == -1) {
            propagate1(ind, val, L, dp);
        }
        if (i != ind) {
            propagate2(i, L, dp);
        }
        rs = max(rs, dp[i]);
        printf("dp[%d] = %d\n", i, dp[i]);
    }
    return rs;
}

int main() {
    // int N = 4;
    // vector<int> L = {4,1,2,1};
    int N = 9;
    vector<int> L = {4,3,5,7,2,1,6,7,8};
    printf("%d\n", getMaxVisitableWebpages(N, L));
    return 0;
}
