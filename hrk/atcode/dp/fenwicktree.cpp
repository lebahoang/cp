#include <cstdio>
#include <iostream>
#include <cmath>

using namespace std;
using ll = long long;
using updateFunc = void (*)(ll &a, ll b);
const int mod = 1e9 + 7;
const int HEIGHTMAX = 5e4+4;

ll tree[130][HEIGHTMAX];
// ll tree[HEIGHTMAX];

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


int main() {
    for (int i = 0; i < 6000000; i++) {
        int tind = min(127, i);
        update(tind, 50, 1, (updateFunc)addMod);
        ll rs = query(tind, 50, (updateFunc)addMod);
        // if (rs < 500) {
            // printf("%d %lld\n", tind, rs);
        // }
    }
    return 0;
}
