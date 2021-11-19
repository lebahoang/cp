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
bool check(int k, int n, int a, int b, int cnt, vector<int>& mm) {
    vector<int> m(mm.begin(), mm.end());
    queue<int> q;
    q.push(k);
    while (cnt > 0 && !q.empty()) {
        k = q.front();
        q.pop();
        int x = k-a;
        int y = k-b;
        if (x > 0) {
            if (x <= n && m[x] > 0) {
                m[x]--;
                cnt--;
            } else {
                // if (v[x] == 0) {
                //     v[x] = 1;
                //     q.push(x);
                // }
                q.push(x);
            }
        }
        if (y > 0) {
            if (y <= n && m[y] > 0) {
                m[y]--;
                cnt--;
            } else {
                // if (v[y] == 0) {
                //     v[y] = 1;
                //     q.push(y);
                // }
                q.push(y);
            }
        }
    }
    if (cnt == 0) return true;
    return false;
}
int solve(int n, int a, int b, vector<int>& u) {
    vector<int> m(n+1, 0);
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        m[i] = u[i-1];
        cnt += m[i];
    }
    int max_k = 405;
    for (int k = 0; k < max_k; k++) {
        printf("kkkk %d\n", k);
        if (check(k,n,a,b,cnt,m)) {
            return k;
        }
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
        for (int i = 0; i < n; i++) cin >> u[i];
        int ans = solve(n,a,b,u);
        if (ans > -1) printf("Case #%d: %d\n", cs, ans);
        else printf("Case #%d: IMPOSSIBLE\n", cs);
    }
    return 0;
}
