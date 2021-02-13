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

// g++ -std=c++14 -stdlib=libc++ -O2 -o s.out 4.cpp && ./s.out < x.txt
using namespace std;
using ll = long long;
const int nax = 5005;
int dp[nax][nax];
int main() {
    int n, m;
    cin >> n >> m;
    string a, b;
    cin >> a >> b;
    int rs = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == 0 && j == 0) {
                if (a[i] == b[j]) dp[i][j] = 2;
                continue;
            }
            if (a[i] == b[j]) {
                if (i-1 >= 0 && j-1 >= 0) {
                    dp[i][j] = max(dp[i][j], dp[i-1][j-1]+2);
                } else {
                    dp[i][j] = 2;
                }
            }
            if (i-1 >= 0) {
                dp[i][j] = max(dp[i][j], dp[i-1][j]-1);
            }
            if (j-1 >= 0) {
                dp[i][j] = max(dp[i][j], dp[i][j-1]-1);
            }
            rs = max(rs, dp[i][j]);
        }
    }

    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < m; j++) {
    //         printf("i %d j %d, %d\n", i, j, dp[i][j]);
    //     }
    // }
    printf("%d\n", rs);
    return 0;
}