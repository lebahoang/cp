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

// g++ -std=c++14 -stdlib=libc++ -O2 -o s.out 4.cpp && ./s.out < x.txt
using namespace std;
using ll = long long;
vector<ll> rsOPT;
vector<ll> rsBF;
ll processOne(ll r, vector<ll>& arr, ll mod) {
    ll rr = r-1;
    if (arr[0]%2 == 1) return ((rr%mod * arr[0]%mod)%mod + arr[0]%mod)%mod;
    return ((rr%mod * (arr[0]-1)%mod)%mod + arr[0]%mod)%mod;
}
void bf(int n, vector<ll> arr, int q, vector<ll> r) {
    ll mod = 1e9 + 7;
    for (ll x: r) {
        ll rs = 0;
        for (int j = 1; j <= (int)x; j++) {
            int i = (j-1)%n + 1;
            if (i+1 < n && arr[i] == 1) {
                if (arr[i-1]%2 != 0) rs = (rs%mod + arr[i-1]%mod)%mod;
                else rs = (rs%mod + (arr[i-1]-1)%mod)%mod;
            } else {
                if (i == n) {
                    // printf("j %d i %d rs %lld\n", j, i, rs);
                    if (j == x) {
                        rs = (rs%mod + arr[i-1]%mod)%mod;
                    } else {
                        if (arr[i-1]%2 != 0) rs = (rs%mod + arr[i-1]%mod)%mod;
                        else rs = (rs%mod + (arr[i-1]-1)%mod)%mod;
                    }
                } else {
                    if (arr[i-1]%2 != 0) rs = (rs%mod + (arr[i-1]-1)%mod)%mod;
                    else rs = (rs%mod + arr[i-1]%mod)%mod;
                }
            }
        }
        rsBF.push_back(rs);
        printf("%lld\n", rs);
    }

}
void solve(int n, vector<ll> arr, int q, vector<ll> r) {
    ll mod = 1e9 + 7;
    bool changed = false;
    int indChanged = -1;
    ll a = 0;
    ll b = 0;
    int lprefixa = 0;
    int lprefixb = 0;
    vector<ll> prefixa = {};
    vector<ll> prefixb = {};
    for(int i = 0; i < n; i++) {
        // printf("i %d, %lld\n", i, arr[i]);
        if (arr[i] == 1 && i < n-1) {
            changed = true;
            indChanged = i;
        } else {
            if (!changed) {
                if (arr[i]%2 == 0) {
                    if (i == n-1 || (i+1 < n-1 && arr[i+1] == 1)) {
                        a = (a%mod + (arr[i]-1)%mod)%mod;
                        if (lprefixa > 0) prefixa.push_back((prefixa[(int)prefixa.size()-1] + (arr[i]-1)%mod)%mod);
                        else prefixa.push_back((arr[i]-1)%mod);
                    } else {
                        a = (a%mod + arr[i]%mod)%mod;
                        if (lprefixa > 0) prefixa.push_back((prefixa[(int)prefixa.size()-1] + arr[i]%mod)%mod);
                        else prefixa.push_back(arr[i]%mod);
                    }
                } else {
                    if (i < n-1 && i+1 < n-1 && arr[i+1] == 1) {
                        a = (a%mod + arr[i]%mod)%mod;
                        if (lprefixa > 0) prefixa.push_back((prefixa[(int)prefixa.size()-1] + arr[i]%mod)%mod);
                        else prefixa.push_back(arr[i]%mod);
                    } else {
                        a = (a%mod + (arr[i]-1)%mod)%mod;
                        if (lprefixa > 0) prefixa.push_back((prefixa[(int)prefixa.size()-1] + (arr[i]-1)%mod)%mod);
                        else prefixa.push_back((arr[i]-1)%mod);
                    }
                }
                lprefixa++;
            } else {
                if (arr[i]%2 == 0) {
                    if (i < n-1) {
                        b = (b%mod + arr[i]%mod)%mod;
                        if (lprefixb > 0) prefixb.push_back((prefixb[(int)prefixb.size()-1] + arr[i]%mod)%mod);
                        else prefixb.push_back(arr[i]%mod);
                    } else {
                        b = (b%mod + (arr[i]-1)%mod)%mod;
                        if (lprefixb > 0) prefixb.push_back((prefixb[(int)prefixb.size()-1] + (arr[i]-1)%mod)%mod);
                        else prefixb.push_back((arr[i]-1)%mod);
                    }
                } else {
                    if (i < n-1) {
                        b = (b%mod + (arr[i]-1)%mod)%mod;
                        if (lprefixb > 0) prefixb.push_back((prefixb[(int)prefixb.size()-1] + (arr[i]-1)%mod)%mod);
                        else prefixb.push_back((arr[i]-1)%mod);
                    } else {
                        b = (b%mod + arr[i]%mod)%mod;
                        if (lprefixb > 0) prefixb.push_back((prefixb[(int)prefixb.size()-1] + arr[i]%mod)%mod);
                        else prefixb.push_back(arr[i]%mod);
                    }
                    
                }
                lprefixb++;
            }
        }
    }
    // for (ll x: arr) {
    //     printf("%lld ", x);
    // }
    // printf("\n");
    for (ll x: r) {
        if (n == 1) {
            rsOPT.push_back(processOne(x, arr, mod));
            printf("%lld\n", processOne(x, arr, mod));
            continue;
        }
        if (arr[0] == 1) {
            int xt = x%n;
            ll rs = (x-xt)/n;
            if (xt > 0) {
                rs = (rs+1)%mod;
            }
            rsOPT.push_back(rs);
            printf("%lld\n", rs);
            continue;
        }
        ll rs = 0;
        int r1 = x%n;
        ll r2 = (x-r1)/n;
        if (!changed) {
            if (r1 == 0) {
                if (r2-1 >= 0) rs = (rs%mod + ((r2-1)%mod * (a+b)%mod)%mod)%mod;
                rs = (rs%mod + prefixa[n-2] + arr[n-1]%mod)%mod;
            } else {
                rs = (rs%mod + (r2%mod * (a+b)%mod)%mod)%mod;
                r1--;
                ll temp = 0;
                if (r1-1 >= 0) temp = (temp%mod + prefixa[r1-1])%mod;
                rs = (rs%mod + temp%mod + arr[r1]%mod)%mod;
            }
        } else {
            if (r1 == 0) {
                rs = (rs%mod + ((r2-1)%mod * (a+b)%mod)%mod)%mod;
                // printf("ddsdas %lld\n", rs);
                ll temp = 0;
                if (lprefixa > 0) temp = (temp%mod + prefixa[lprefixa-1])%mod;
                if (lprefixb-2 >= 0) temp = (temp%mod + prefixb[lprefixb-2]%mod)%mod; 
                // printf("ddsdas %lld\n", temp);
                rs = (rs%mod + temp%mod + arr[n-1]%mod)%mod;
                // printf("ddsdas %lld\n", rs);
            } else {
                rs = (rs%mod + (r2%mod * (a+b)%mod)%mod)%mod;
                r1--;
                ll temp = 0;
                if (r1 < indChanged) {
                    if (r1-1 >= 0) temp = (temp%mod + prefixa[r1-1]%mod)%mod;
                } else if (r1 == indChanged) {
                    if (r1-2 >= 0) temp = (temp%mod + prefixa[r1-2]%mod)%mod;
                    if (arr[r1-1]%2 == 0) temp = (temp%mod + arr[r1-1]%mod)%mod;
                    else temp = (temp%mod + (arr[r1-1]-1)%mod)%mod;
                } else {
                    temp = (temp%mod + prefixa[lprefixa-1])%mod;
                    if (r1-indChanged-2 >= 0) temp = (temp%mod + prefixb[r1-indChanged-2]%mod)%mod;
                }
                rs = (rs%mod + temp%mod + arr[r1]%mod)%mod;
            }
        }
        // printf("%lld %lld\n", x, rs);
        rsOPT.push_back(rs);
        printf("%lld\n", rs);
    }
}
int main() {
    int t;
    cin >> t;
    for (int cs = 0; cs < t; cs++) {
        int n;
        cin >> n;
        vector<ll> arr(n,0);
        for (int i = 0; i < n; i++) cin >> arr[i];
        int q;
        cin >> q;
        vector<ll> r(q, 0);
        for (int i = 0; i < q; i++) cin >> r[i];
        // solve(n, arr, q, r);
        bf(n, arr, q, r);
        // for (int i = 0; i < q; i++) {
        //     if (rsOPT[i] != rsBF[i]) {
        //         printf("R %lld, rsOPT %lld, rsBF %lld\n", r[i], rsOPT[i], rsBF[i]);
        //         return 0;
        //     }
        // }
    }
    return 0;
}