#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstring>
#include <string>

using namespace std;
using ll = long long;

struct Block {
    ll w;
    ll s;
    ll v;
};

const int NNODES = 1009;
const int NWEIGHTS = 2e4 + 7;
Block b[NNODES];
ll dp[NWEIGHTS];
ll t[NWEIGHTS];

bool cmp(Block a, Block b) {
    return (a.s + a.w) < (b.s + b.w);
}

ll solve(int n) {
    ll maxV = 0;
    dp[b[0].w] = b[0].v;
    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= b[i].s+b[i].w; j++) {
            if (j-b[i].w > 0 && dp[j-b[i].w] > 0) {
                t[j] = max(t[j], dp[j-b[i].w] + b[i].v);
            }
        }
        t[b[i].w] = max(t[b[i].w], b[i].v);

        for (int j = 1; j <= b[i].s+b[i].w; j++) {
            dp[j] = max(dp[j], t[j]);
            t[j] = 0;
        }
    }
    
    for (int j = 0; j <= NWEIGHTS; j++) {
        maxV = max(maxV, dp[j]);
    }
    return maxV;
}
int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        ll tw, ts, tv;
        cin >> tw >> ts >> tv;
        b[i] = Block{tw, ts, tv};
    }
    sort(b, b+n, cmp);
    // for (int i = 0; i < n; i++) {
    //     printf("%lld %lld %lld\n", b[i].w, b[i].s, b[i].v);
    // }
    printf("%lld\n", solve(n));
    return 0;
}