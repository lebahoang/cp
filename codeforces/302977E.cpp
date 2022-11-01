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
const ll mod = 1e9+7;

// For test speed: g++ -std=c++17 -Wall -lm -O2 -o s.out 302977E.cpp && time ./s.out < x.txt
// g++ -std=c++17 -Wshadow -Wall -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined -o s.out 302977E.cpp && ./s.out < x.txt

int main() {
    int n;
    cin >> n;
    int k;
    cin >> k;
    ll office;
    cin >> office;
    vector<ll> p(n, 0);
    vector<ll> keys(k, 0);
    vector<vector<ll>> dp(n, vector<ll>(k, 1e13));
    for (int i = 0; i < n; i++) cin >> p[i];
    for (int i = 0; i < k; i++) cin >> keys[i];
    sort(p.begin(), p.end());
    sort(keys.begin(), keys.end());
    for (int i = 0; i < k; i++) {
        if (i == 0) {
            dp[0][i] = abs(keys[i] - p[0]) + abs(office-keys[i]);
        } else {
            dp[0][i] = min(abs(keys[i] - p[0]) + abs(office-keys[i]), dp[0][i-1]);
        }
        // printf("dp[%d][%d] %lld\n", 0, i, dp[0][i]);
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < k; j++) {
            if (j < i) continue;
            ll t = max(abs(keys[j] - p[i]) + abs(office-keys[j]), dp[i-1][j-1]);
            dp[i][j] = min(t, dp[i][j-1]);
            // printf("dp[%d][%d] %lld\n", i, j, dp[i][j]);
        }
    }
    printf("%lld\n", dp[n-1][k-1]);
    return 0;
}