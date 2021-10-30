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
    vector<int> dp(n, 0);
    vector<int> prefix(n, 0);
    for (int i = 0; i < n; i++) {
        if (i == 0) prefix[i] = st[i];
        else prefix[i] = prefix[i-1]+st[i];
    }
    dp[1] = prefix[1];
    for (int i = 2; i < n; i++) {
        dp[i] = -1e9-9;
        for (int j = i-1; j >= 1; j--) {
            int t = prefix[i]-prefix[j];
            dp[i] = max(dp[i], prefix[j]-dp[j]+t);
            printf("i %d j %d, %d\n", i, j, prefix[j]-dp[j]+t);
            dp[i] = max(dp[i], t);
        }
    }
    for(int i = 1; i < n; i++) printf("dp[%d] %d, %d\n", i, dp[i], prefix[i]-dp[i]);
    return dp[n-1];
}
int main() {
    vector<int> st = {-1,2,-3,4,-5};
    printf("%d\n", solve(st));
    return 0;
}