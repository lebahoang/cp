#include <cstdio>
#include <fstream>
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <utility>

using namespace std;
using ll = long long;
ll calculateV(int mid, int i, int j, vector<vector<ll>>& prefix) {
    int ii = i-mid+1;
    int jj = j-mid+1;
    ll a = 0;
    if (ii > 0) a = prefix[ii-1][jj-1];
    ll b = 0;
    if (ii-1 >= 0) b = prefix[ii-1][j];
    ll c = 0;
    if (jj-1 >= 0) c= prefix[i][jj-1];
    ll v = prefix[i][j]-b-c+a;
    return v;
}
int bs(int i, int j, int n, int m, vector<vector<ll>>& prefix) {
    int maxL = min(i+1, j+1);
    int l = 1;
    int r = maxL;
    while (l <= r) {
        int mid = (l+r)/2;
        ll v = calculateV(mid, i, j, prefix);
        if (v >= 0 && mid+1 > maxL) return mid;
        ll vprev = calculateV(mid+1, i, j, prefix);
        if (v >= 0 && vprev < 0) return mid;
        if (vprev >= 0) {
            l = mid+1;
        } else {
            r = mid-1;
        }
    }
    return -1;
}
ll solve() {
    ll rs = 0;
    int n,m,k;
    cin >> n >> m >> k;
    vector<vector<int>> a(n, vector<int>(m, 0));
    vector<vector<ll>> prefix(n, vector<ll>(m,0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            a[i][j] -= k;
            int t = a[i][j];
            bool f1 = false;
            bool f2 = false;
            if (i-1 >= 0) {
                f1 = true;
                t += prefix[i-1][j];
            }
            if (j-1 >= 0) {
                f2 = true;
                t += prefix[i][j-1];
            }
            if (f1 && f2) {
                t -= prefix[i-1][j-1];
            }
            prefix[i][j] = t;
        }
    }
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < m; j++) {
    //         printf("%d ", a[i][j]);
    //     }
    //     printf("\n");
    // }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] < 0) continue;
            int maxlen = bs(i, j, n, m, prefix);
            // printf("i %d j %d ind(max Length) %d\n", i, j, maxlen);
            rs += maxlen;
        }
    }
    return rs;
}

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        printf("%lld\n", solve());
    }
    return 0;
}