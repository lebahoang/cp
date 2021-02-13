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

// g++ -std=c++14 -stdlib=libc++ -O2 -o s.out 1000.cpp && ./s.out

// n-x(get-1) = K
using namespace std;
bool check(int i, int j, int c, int k) {
    int n = (j-i+1);
    // printf("AAAAA i %d j %d c %d k %d (n-c)mod(k-1) %d\n", i, j, c, k, (n-c)%(k-1));
    if ((n-c)%(k-1) == 0) return true;
    return false;
}
int go(int k, vector<int>& prefix, int (&dp)[50][50][50], int i, int j, int c) {
    if (dp[i][j][c] != 1e9) {
        return dp[i][j][c];
    }
    if (j-i+1 == c && c < k) {
        dp[i][j][c] = 0;
        return dp[i][j][c];
    } else if (c == 1) {
        if (j-i+1 == k) {
            if (i-1 >= 0) {
                dp[i][j][c] = prefix[j]-prefix[i-1];
            } else {
                dp[i][j][c] = prefix[j];
            }
        } else {
            int t = 0;
            if (i-1 >= 0) t = prefix[i-1];
            t = prefix[j]-t;
            for (int a = i; a < j; a++) {
                for (int kk = 1; kk < k; kk++) {
                    if (check(i, a, kk, k) && check(a+1, j, k-kk, k)) {
                        int x = go(k, prefix, dp, i, a, kk);
                        int y = go(k, prefix, dp, a+1, j, k-kk);
                        dp[i][j][c] = min(dp[i][j][c], x+y+t);
                    }
                }
            }
        }
        return dp[i][j][c];
    }
    for (int a = i; a < j; a++) {
        for (int kk = 1; kk < c; kk++) {
            if (check(i, a, kk, k) && check(a+1, j, c-kk, k)) {
                int x = go(k, prefix, dp, i, a, kk);
                int y = go(k, prefix, dp, a+1, j, c-kk);
                dp[i][j][c] = min(dp[i][j][c], x+y);
            }
        }
    }
    return dp[i][j][c];
}
int solve(vector<int>& stones, int K) {
    int dp[50][50][50];
    // int sum[50][50][50];
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            for (int l = 0; l < 50; l++) {
                dp[i][j][l] = 1e9;
                // sum[i][j][l] = 1e9;
            }
        }
    }
    int n = (int)stones.size();
    if ((K-1 > 1 && n%(K-1) != 1)) return -1;
    if (K == 2 && n == 1) return 0;
    vector<int> prefix(n, 0);
    prefix[0] = stones[0];
    for (int i = 1; i < n; i++) prefix[i] = prefix[i-1]+stones[i];
    int rs = go(K, prefix, dp, 0, n-1, 1);
    // for (int i = 0; i < n; i++) {
    //     for (int j = i; j < n; j++) {
    //         for (int l = 1; l <= K; l++) {
    //             printf("i %d j %d c %d dp %d\n", i, j, l, dp[i][j][l]);
    //         }
    //     }
    // }
    return rs;
}
int main() {
    // vector<int> stones = {3,2,4,1};
    // int k = 2;
    // vector<int> stones = {3,5,1,2,6};
    // int k = 3;
    vector<int> stones = {3,2,4,1,3,45,12,54,23,34,11,1,1,1,32,4,12,56,7,832,76,7};
    int k = 4;
    // vector<int> stones = {3,2,4,1,3,45,12};
    // int k = 2;
    // vector<int> stones = {4,2,4,6,4,6,9,9,5};
    // int k = 3;
    printf("%d\n", solve(stones, k));
    return 0;
}