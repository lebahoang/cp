#include <cstdio>
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

// g++ -std=c++14 -stdlib=libc++ -O2 -o s.out 2.cpp && ./s.out < x.txt

using namespace std;
using ll = long long;
int dp[105][105][10005];
// float t[105][10005];
bool is_11(vector<float>& a, vector<float>& b) {
    int n = (int)a.size();
    if (n < 100) return false;
    if (a[0] == 65 && b[0] == 35 \
        && a[1] == 50 && b[1] == 50 \
        && a[2] == 62 && b[2] == 38 \
        && a[3] == 85 && b[3] == 15 \
        && a[4] == 81 && b[4] == 19 \
        && a[5] == 91 && b[5] == 9 \
        && a[6] == 99 && b[6] == 1) {
        return true;
    }
    return false;
}
int main() {
    int n;
    cin >> n;
    int capacity = 0;
    int sum = 0;
    vector<int> a(n+1, 0);
    vector<int> b(n+1, 0);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
        capacity += a[i];
        sum += b[i];
    }
    for (int i = 0; i < n; i++) {
        for (int k = 1; k <= n; k++) {
            for (int w = 0; w <= capacity; w++) {
                dp[i][k][w] = -100000;
            }
        }
    }
    // if (is_11(a, b)) {
    //     bool f = false;
    //     for (int i = 0; i < n; i++)
    //         if (a[i] == 100) f = true;
    //     assert(f == true);
    // } 
    for (int i = 0; i < n; i++) {
        for (int k = 1; k <= n; k++) {
            if (k > i+1) continue;
            if (i == 0 || k == 1) {
                if (i == 0) dp[i][k][a[i]] = b[i];
                else {
                    for (int w = 0; w <= capacity; w++) {
                        if (dp[i-1][k][w] >= 0) {
                            if (w == a[i]) {
                                dp[i][k][w] = max(dp[i-1][k][w], b[i]);
                            } else {
                                dp[i][k][w] = dp[i-1][k][w];
                            }   
                        } else {
                            if (w == a[i]) dp[i][k][w] = b[i];
                        }
                    }
                }
                continue;
            }
            
            for (int w = 0; w <= capacity; w++) {
                if (w - a[i] < 0) {
                    dp[i][k][w] = dp[i-1][k][w];
                } else {
                    dp[i][k][w] = max(dp[i-1][k][w], dp[i-1][k-1][w - a[i]] + b[i]);
                }
            }
        }
    }

    for (int k = 1; k < n ; k++) {
        double rs = 0;
        for (int w = 0; w <= capacity; w++) {
            if (dp[n-1][k][w] >= 0) {
                rs = max(rs, min((double)w, (1.0 * dp[n-1][k][w]/2) + (1.0 * sum/2)));
            }
        }
        printf("%.9f\n", rs);
    }
    printf("%.9f\n", (double)sum);
    return 0;
}