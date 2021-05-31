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
    dp[1][0] = prefix[1];
    dp[1][1] = 1e9+9;
    for (int i = 2; i < n; i++) {
        if (dp[i-1][1] < 1e9) {
            dp[i][0] = max(dp[i-1][0]+st[i], dp[i-1][1]+prefix[i]);
        } else {
            dp[i][0] = dp[i-1][0]+st[i];
        }
            
        dp[i][1] = min(dp[i-1][1]-st[i], dp[i-1][0]-prefix[i]);
        dp[i][0] = max(dp[i][0], prefix[i]);
    }
    for(int i = 1; i < n; i++) printf("dp[%d][0] %d, dp[%d][1] %d\n", i, dp[i][0], i, dp[i][1]);
    return max(dp[n-1][0], dp[n-1][1]);
}
int main() {
    vector<int> st = {-1,2,-3,4,-5};
    printf("%d\n", solve(st));
    return 0;
}