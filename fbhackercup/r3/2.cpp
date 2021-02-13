#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <utility>
#include <unordered_map>

// g++ -std=c++14 -stdlib=libc++ -O2 -o s.out 2.cpp && ./s.out < x.txt
using namespace std;
using ll = long long;
const int nax = 505;
int dp[nax][nax];
struct I {
    int p;
    int r;
    int i;
};
void setDP() {
    for (int i = 0; i < nax; i++) {
        for (int j = 0; j < nax; j++) {
            dp[i][j] = 2e9+9;
        }
    }
}
bool cmp(I a, I b) {
    if (a.p < b.p) return true;
    else if (a.p > b.p) return false;
    if (a.i < b.i) return true;
    else if (a.i > b.i) return false;
    return true;
}
pair<int, int> count(int l, int i, vector<I>& a) {
    int rs = 2e9+9;
    int isOnlyZero = 1;
    unordered_map<int, int> m;

    for (int k = l; k <= i; k++) {
        if (a[k].r == 1) isOnlyZero = 0;
        int x = 0;
        int y = 0;
        if (m.find(a[k].p) == m.end()) m[a[k].p] = 2e9+9;
        int ind = a[k].i;
        for (int kk = l; kk <= i; kk++) {
            if (kk == k) continue;
            if (a[k].p == a[kk].p && ((a[k].r == 1 && a[kk].r == 0 && a[kk].i > ind) || (a[k].r == 0 && a[kk].r == 1 && a[kk].i <= ind))) {
                y++;
            }
            if (a[k].p != a[kk].p && ((a[k].r == 1 && a[kk].r == 0 && a[kk].i > ind) || (a[k].r == 0 && a[kk].r == 1 && a[kk].i <= ind))) {
            // if ((a[kk].r == 0 && a[kk].i > ind) || (a[kk].r == 1 && a[kk].i <= ind)) {
                x++;
            }
        }
        // printf("k %d x %d\n", k, x);
        rs = min(rs, x);
        m[a[k].p] = min(m[a[k].p], y);
    }
    for (auto it = m.begin(); it != m.end(); it++) {
        rs += it->second;
    }
    return {rs, isOnlyZero};

    // int x = 0;
    // int y = 0;
    // for (int k = l; k <= i; k++) {
    //     if (a[k].r == 0) x++;
    //     else y++;
    // }
    // if (y == 0) return {min(x,y), 1};
    // return {min(x,y), 0};
}
int solve(int n, int k, vector<I>& a) {
    sort(a.begin(), a.begin()+n, cmp);
    for (int i = 0; i < n; i++) {
        printf("%d %d %d %d\n", a[i].p, a[i].r, a[i].i, i);
    }
    if (a[0].r == 1 && k > 0) dp[0][1] = 1;
    else if (a[0].r == 0) dp[0][0] = 0;
    for (int i = 1; i < n; i++) {
        for (int l = -1; l < i; l++) {
            pair<int, int> xx = count(l+1, i, a);
            int x = xx.first;
            int isOnlyZero = xx.second;
            printf("i %d l %d x %d\n", i, l+1, x);
            for (int j = 0; j <= k; j++) {
                if (isOnlyZero == 1) {
                    if (j != x) continue;
                    if (l >= 0) {
                        dp[i][j] = min(dp[i][j], dp[l][j]);
                    } else {
                        dp[i][j] = min(dp[i][j], 0);
                    }
                } else {
                    if (j != x) continue;
                    if (l >= 0) {
                        // printf("dassads\n");
                        dp[i][j] = min(dp[i][j], dp[l][j-x]+1);
                    } else {
                        dp[i][j] = min(dp[i][j], 1);
                    }
                }
            }
        }
    }
    printf("aaaaa %d %d %d %d %d\n", dp[11][0],dp[11][1],dp[11][2],dp[11][3],dp[11][4]);
    printf("aaaaa %d %d %d %d %d\n", dp[15][0],dp[15][1],dp[15][2],dp[15][3],dp[15][4]);
    int rs = 2e9+9;
    for (int i = 0; i <= k; i++) {
        rs = min(rs, dp[n-1][i]);
    }
    if (rs >= 2e9+9) return -1;
    return rs;
}
int main() {
    int t;
    cin >> t;
    vector<I> a(nax, {-1,-1,-1});
    for (int cs = 1; cs <= t; cs++) {
        setDP();
        printf("PPPP\n");
        int n,k,pi,ri;
        cin >> n >> k;
        for (int i = 0; i < n; i++) {
            cin >> pi >> ri;
            a[i] = {pi, ri, i};
        }
        printf("Case #%d: %d\n", cs, solve(n, k, a));
    }
    return 0;
}
