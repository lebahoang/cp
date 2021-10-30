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

// g++ -std=c++14 -stdlib=libc++ -O2 -o s.out 41.cpp && ./s.out < x.txt
// g++ -std=c++14 -stdlib=libc++ -O2 -o s.out 41.cpp && ./s.out < ~/Downloads/running_on_fumes_chapter_1_input.txt > out41.txt
using namespace std;
using ll = long long;

const int mod = 1e9 + 7;
const int nmax = 1e6 + 7;
int l[nmax], h[nmax];

ll total[nmax];
ll dp[nmax];

struct I {
    ll h;
    ll l;
};

int mul(ll a, ll b, int mod) {
    return (ll) a * b % mod;
}
int add(ll a, ll b, int mod) {
    a += b;
    if(a >= mod)
        a -= mod;
    return a; 
}

int sub(ll a,ll b, int mod){
    a -= b;
    if(a < 0)
        a += mod;
    return a;
}

int point2interval(int i, vector<pair<int, int>> intervals) {
    int l = 0;
    int r = (int)intervals.size()-1;
    while (true) {
        if (l > r) break;
        int mid = (l+r)/2;
        int s = intervals[mid].first;
        int e = intervals[mid].second;
        if (s <= i && e >= i) return mid;
        if (s > i) {
            r = mid-1;
        } else if (e < i) {
            l = mid+1;
        }
    }
    return -1;
}
int solve(int n, int w, vector<pair<int, int>> intervals, vector<I> ps) {
    // for (int i = 0; i < n; i++) printf("%d ", l[i]);
    // printf("\n");
    // for (int i = 0; i < n; i++) printf("%d ", h[i]);
    // printf("\n");
    // for (int i = 0; i < (int)intervals.size(); i++) printf("%d %d\n", intervals[i].first, intervals[i].second);
    // printf("\n");
    dp[0] = mul(add(w, h[0], mod), 2, mod);
    printf("P %lld\n",dp[0]);
    total[0] = dp[0];
    for (int i = 1; i < n; i++) {
        // ll p = (((ps[i].h+l[i]+w-ps[i].l)%mod)*2)%mod;
        // ll p = (((ps[i].h+l[i]+w-ps[i].l)%mod)*2)%mod;
        ll p = mul(add(ps[i].h, l[i]+w-ps[i].l, mod), 2, mod);
        int j = point2interval(i, intervals);
        if (j-1 >= 0) {
            // total[i] = (p%mod + total[intervals[j-1].second]%mod)%mod;
            total[i] = add(p, total[intervals[j-1].second], mod);
        } else {
            total[i] = p%mod;
        }
        // printf("%d %d, t %lld, total %lld\n", ps[i].h, l[i]+w-ps[i].l, p, total[i]);
        // printf("j %d, maxH %lld, s %lld, p %lld, P %lld\n", j, ps[i].h, ps[i].l, p, total[i]);
        // dp[i] = ((dp[i-1]%mod) * (total[i]%mod))%mod;
        // dp[i] = (dp[i-1]*total[i])%mod;
    }
    ll rs = 1;
    for (int i = 0; i < n; i++) {
        // rs = ((rs%mod) * (total[i]%mod))%mod;
        rs = mul(rs, total[i], mod);
    }
    return rs;
}
int main() {
    int cases;
    cin >> cases;
    for(int cs = 0; cs < cases; cs++) {
        int n,k,w;
        cin >> n >> k >> w;
        for (int i = 0; i < k; i++) {
            cin >> l[i];
        }
        int a,b,c,d;
        cin >> a >> b >> c >> d;
        for (int i = k; i < n; i++) {
            // l[i] = ((((a%d)*(l[i-2]%d))%d + ((b%d)*(l[i-1]%d))%d + c%d)%d) + 1;
            // l[i] = (a*l[i-2] + b*l[i-1] + c)%d + 1;
            l[i] = (mul(a, l[i-2], d) + mul(b, l[i-1], d) + c)%d + 1;
        }
        for (int i = 0; i < k; i++) {
            cin >> h[i];
        }
        cin >> a >> b >> c >> d;
        for (int i = k; i < n; i++) {
            // h[i] = ((((a%d)*(h[i-2]%d))%d + ((b%d)*(h[i-1]%d))%d + c%d)%d) + 1;
            // h[i] = (a*h[i-2] + b*h[i-1] + c)%d + 1;
            h[i] = (mul(a, h[i-2], d) + mul(b, h[i-1], d) + c)%d + 1;
        }
        vector<pair<int, int>> intervals = {};
        vector<I> ps = {};
        int s = 0;
        int e = 0;
        int maxH = h[0];
        ps.push_back({maxH, l[s]});
        for (int i = 1; i < n; i++) {
            if (l[i] <= l[i-1]+w) {
                e = i;
                maxH = max(maxH, h[i]);
            } else {
                intervals.push_back({s, e});
                s = i;
                e = i;
                maxH = h[i];
            }
            ps.push_back({maxH, l[s]});
        }
        if (e == -1) {
            e = s;
        }
        intervals.push_back({s, e});
        printf("Case #%d: %d\n", cs+1, solve(n,w, intervals, ps));
    }
    
    return 0;
}