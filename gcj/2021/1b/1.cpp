#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#include <string>
#include <set>
#include <vector>
#include <utility>

// g++ -std=c++17 -O2 -o s.out 1.cpp && ./s.out < x.txt
using namespace std;
bool check(int k, int a, int b, int cnt, vector<int>& mm, vector<vector<int>>& dp) {
    vector<int> m(mm.begin(), mm.end());
    vector<int> v(5005, 0);
    queue<int> q;
    q.push(k);
    v[k] = 1;
    while (cnt > 0 && !q.empty()) {
        k = q.front();
        q.pop();
        int x = k-a;
        int y = k-b;
        // printf("kkkk %d, cnt %d, x %d y %d\n", k, cnt, x, y);
        // for (int i = 1; i < (int)m.size(); i++) {
        //     if (m[i] > 0) {
        //         printf("i %d m[i] %d\n", i, m[i]);
        //     }
        // }
        if (x > 0) {
            if (m[x] > 0) {
                m[x]--;
                cnt--;
            } else {

            }
        }
        if (y > 0) {
            if (m[y] > 0) {
                m[y]--;
                cnt--;
            } else {
                
            }
        }
        // printf("-----After: cnt %d\n", cnt);
        // for (int i = 1; i < (int)m.size(); i++) {
        //     if (m[i] > 0) {
        //         printf("i %d m[i] %d\n", i, m[i]);
        //     }
        // }
    }
    if (cnt == 0) return true;
    return false;
}
int solve(int n, int a, int b, vector<int>& u) {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        cnt += u[i];
    }
    int max_k = 12;
    vector<vector<int>> dp(max_k, vector<int>(25, 0));
    for (int k = 0; k < max_k; k++) {
        
    }
    return -1;
}
int main() {
    int t;
    cin >> t;
    for (int cs = 1; cs <= t; cs++) {
        int n, a, b;
        cin >> n >> a >> b;
        vector<int> u(n+1, 0);
        for (int i = 1; i <= n; i++) cin >> u[i];
        int ans = solve(n,a,b,u);
        if (ans > -1) printf("Case #%d: %d\n", cs, ans);
        else printf("Case #%d: IMPOSSIBLE\n", cs);
    }
    return 0;
}
