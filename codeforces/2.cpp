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

// g++ -std=c++14 -stdlib=libc++ -O2 -o s.out 2.cpp && ./s.out < x.txt
// https://codeforces.com/problemset/problem/489/F
using namespace std;
using ll = long long;
ll dp[505][505];
bool done[505][505];
// ll a[505][505];
// ll b[505][505];

ll c(int i, int n, int mod) {
    ll nn = n;
    if (i == 1) return nn%mod;
    else if (i == 2) return (nn*(nn-1)/2)%mod;
    return -1;
}
// ll solve2(int step, int n, int zero, int one, int mod) {
//     int x = zero;
//     for (int i = 0; i < step; i++) {
//         printf("%d\n", x);
//         for (int j = 0; j <= zero; j++) {
//             for (int k = 0; k <= n-j; k++) {
//                 if (j+2 <= zero && k-2 >= 0 && a[j+2][k-2] > 0) {
//                     ll t = (c(2, j+2, mod)*a[j+2][k-2])%mod;
//                     b[j][k] = (b[j][k]%mod + t)%mod;
//                 }
//                 if (k+2 <= n-j && a[j][k+2] > 0) {
//                     ll t = (c(2, k+2, mod)*a[j][k+2])%mod;
//                     b[j][k] = (b[j][k]%mod + t)%mod;

//                 }
//                 if (j+1 <= zero && a[j+1][k] > 0) {
//                     ll t = (c(1,j+1,mod)*c(1,k,mod)*a[j+1][k])%mod;
//                     b[j][k] = (b[j][k]%mod + t)%mod;
//                 }  
//             }
//         }

//         for (int j = 0; j <= zero; j++) {
//             for (int k = 0; k <= n-j; k++) {
//                 a[j][k] = b[j][k];
//             }
//         }
//     }
//     return a[0][0];
// }

ll solve3(int step, int n, int zero, int one, int mod) {
    // printf("zero %d one %d\n", zero, one);
    if (zero == 0 && one == 0) {
        if (step == n) return 1;
        return -1;
    }
    if (step >= n) {
        return -1;
    }
    if (done[zero][one]) {
        return dp[zero][one];
    }
    if (zero >= 2) {
        ll t = solve3(step+1, n, zero-2, one+2, mod);
        if (t > -1) {
            t = (c(2,zero,mod)*t)%mod;
            dp[zero][one] = (dp[zero][one]%mod + t%mod)%mod;
        } 
    }
    if (one >= 2) {
        ll t = solve3(step+1, n, zero, one-2, mod);
        if (t > -1) {
            t = (c(2,one,mod)*t)%mod;
            dp[zero][one] = (dp[zero][one]%mod + t%mod)%mod;
        }  
    }
    if (zero >= 1 && one >= 1) {
        ll t = solve3(step+1, n, zero-1, one, mod);
        if (t > -1) {
            t = (c(1,zero,mod)*c(1,one,mod)*t)%mod;
            dp[zero][one] = (dp[zero][one]%mod + t%mod)%mod;
        }
    }
    done[zero][one] = true;
    return dp[zero][one];
}

int main() {
    int n,m,mod;
    cin >> n >> m >> mod;
    string s[505];
    for (int i = 0; i < m; i++) {
        cin >> s[i];
    }
    if (m == 0) {
        // dp[n-2][2] = c(2,n,mod);
        // printf("Final RS %lld\n", solve(n-1, n-2, 2, mod));
        ll rs = (c(2,n,mod)*solve3(0, n-1, n-2, 2, mod))%mod;
        printf("%lld\n", rs);
        return 0;
    }
    int zero = 0;
    int one = 0;
    for (int j = 0; j < n; j++) {
        int a = 0;
        for (int i = 0; i < m; i++) {
            if (s[i][j] == '1') {
                a++;
            }
        }
        if (a == 0) {
            zero++;
        } else if (a == 1) {
            one++;
        }
    }
    // dp[zero][one] = 1%mod;
    printf("%lld\n", solve3(0, n-m, zero, one, mod));
    return 0;
}