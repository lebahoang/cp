#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>

// g++ -std=c++14 -stdlib=libc++ -O2 -o s.out a.cpp && ./s.out < x.txt
using namespace std;
const int nax = 306;
double dp[nax][nax][nax];
int main() {
    int n;
    cin >> n;
    vector<int> as(n, 0);
    for (int i = 0; i < n; i++) cin >> as[i];
    int a = 0;
    int b = 0;
    int c = 0;
    for (int i = 0; i < n; i++) {
        if (as[i] == 1) a++;
        else if (as[i] == 2) b++;
        else c++;
    }

    for (int k = c; k >= 0; k--) {
        for (int j = b; j >= 0; j--) {
            for (int i = a; i >= 0; i--) {
                if (i == a && j == b && k == c) {
                    dp[i][j][k] = 0.0;
                    continue;
                }
                double x = i+j+k;
                dp[i][j][k] = (double)(n+3)/x;
                if (i+1 <= a && j-1 >= 0) {
                    dp[i][j][k] += (double) (i+1)/x * (dp[i+1][j-1][k]);
                }
                if (j+1 <= b && k-1 >= 0) {
                    dp[i][j][k] += (double) (j+1)/x * (dp[i][j+1][k-1]);
                }
                if (k+1 <= c) {
                    dp[i][j][k] += (double) (k+1)/x * (dp[i][j][k+1]);
                }
                printf("i %d j %d k %d %.9f\n", i, j, k, dp[i][j][k]);
            }
        }
    }
    printf("%.9f\n", dp[0][0][0]);
    return 0;
}