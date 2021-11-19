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
#include <unordered_map>

// g++ -std=c++14 -stdlib=libc++ -O2 -o s.out 2.cpp && ./s.out < x.txt
using namespace std;
using ll = long long;
const int nax = 505;
int dp[nax][nax];
struct I {
    int p;
    int r;
    int i;
};
int solve() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= k; j++) {
            if (r[i] == 0) {
                for (int a = 0; a < i; a++) {
                    if (p[x] == p[i] && r[x] == 1)
                }
            } else {

            }
        }
    }
}
int main() {
    int t;
    cin >> t;
    vector<I> a(nax, {-1,-1,-1});
    for (int cs = 1; cs <= t; cs++) {
        setDP();
        printf("PPPP\n");
        int n,k,pi,ri;
        cin >> n >> k;
        for (int i = 0; i < n; i++) {
            cin >> pi >> ri;
            a[i] = {pi, ri, i};
        }
        printf("Case #%d: %d\n", cs, solve(n, k, a));
    }
    return 0;
}
