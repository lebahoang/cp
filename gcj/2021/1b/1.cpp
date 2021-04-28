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
// bool check(int k, int n, int a, int b, int cnt, vector<int>& u, vector<vector<int>>& dp) {
//     vector<int> m(u.begin(), u.end());
//     vector<int> obtain(25, 0);
//     queue<int> q;
//     q.push(k);
//     while (!q.empty()) {
//         k = q.front();
//         q.pop();
//         int x = k-a;
//         int y = k-b;
//         // printf("kkkk %d, cnt %d, x %d y %d\n", k, cnt, x, y);
//         // for (int i = 1; i < (int)m.size(); i++) {
//         //     if (m[i] > 0) {
//         //         printf("i %d m[i] %d\n", i, m[i]);
//         //     }
//         // }
//         if (x > 0) {
//             if (m[x] > 0) {
//                 obtain[x]++;
//                 m[x]--;
//                 cnt--;
//             } else {
//                 vector<int> t = dp[x];
//                 for (int i = 1; i <= n; i++) {
//                     if (m[i] > 0) {
//                         obtain[i] += t[i];
//                         m[i] -= t[i];
//                         cnt -= t[i];
//                     }
//                 }
//             }
//         }
//         if (y > 0) {
//             if (m[y] > 0) {
//                 obtain[y]++;
//                 m[y]--;
//                 cnt--;
//             } else {
//                 vector<int> t = dp[y];
//                 for (int i = 1; i <= n; i++) {
//                     if (m[i] > 0) {
//                         obtain[i] += t[i];
//                         m[i] -= t[i];
//                         cnt -= t[i];
//                     }
//                 }
//             }
//         }
//         // printf("-----After: cnt %d\n", cnt);
//         // for (int i = 1; i < (int)m.size(); i++) {
//         //     if (m[i] > 0) {
//         //         printf("i %d m[i] %d\n", i, m[i]);
//         //     }
//         // }
//     }
//     dp[k] = obtain;
//     if (cnt == 0) return true;
//     return false;
// }
bool check(int k, int n, int a, int b, int cnt, vector<int>& u, vector<int>& visited, vector<vector<int>>& dp) {
    vector<int> m(u.begin(), u.end());
    vector<int> obtain(25, 0);
    int x = k-a;
    int y = k-b;
    // printf("kkkk %d, cnt %d, x %d y %d\n", k, cnt, x, y);
    // for (int i = 1; i < (int)m.size(); i++) {
    //     if (m[i] > 0) {
    //         printf("i %d m[i] %d\n", i, m[i]);
    //     }
    // }
    if (x > 0) {
        if (x <= n && m[x] > 0) {
            obtain[x]++;
            m[x]--;
            cnt--;
        } else {
            if (visited[x] == 0) {
                check(x, n, a, b, cnt, m, visited, dp);
            }
            vector<int> t = dp[x];
            for (int i = 1; i <= n; i++) {
                obtain[i] += t[i];
                m[i] -= t[i];
                cnt -= t[i];
            }
        }
    }
    if (y > 0) {
        if (y <= n && m[y] > 0) {
            obtain[y]++;
            m[y]--;
            cnt--;
        } else {
            if (visited[y] == 0) {
                check(y, n, a, b, cnt, m, visited, dp);
            }
            vector<int> t = dp[y];
            for (int i = 1; i <= n; i++) {
                obtain[i] += t[i];
                m[i] -= t[i];
                cnt -= t[i];
            }
        }
    }
    // printf("-----After: cnt %d\n", cnt);
    // for (int i = 1; i < (int)m.size(); i++) {
    //     if (m[i] > 0) {
    //         printf("i %d m[i] %d\n", i, m[i]);
    //     }
    // }
    printf("%d, cnt %d, ", k, cnt);
    for (int i = 1; i <= n; i++) {
        printf("%d ", obtain[i]);
    }
    printf("\n");

    visited[k] = 1;
    dp[k] = obtain;
    if (cnt == 0) return true;
    return false;
}
int solve(int n, int a, int b, vector<int>& u) {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        cnt += u[i];
    }
    int max_k = 20;
    for (int k = 0; k < max_k; k++) {
        printf("k %d\n", k);
        vector<vector<int>> dp(max_k, vector<int>(25, 0));
        vector<int> visited(max_k, 0);
        if (check(k, n, a, b, cnt, u, visited, dp)) {
            return k;
        }
    }
    // printf("dsadas\n");
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
