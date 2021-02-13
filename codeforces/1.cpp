#include <cstdio>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <utility>

// g++ -std=c++14 -stdlib=libc++ -O2 -o s.out 41.cpp && ./s.out < x.txt
// g++ -std=c++14 -stdlib=libc++ -O2 -o s.out 41.cpp && ./s.out < ~/Downloads/running_on_fumes_chapter_1_input.txt > out41.txt
using namespace std;
using ll = long long;
ll t[505][3];
ll dp[505][505][3];
ll b[505];
ll c[505];
string s[505];
void dfs(int i, int j, int n, int m) {
    if (i == n) {
        dp[i][j][0] = c[j];
        dp[i][j][1] = c[j];
        dp[i][j][2] = c[j];
        // printf("aaa %lld %lld %lld\n", dp[i][j][0], dp[i][j][1], dp[i][j][2]);
        return;
    }
    dfs(i+1, j, n, m);
    dp[i][j][1] = max({dp[i+1][j][0], dp[i+1][j][1], dp[i+1][j][2]});
    if (j-1 >= 0 && s[i][j] != '.') {
        dfs(i+1, j-1, n, m);
        dp[i][j][0] = max({dp[i+1][j-1][0], dp[i+1][j-1][1], dp[i+1][j-1][2]});
    }
    if (j+1 < m && s[i][j] != '.') {
        dfs(i+1, j+1, n, m);
        dp[i][j][2] = max({dp[i+1][j+1][0], dp[i+1][j+1][1], dp[i+1][j+1][2]});
    }
    
    return;
}
ll solve(int n, int m) {
    for (int i = 0; i < m; i++) {
        // memset(dp, 0, sizeof(dp));
        dfs(0, i, n, m);
        t[i][0] = dp[0][i][0];
        t[i][1] = dp[0][i][1];
        t[i][2] = dp[0][i][2];
        // printf("%d %lld %lld %lld\n", i, t[i][0], t[i][1], t[i][2]);
    }
    ll rs[505][3];
    rs[0][0] = t[0][0]*b[0];
    rs[0][1] = t[0][1]*b[0];
    rs[0][2] = t[0][2]*b[0];
    for (int i = 1; i < m; i++) {
        rs[i][0] = max({rs[i-1][0], rs[i-1][1]}) + t[i][0]*b[i];
        rs[i][1] = max({rs[i-1][0], rs[i-1][1], rs[i-1][2]}) + t[i][1]*b[i];
        rs[i][2] = max({rs[i-1][0], rs[i-1][2]}) + t[i][2]*b[i];
    }
    return max({rs[m-1][0], rs[m-1][1], rs[m-1][2]});
}
int main() {
    int tc;
    cin >> tc;
    for (int cs = 0; cs < tc; cs++) {
        int n,m;
        cin >> n >> m;
        memset(t, 0, sizeof(t));
        memset(dp, 0, sizeof(dp));
        memset(b, 0, sizeof(b));
        memset(c, 0, sizeof(c));
        memset(s, 0, sizeof(s));
        for (int i = 0; i < m; i++) cin >> b[i];
        for (int i = 0; i < n; i++) {
            cin >> s[i];
        }
        for (int i = 0; i < m; i++) cin >> c[i];
        printf("%lld\n", solve(n, m));
    }
    return 0;
}

// int main() {
//     // ifstream infile("balls.in");
//     std::ios::sync_with_stdio(false);
//     std::cin.tie(0);
//     std::cout.tie(0);
//     freopen("balls.in","r",stdin);
//     int tc;
//     cin >> tc;
//     for (int cs = 0; cs < tc; cs++) {
//         int n,m;
//         cin >> n >> m;
//         memset(t, 0, sizeof(t));
//         memset(dp, 0, sizeof(dp));
//         memset(b, 0, sizeof(b));
//         memset(c, 0, sizeof(c));
//         memset(s, 0, sizeof(s));
//         for (int i = 0; i < m; i++) cin >> b[i];
//         for (int i = 0; i < n; i++) {
//             cin >> s[i];
//         }
//         for (int i = 0; i < m; i++) cin >> c[i];
//         // printf("%lld\n", solve(n, m));
//         cout << solve(n,m) << "\n";
//     }
//     return 0;
// }