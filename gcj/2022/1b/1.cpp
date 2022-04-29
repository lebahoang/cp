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
// g++ -std=c++17 -Wshadow -Wall -o s.out -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined 1.cpp && ./s.out



int main() {
    int t;
    cin >> t;
    for (int cs = 1; cs <= t; cs++) {
        int n;
        cin >> n;
        vector<ll> d(n+1, 0);
        for (int i = 0; i < n; i++) cin >> d[i];
        vector<ll> maxPrefix(n, 0);
        for (int i = 0; i < n; i++) {
            if (i == 0) maxPrefix[i] = d[i];
            else maxPrefix[i] = max(maxPrefix[i-1], d[i]);
        }
        vector<ll> maxSuffix(n, 0);
        for (int i = n-1; i >= 0; i--) {
            if (i == n-1) maxSuffix[i] = d[i];
            else maxSuffix[i] = max(maxSuffix[i+1], d[i]);
        }

        vector<vector<ll>> dp(n, vector<ll>(n, 0));
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                int j = i+k;
                if (j >= n) continue;
                if (i == j) {
                    if (i == 0 && maxSuffix[i+1] <= d[i]) dp[i][j] = 1;
                    else if (i == n-1 && maxPrefix[i-1] <= d[i]) dp[i][j] = 1;
                    else if (i-1 >= 0 && i+1 < n && maxPrefix[i-1] <= d[i] && maxSuffix[i+1] <= d[i]) {
                        dp[i][j] = 1;
                    }
                } else {
                    bool f1 = false;
                    bool f2 = false;
                    bool f3 = false;
                    bool f4 = false;
                    if (i == 0 || (i-1 >= 0 && maxPrefix[i-1] <= d[i])) {
                        f1 = true;
                    }
                    if (j+1 == n || (j+1 < n && maxSuffix[j+1] <= d[i])) {
                        f2 = true;
                    }
                    if (f1 && f2) {
                        dp[i][j] = max(dp[i][j], dp[i+1][j] + 1);
                    } else {
                        dp[i][j] = max(dp[i][j], dp[i+1][j]);
                    }
                    if (i == 0 || (i-1 >= 0 && maxPrefix[i-1] <= d[j])) {
                        f3 = true;
                    }
                    if (j+1 == n || (j+1 < n && maxSuffix[j+1] <= d[j])) {
                        f4 = true;
                    }
                    if (f3 && f4) {
                        dp[i][j] = max(dp[i][j], dp[i][j-1] + 1);
                    } else {
                        dp[i][j] = max(dp[i][j], dp[i][j-1]);
                    }
                }
            }
        }
        printf("Case #%d: %lld\n", cs, dp[0][n-1]);
    }
    return 0;
}