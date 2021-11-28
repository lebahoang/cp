#include <cstdlib>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <stack>
#include <queue>
    
// g++ -std=c++14 -Wshadow -Wall -o s.out -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined 1.cpp && ./s.out < x.txt

using namespace std;
using ll = long long;
// ll bf(vector<ll>& a, int n) {
//     ll rs = 0;
//     for (int i = 0; i < n; i++) {
//         for (int j = i+2; j < n; j++) {
//             ll v = -1;
//             int kk = -1;
//             for (int k = i+1; k < j; k++) {
//                 ll xx = (a[i]-a[k])*(a[k]-a[j]);
//                 if (xx > v) {
//                     v = xx;
//                     kk = k;
//                 }
//             }
//             rs += v;
//             // printf("I %d J %d K %d\n", i, j, kk);
//         }
//     }
//     return rs;
// }
int main() {
    int t;
    cin >> t;
    for (int cs = 0; cs < t; cs++) {
        ll rs = 0;
        int n;
        cin >> n;
        vector<ll> a(n+2, 0);
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < n; i++) {
            for (int j = i+2; j < n; j++) {
                ll s = a[i]+a[j];
                int l = i;
                int r = j;
                int k = -1;
                while (l < r) {
                    int mid = (l+r)/2;
                    // printf("MID %d\n", mid);
                    ll x = 2*a[mid]-s;
                    if (x <= 0) {
                        if (a[mid] != a[i] && (mid == j-1 || a[mid+1] == a[j] || 2*a[mid+1]-s > 0)) {
                            k = mid;
                            break;
                        }
                        l = mid+1;
                    } else if (x > 0) {
                        if (mid == i+1 || a[mid-1] == a[i]) {
                            k = mid;
                            break;
                        }
                        r = mid-1;
                    }
                    // printf("I %d, J %d, L %d R %d\n", i, j, l, r);
                    if (l >= r) {
                        k = l;
                    }
                }
                // printf("I %d, J %d, K %d\n", i, j, k);
                rs += max((a[i]-a[k])*(a[k]-a[j]), (a[i]-a[k+1])*(a[k+1]-a[j]));
            }
        }
        // printf("%lld, %lld\n", rs, bf(a, n));
        printf("%lld\n", rs);
    }
    return 0;
}