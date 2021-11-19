#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <unordered_map>
#include <stack>
#include <queue>
#include <vector>
#include <utility>

// g++ -std=c++14 -stdlib=libc++ -O2 -o s.out 41.cpp && ./s.out < x.txt
// g++ -std=c++14 -stdlib=libc++ -O2 -o s.out 41.cpp && ./s.out < ~/Downloads/running_on_fumes_chapter_1_input.txt > out41.txt
using namespace std;
pair<int, int> a[1000004];
unordered_map<int, int> p;
int dp[1000004][2];
int solve(int n) {
    int rs = 0;
    memset(dp, 0, sizeof(dp));
    unordered_map<int, int> m;
    sort(a, a+n);
    for (int i = 0; i < n; i++) {
        p[a[i].first] = i;
    }
    dp[0][0] = a[0].second;
    dp[0][1] = a[0].second;
    m[a[0].first + a[0].second] = dp[0][1];
    rs = dp[0][0];
    
    for (int i = 1; i < n; i++) {
        // int pi = a[i].first;
        // int hi = a[i].second;
        // dp[i][0] = hi;
        // dp[i][1] = hi;
        // if (p.find(pi-hi) != p.end()) {
        //     dp[i][0] = dp[p[pi-hi]][0] + hi;
        // }
        
        // for (int j = 0; j < i; j++) {
        //     int pj = a[j].first;
        //     int hj = a[j].second;
        //     if (pj + hj == pi-hi) {
        //         dp[i][0] = max(dp[i][0], dp[j][1] + hi);
        //     }

        //     if (pj + hj == pi) {
        //         dp[i][1] = max(dp[i][1], dp[j][1] + hi);
        //     }
        // }
        // m[pi + hi] = dp[i][1];
        // // printf("%d %d %d\n", i, dp[i][0], dp[i][1]);
        // rs = max({rs, dp[i][0], dp[i][1]});

        int pi = a[i].first;
        int hi = a[i].second;
        dp[i][0] = hi;
        dp[i][1] = hi;
        if (p.find(pi-hi) != p.end()) {
            dp[i][0] = max(dp[i][0], dp[p[pi-hi]][0] + hi);
        }
        if (m.find(pi-hi) != m.end()) {
            dp[i][0] = max(dp[i][0], m[pi-hi] + hi);
        }
        if (m.find(pi) != m.end()) {
            dp[i][1] = max(dp[i][1], m[pi] + hi);
        }

        if (m.find(pi+hi) == m.end()) {
            m[pi+hi] = dp[i][1];
        } else {
            m[pi+hi] = max(m[pi+hi], dp[i][1]);
        }
        rs = max({rs, dp[i][0], dp[i][1]});
    }
    p.clear();
    return rs;
}
int main() {
    int t;
    cin >> t;
    for (int c = 0; c < t; c++) {
        int n;
        int pi, hi;
        cin >> n;
        for (int j = 0; j < n; j++) {
            cin >> pi >> hi;
            a[j] = {pi, hi};
        }
        printf("Case #%d: %d\n", c+1, solve(n));
    }
    return 0;
}