#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <utility>

// g++ -std=c++14 -stdlib=libc++ -O2 -o s.out 1.cpp && ./s.out

using namespace std;
// int solve(string a, int d) {
//     int rs = 0;
//     int c = 0;
//     int j = 0;
//     for (int i = 0; i < (int)a.length(); i++) {
//         if (a[i] == '1') c++;
//         j++;
//         if (j == d) {
//             if (c == 0) {
//                 rs++;
//                 a[i] = '1';
//                 c = 1;
//             }
//             if (a[i-j+1] == '1') c--;
//             j--;
//         }
//     }
//     return rs;
// }

using ll = long long;
const int NMAX = 303;
int a[NMAX][NMAX];
int visited[NMAX][NMAX];

void go(int i, int j, int n, int m, ll cur, ll& rs) {
    visited[i][j] = 1;
    if (i == n-1 && j == m-1) {
        rs = min(rs, cur);
        visited[i][j] = 0;
        return;
    }
    int tcur = 0;
    if (i-1 >= 0 && visited[i-1][j] == 0) {
        int k = abs(a[i-1][j] - a[i][j]);
        if (k > rs) return;
        tcur = cur;
        if (k > cur) cur = k;
        go(i-1, j, n, m, cur, rs);
        cur = tcur;
        visited[i-1][j] = 0;
    }
    if (i+1 < n && visited[i+1][j] == 0) {
        int k = abs(a[i+1][j] - a[i][j]);
        if (k > rs) return;
        tcur = cur;
        if (k > cur) cur = k;
        go(i+1, j, n, m, cur, rs);
        cur = tcur;
        visited[i+1][j] = 0;
    }
    if (j-1 >= 0 && visited[i][j-1] == 0) {
        int k = abs(a[i][j-1] - a[i][j]);
        if (k > rs) return;
        tcur = cur;
        if (k > cur) cur = k;
        go(i, j-1, n, m, cur, rs);
        cur = tcur;
        visited[i][j-1] = 0;
    }
    if (j+1 < m && visited[i][j+1] == 0) {
        int k = abs(a[i][j+1] - a[i][j]);
        if (k > rs) return;
        tcur = cur;
        if (k > cur) cur = k;
        go(i, j+1, n, m, cur, rs);
        cur = tcur;
        visited[i][j+1] = 0;
    }
}

ll solve(int n, int m) {
    ll rs = 1e12 + 9;
    ll cur = 0;
    go(0, 0, n, m, cur, rs);
    return rs;
}
int main() {
    // int d;
    // string a = "";
    // cin >> a >> d;
    // int rs = solve(a, d);
    // printf("%d\n", rs);

    int n,m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    printf("%lld\n", solve(n, m));
    return 0;
}