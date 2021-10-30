#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#include <string>
#include <set>
#include <map>
#include <unordered_map>
#include <vector>
#include <utility>

// g++ -std=c++14 -Wshadow -Wall -o s.out -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined 3.cpp && ./s.out < x.txt
using namespace std;
using ll = long long;
int solve(vector<int>& st) {
    int n = (int)st.size();
    vector<vector<int>> dp(n, vector<int>(2, 0));
    vector<int> prefix(n, 0);
    for (int i = 0; i < n; i++) {
        if (i == 0) prefix[i] = st[i];
        else prefix[i] = prefix[i-1]+st[i];
    }
    if (n == 2) return prefix[n-1];
    dp[n-1][0] = prefix[n-1];
    dp[n-1][1] = -prefix[n-1];
    // printf("dp[%d][0] %d, dp[%d][1] %d\n", n-1, dp[n-1][0], n-1, dp[n-1][1]);
    for (int i = n-2; i >= 1; i--) {
        dp[i][0] = max(dp[i+1][0], prefix[i]+dp[i+1][1]);
        dp[i][1] = min(dp[i+1][1], -prefix[i]+dp[i+1][0]);
        // printf("dp[%d][0] %d, dp[%d][1] %d\n", i, dp[i][0], i, dp[i][1]);
    }
    return dp[1][0];
}
int main() {
    // vector<int> st = {-1,2,-3,4,-5};
    vector<int> st = {7,-6,5,10,5,-2,-6};
    // vector<int> st = {-3,-5,3};
    printf("%d\n", solve(st));
    return 0;
}