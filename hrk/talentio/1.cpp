#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstring>


using namespace std;
using ll = long long;
using updateFunc = void (*)(ll &a, ll b);

const int mod = 1e9 + 7;
const int NMAX = 5e4+4;
const int HEIGHTMAX = 5e4+4;

int h[NMAX];
int c[NMAX];
ll dp[NMAX][128];

ll tree[128][HEIGHTMAX];
// ll tree[HEIGHTMAX];

void updateMod(ll &x, ll y)
{
  x = (x%mod + y%mod) % mod;
}

void addMod(ll &x, ll y)
{
  x = (x%mod + y%mod) % mod;
}

void update( int mask, int ind, ll value, updateFunc f)
{
  for (int i = ind; i <= HEIGHTMAX; i += i & -i)
    // addMod(tree[mask][i], value);
    f(tree[mask][i], value);
}

ll query(int mask, int ind, updateFunc f)
{
  ll rs = 0;
  for (int i = ind; i; i -= i & -i) 
    // addMod(rs, tree[mask][i]);
    f(rs, tree[mask][i]);
  return rs;
}

ll solve(int n, int k) {
    ll rs = 0;
    int masks = (1 << k)-1;
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= masks; j++) {
            if ((j & (1 << (c[i]-1))) != 0) {
                ll a = query(j, h[i]-1, (updateFunc)addMod); // tree[j].query(0, h[i]-1);
                ll b = query(j^(1 << (c[i]-1)), h[i]-1, (updateFunc)addMod); // tree[j^(1 << (c[i]-1))].query(0, h[i]-1);
                if (j == (0 ^ (1 << (c[i]-1)))) {
                    dp[i][j] = (a%mod + b%mod + 1)%mod;
                } else {
                    dp[i][j] = (a%mod + b%mod)%mod;
                }
                // printf("%d %d %lld %lld %lld\n", h[i], j, a, b, dp[i][j]);
                update(j, h[i], dp[i][j], (updateFunc)addMod); // trees[j].update(dp[i][j], h[i]);
            }
        }
        rs = (rs%mod + dp[i][masks] % mod)%mod;
    }

    return rs;
}

int main() {
    int n,k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> h[i] >> c[i];
    }
    // printf("vvvvv\n");
    printf("%lld\n", solve(n,k));
    return 0;
}