#include <cstdlib>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <stack>
#include <queue>
    
// g++ -std=c++14 -Wshadow -Wall -o s.out -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined 1556C.cpp && ./s.out < x.txt

using namespace std;
// int main() {
//     int t;
//     cin >> t;
//     for (int k = 0; k < t; k++) {
//         long long rs = 0;
//         int n;
//         cin >> n;
//         vector<long long> a(n+2, 0);
//         vector<long long> b(n+2, 0);
//         b[0] = 0;
//         int m = 1;
//         for (int i = 1; i <= n; i++) {
//             cin >> a[i];
//             if (i%2 == 0) {
//                 rs += min(a[i], a[i-1]);
//                 b[i/2] = b[i/2-1] + a[i-1] - a[i];
//                 m++;
//             }
//         }
//         // printf("AAA %lld, m %d\n", rs, m);
//         // for (int i = 0; i < m; i++) {
//         //     printf("%lld ", b[i]);
//         // }
//         // printf("\n");
//         vector<vector<long long>> c(m+2, vector<long long>(m+2, 0));
        
//         for (int i = 0; i < m; i++) {
//             for (int j = i; j < m; j++) {
//                 if  (j == i) {
//                     c[i][j] = b[i];
//                 } else {
//                     c[i][j] = min(c[i][j-1], b[j]);
//                 }
//             }
//         }
//         for (int i = 0; i < m-1; i++) {
//             for (int j = i+2; j < m; j++) {
//                 if (c[i+1][j-1] >= b[i] && c[i+1][j-1] >= b[j]) {
//                     long long val = c[i+1][j-1] - max(b[i], b[j]) + 1;
//                     // printf("I %d, J %d, %lld\n", i, j, val);
//                     rs += val;
//                 }
//             }
//         }
//         printf("%lld\n", rs);
//     }
// return 0;
// }
    
int main() {
    long long rs = 0;
    int n;
    cin >> n;
    vector<long long> a(n+2, 0);
    vector<long long> b(n+2, 0);
    b[0] = 0;
    int m = 1;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (i%2 == 0) {
            rs += min(a[i], a[i-1]);
            b[i/2] = b[i/2-1] + a[i-1] - a[i];
            m++;
        }
    }
    // printf("AAA %lld, m %d\n", rs, m);
    // for (int i = 0; i < m; i++) {
    //     printf("%lld ", b[i]);
    // }
    // printf("\n");
    vector<vector<long long>> c(m+2, vector<long long>(m+2, 0));
    
    for (int i = 0; i < m; i++) {
        for (int j = i; j < m; j++) {
            if  (j == i) {
                c[i][j] = b[i];
            } else {
                c[i][j] = min(c[i][j-1], b[j]);
            }
        }
    }
    for (int i = 0; i < m-1; i++) {
        for (int j = i+2; j < m; j++) {
            if (c[i+1][j-1] >= b[i] && c[i+1][j-1] >= b[j]) {
                long long val = c[i+1][j-1] - max(b[i], b[j]) + 1;
                // printf("I %d, J %d, %lld\n", i, j, val);
                rs += val;
            }
        }
    }
    printf("%lld\n", rs);
    return 0;
}
    