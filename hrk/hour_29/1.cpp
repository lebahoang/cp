#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <queue>

using namespace std;
using ll = long long;
const ll mod = 1e9+7;
const int NMAX = 1e5 + 6;

vector<int> v[NMAX];
int fatherOf[NMAX];
vector<int> vcolor;


ll dp[NMAX][2];


void dfs(int root) {
    ll t = 0;
    for (int x: v[root]) {
        if (t == 0) t = 1;
        if (fatherOf[root] == x) {
            continue;
        }
        fatherOf[x] = root;
        dfs(x);
        if (dp[x][0] == 1) {
            t = (t%mod * dp[x][0]%mod)%mod;
        } else {
            t = (t%mod * (dp[x][0]%mod + 1)%mod)%mod;
        }
    }
    if (vcolor[root] == 1) {
        dp[root][0] = 0;
        dp[root][1] = t;
    } else {
        dp[root][0] = t;
        if (v[root].size() == 1) {
            if (fatherOf[root] == v[root][0]) {
                dp[root][1] = 0;
            } else {
                dp[root][1] = dp[v[root][0]][1]%mod;
            }
        } else {
            vector<ll> prefix(v[root].size(), 1);
            vector<ll> suffix(v[root].size(), 1);
            for (int i = 0; i < v[root].size(); i++) {
                int x = v[root][i];
                if (fatherOf[root] == x) continue;
                if (i == 0) {
                    if (dp[x][1] == 0) {
                        prefix[i] = dp[x][0]%mod;
                    } else {
                        prefix[i] = (dp[x][0]%mod + 1%mod)%mod;
                    }
                } else {
                    if (dp[x][1] == 0) {
                        prefix[i] = (prefix[i-1]%mod * dp[x][0]%mod)%mod;
                    } else {
                        prefix[i] = (prefix[i-1]%mod * (dp[x][0]%mod + 1%mod)%mod)%mod;
                    }
                    
                }
            }
            for (int i = v[root].size()-1; i >= 0; i--) {
                int x = v[root][i];
                if (fatherOf[root] == x) continue;
                if (i == v[root].size()-1) {
                    if (dp[x][1] == 0) {
                        suffix[i] = dp[x][0]%mod;
                    } else {
                        suffix[i] = (dp[x][0]%mod + 1%mod)%mod;
                    }
                    
                } else {
                    if (dp[x][1] == 0) {
                        suffix[i] = (suffix[i+1]%mod * dp[x][0]%mod)%mod;
                    } else {
                        suffix[i] = (suffix[i+1]%mod * (dp[x][0]%mod + 1%mod)%mod)%mod;
                    }
                        
                }
            }
            for (int i = 0; i < v[root].size(); i++) {
                int x = v[root][i];
                if (fatherOf[root] == x) continue;
                if (i == 0) {
                    dp[root][1] = (dp[root][1]%mod + (suffix[i+1]%mod * dp[x][1]%mod)%mod)%mod;
                } else if (i == v[root].size()-1) {
                    dp[root][1] = (dp[root][1]%mod + (prefix[i-1]%mod * dp[x][1]%mod)%mod)%mod;
                } else {
                    dp[root][1] = (dp[root][1]%mod + (prefix[i-1]%mod * suffix[i+1]%mod * dp[x][1]%mod)%mod)%mod;
                }
            }
        }
    }
}

ll solve(int n) {
    dfs(0);
    for (int i = 0; i < n; i++) {
        printf("%d %lld %lld\n", i, dp[i][0], dp[i][1]);
    }
    return dp[0][1];
}

int main() {
    int n;
    cin >> n;
    int pi;
    for (int i = 0; i < n-1; i++) {
        cin >> pi;
        v[i+1].push_back(pi);
        v[pi].push_back(i+1);
    }
    int c;
    for (int i = 0; i < n; i++) {
        cin >> c;
        vcolor.push_back(c);
    }
    printf("%lld\n", solve(n));
    return 0;
}