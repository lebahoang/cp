#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
// g++ -std=c++17 -Wshadow -Wall -o s.out -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined 3.cpp && ./s.out
using ll = long long;
ll solve(int n, vector<int>& x, int a, int b) {
    vector<ll> r = {};
    for (int i = 0; i < n; i++) {
        r.push_back((ll)(x[i] - i));
        // printf("%lld ", r.back());
    }
    // printf("\n");
    vector<ll> dp(n+3, 1e15);
    vector<ll> maxV(n+3, -1);
    dp[0] = 0;
    maxV[0] = x[0];
    // printf("dp[%d] %lld, maxV[%d] %lld\n", 0, dp[0], 0, maxV[0]);
    for (int i = 1; i < n; i++) {
        for (int k = 0; k <= i; k++) {
            ll val = r[k];
            if (val <= 0) val = 1;
            ll t = 0;
            for (int l = 0; l <= i; l++) {
                if (r[l] <= val) {
                    t += (val-r[l])*a;
                } else {
                    t += (r[l]-val)*b;
                }
            }
            if (dp[i] > t) {
                dp[i] = t;
                maxV[i] = val;
            }
        }
        //////
        for (int j = 0; j < i; j++) {
            if (i-j == 1) {
                ll val = r[j+1];
                if (val <= 0) val = 1;
                if (maxV[j] <= val) {
                    ll t = 0;
                    if (val <= r[j+1]) {
                        t = dp[j] + (r[j+1]-val)*a;
                    } else {
                        t = dp[j] + (val-r[j+1])*b;
                    }
                    if (dp[i] > t) {
                        dp[i] = t;
                        maxV[i] = val;
                    }
                }
            } else {
                for (int k = j+1; k <= i; k++) {
                    ll val = r[k];
                    if (val <= 0) val = 1;
                    if (maxV[j] <= val) {
                        ll t = 0;
                        for (int l = j+1; l <= i; l++) {
                            if (r[l] <= val) {
                                t += (val-r[l])*a;
                            } else {
                                t += (r[l]-val)*b;
                            }
                        }
                        if (dp[i] > dp[j]+t) {
                            dp[i] = dp[j]+t;
                            maxV[i] = val;
                        }
                    }
                }
            }
        }
        // printf("dp[%d] %lld, maxV[%d] %lld\n", i, dp[i], i, maxV[i]);
    }
    return dp[n-1];
}
int main() {
    // int n = 5;
    // vector<int> r = {2,5,3,6,5};
    // int a = 1;
    // int b = 1;
    // int n = 3;
    // vector<int> r = {100,100,100};
    // int a = 2;
    // int b = 3;
    int n = 3;
    vector<int> r = {100, 100, 100};
    int a = 7;
    int b = 3;
    // int n = 4;
    // vector<int> r = {6,5,4,3};
    // int a = 10;
    // int b = 1;
    // int n = 4;
    // vector<int> r = {100,100,1,1};
    // int a = 2;
    // int b = 1;
    // int n = 6;
    // vector<int> r = {6, 5, 2, 4, 4, 7};
    // int a = 1;
    // int b = 1;
    
    printf("%lld\n", solve(n, r, a, b));
    return 0;
}