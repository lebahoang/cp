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

// g++ -std=c++14 -stdlib=libc++ -O2 -o s.out 1.cpp && ./s.out < x.txt
using namespace std;
using ll = long long;

int sum(int a, int n) {
    return (n*(2*a + n-1))/2;
}
void dfs(vector<int> a, int n, int i, int prefix, int c, int k, vector<int>& rs) {
    // for (int x: a) {
    //     printf("%d ", x);
    // }
    // printf("-------\n");
    if ((int)a.size() == n) {
        if (c == k) {
            rs = vector<int>(a.begin(), a.end());
        }
        return;
    }
    int left = k+1-c;
    if ((prefix - sum(i, left)) > 0) return;
    else {
        // printf("i %d left %d sum %d\n", i, left-1, sum(i, left-1));
        if ((prefix - sum(i, left-1)) > 0) {
            rs = vector<int>(a.begin(), a.end());
            int l = (int)a.size();
            int t = i;
            for (int j = 0; j < n-l; j++) {
                rs.push_back(-t);
                t++;
            }
            return;
        }
    }
    a.push_back(i);
    if (prefix + i > 0) {
        dfs(a, n, i+1, prefix + i, c+1, k, rs);
    } else {
        dfs(a, n, i+1, prefix + i, c, k, rs);
    }
    a.pop_back();
    if ((int)rs.size() > 0) return;
    a.push_back(-i);
    if (prefix - i > 0) {
        dfs(a, n, i+1, prefix - i, c+1, k, rs);
    } else {
        dfs(a, n, i+1, prefix - i, c, k, rs);
    }
    a.pop_back();
    return;
}
void solve() {
    int n, k;
    cin >> n >> k;
    // if (k == n) {
    //     for (int x = 1; x <= n; x++) {
    //         printf("%d ", x);
    //     }
    //     printf("\n");
    //     return;
    // }
    vector<int> a = {};
    vector<int> rs;
    dfs(a, n, 1, 0, 0, k, rs);
    for (int x: rs) {
        printf("%d ", x);
    }
    printf("\n");
}
int main() {
    int t;
    cin >> t;
    for (int cs = 0; cs < t; cs++) {
        solve();
    }
    return 0;
}
