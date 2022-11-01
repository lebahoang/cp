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

// For test speed: g++ -std=c++17 -Wall -lm -O2 -o s.out 1746D.cpp.cpp && time ./s.out < x.txt
// g++ -std=c++17 -Wshadow -Wall -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined -o s.out 1746D.cpp && ./s.out < x.txt
struct I {
    ll k;
    ll val;
};
ll dfs(int i, ll k, vector<vector<int>>& nei, vector<ll>& s, vector<vector<I>>& dp) {
    // printf("I %d, nei[i].size %d k %lld\n", i, (int)nei[i].size(), k);
    for (I& x: dp[i]) {
        if (x.k == k) return x.val;
    }
    ll ans = s[i]*k;
    if ((int)nei[i].size() == 0) {
        dp[i].push_back(I{k, ans});
        return ans;
    }
    ll rem = k%(ll)nei[i].size();
    ll kk = (k-rem)/(ll)nei[i].size();
    vector<ll> ss = {};
    for (int j: nei[i]) {
        ll f1 = dfs(j, kk, nei, s, dp);
        if (rem > 0) {
            ll f2 = dfs(j, kk+1, nei, s, dp);
            ss.push_back(f2-f1);
        } else {
            ss.push_back(0);
        }
        ans += f1;
    }
    // printf("scoreOfTree[%d] %lld\n", i, scoreOfTree[i]);
    sort(ss.begin(), ss.end(), greater<ll>());
    for (int x = 0; x < (int)rem; x++) {
        ans += ss[x];
    }
    dp[i].push_back(I{k, ans});
    return ans;
}
int main() {
    int t;
    cin >> t;
    for (int cs = 0; cs < t; cs++) {
        int n;
        ll k;
        cin >> n >> k;
        vector<vector<int>> nei(n+5, vector<int>{});
        vector<ll> s(n+5, 0);
        int pi;
        for (int i = 2; i <= n; i++) {
            cin >> pi;
            nei[pi].push_back(i);
        }
        for (int i = 1; i <= n; i++) {
            cin >> s[i];
        }
        vector<vector<I>> dp(n+5, vector<I>{});
        dfs(1, k, nei, s, dp);
        printf("%lld\n", dp[1][0].val);
    }
    return 0;
}