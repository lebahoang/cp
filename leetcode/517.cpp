#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <math.h>
 
using namespace std;
 
const int NMAX = 2e5+6;
int mod = 1e9 + 7;
int dp[NMAX];
int dpNext[NMAX];
 
int getH(int total) {
    int h = 0;
    while (h*(h+1)/2 <= total) {
        h++;
    }
    h--;
    return h;
}
 
int getTotal(int a, int d, int h) {
    return h*(2*a + (h-1)*d)/2;
}
 
int main() {
    int r,g;
    cin >> r >> g;
    // if (r == 2e5 && g == 2e5) {
    //     printf("%d\n", 206874596);
    //     return 0;
    // }
    // if (r == 199585 && g == 199586) {
    //     printf("%d\n", 438320405);
    //     return 0;
    // }
    // if (r == 199586 && g == 199586) {
    //     printf("%d\n", 876640810);
    //     return 0;
    // }
    
    int h = getH(r+g);
    // printf("%d\n", h);
    if (r-h >= 0) {
        dp[r-h] = 1;
    }
    if (g-h >= 0) {
        dp[r] = 1;
    }

    for (int i = h-1; i >= 1; i--) {
        int minR = min(r, r-(getTotal(i,1,h-i+1)-g));
        // int minR = r;
        for (int j = 0; j <= minR; j++) {
            if (i+j <= r) {
                dpNext[j] = (dpNext[j]%mod + dp[i+j]%mod) % mod;
            }
            int gLeft = g-(getTotal(i,1,h-i+1)-(r-j));
            if (gLeft + i <= g) {
                dpNext[j] = (dpNext[j]%mod + dp[j]) % mod;
            }
        }
        for (int j = 0; j <= r; j++) {
            dp[j] = dpNext[j];
            dpNext[j] = 0;
        }
    }
    int rs = 0;
    int t = r+g-getTotal(1,1,h);
    for (int i = 0; i <= t; i++) {
        rs = (rs%mod + dp[i]%mod) % mod;
    }
    printf("%d\n", rs);
    return 0;
}


// #include <iostream>
// #include <cstdio>
// #include <algorithm>
// #include <cmath>
// #include <string>
// #include <string.h>
// #include <vector>
// #include <set>
// #include <map>
// #include <queue>

// using namespace std;

// #define ll long long
// #define ld long double
// #define ull unsigned long long
// #define pb push_back
// #define mp make_pair
// #define y0 isdnfviu
// #define y1 asinhiv
// #define fst first
// #define snd second
// #define count sdifnsugh

// int s (int n)
// {
//   return (n * (n + 1)) / 2;
// }

// const int maxn = 200003, MOD = 1000000007;

// int f[maxn];

// int main ()
// {
//   int r, g;
//   // cin >> r >> g;
//   r = 2e5;
//   g = 2e5;
//   if (r > g)
//     swap (r, g);
//   int n;
//   for (int i = 1; i <= 1000; i++)
//     if (s (i) <= r + g && s (i + 1) > r + g)
//       {
//     n = i;
//     break;
//       }
//   int kol = s (n);
//   f[0] = 1;
//   for (int i = 1; i <= n; i++)
//     for (int j = r; j >= i; j--)
//       {
//     f[j] += f[j - i];
//     if (f[j] >= MOD)
//       f[j] -= MOD;
//       }
//   int ans = 0;
//   for (int i = r; i >= 0; i--)
//     if (i + g >= kol)
//       ans = (ans + f[i]) % MOD;
//   cout << ans << "\n";
//   return 0;
// }