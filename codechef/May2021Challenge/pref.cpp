#include <bits/stdc++.h>
 
using namespace std;
 
#define fast ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using ll = long long;
const ll mod = 1000000007;
 
vector<int> nodes[500001];
 
ll dfs(int node, int parent) {
    // multiset<int> s;
    vector<ll> s;
    for (int i : nodes[node]) {
        if (i == parent) continue;
        ll ans = dfs(i, node);
        // s.insert(ans);
        s.push_back(ans);
    }
    sort(s.begin(), s.end());
    ll res = 1;
    // for (auto i = s.rbegin(); i != s.rend(); i++) {
    //     res += (val++) * (*i);
    // }
    ll val = (ll)s.size();
    for (ll i: s) {
        res += val*i;
        val--;
    }
    return res;
}
 
ll solve(int n, ll x) {
    ll ans = dfs(1, -1);
    ll rs = (ans%mod * x%mod)%mod;
    return rs;
}
 
signed main() {
    int t = 1;
    cin >> t;
    while (t--) {
        int n;
        ll x; 
        cin >> n >> x;
        for (int i = 0; i < n - 1; i++) {
            int a, b;
            cin >> a >> b;
            nodes[a].push_back(b);
            nodes[b].push_back(a);
        }
        printf("%lld\n", solve(n, x));
        for (int i = 1; i <= n; i++) nodes[i].clear();
    }
}