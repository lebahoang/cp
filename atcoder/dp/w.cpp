#include <iostream>
#include <stdio.h>
#include <vector>
#include <cmath>

using namespace std;
using ll = long long;
using getTwoNodeValueFunc = ll (*)(ll a, ll b);
using updateOneNodeValueFunc = ll (*)(ll a, ll b);

const ll NEG_INF = -1e12;
const int NMAX = 2e5 + 5;

ll getMax(ll a, ll b) {
    return max(a, b);
}

ll updateAdd(ll a, ll b) {
    return  a+b;
}

class LazySegmentTree {
private:
    int numItems;
    vector<ll> tree;
    vector<ll> lazy;
    getTwoNodeValueFunc getFunc;
    updateOneNodeValueFunc updateFunc;
    int getNumberOfNodes() {
        int x = int(ceil(log2(numItems)));
        return ((1-pow(2, x+1))/(1-2)) + 1;
    };
    void buildTree() {
        vector<ll> t1(getNumberOfNodes(), 0);
        tree = t1;
        vector<ll> t2(getNumberOfNodes(), 0);
        lazy = t2;
    };
    void _update(ll value, int ind, int start, int end, int l, int r) {
        // update value of 1 node in tree
        // [start, end] is an updating index interval of segment tree
        // [l, r] is user input index interval
        if (lazy[ind] != 0) {
            tree[ind] = updateFunc(tree[ind], lazy[ind]);
            if (start != end) {
                lazy[2*ind+1] = updateFunc(lazy[2*ind+1], lazy[ind]);
                lazy[2*ind+2] = updateFunc(lazy[2*ind+2], lazy[ind]);
            }    
            lazy[ind] = 0;
        }
            
        if (start > r || end < l) return;
        if (start >= l && end <= r) {
            tree[ind] = updateFunc(tree[ind], value);
            if (start != end) {
                lazy[2*ind+1] = updateFunc(lazy[2*ind+1], value);
                lazy[2*ind+2] = updateFunc(lazy[2*ind+2], value);
            }
            return;
        }
            
        int mid = (start+end)/2;
        _update(value, 2*ind+1, start, mid, l, r);
        _update(value, 2*ind+2, mid+1, end, l, r);
        tree[ind] = getFunc(tree[2*ind+1], tree[2*ind+2]);
    };
    ll _query(int ind, int start, int end, int l, int r) {
        if (lazy[ind] != 0) {
            tree[ind] = updateFunc(tree[ind], lazy[ind]);
            if (start != end) {
                lazy[2*ind+1] = updateFunc(lazy[2*ind+1], lazy[ind]);
                lazy[2*ind+2] = updateFunc(lazy[2*ind+2], lazy[ind]);
            }
            lazy[ind] = 0;
        }
            
        if (start > r || end < l) return NEG_INF;

        if (start >= l && end <= r) return tree[ind];

        int mid = (start + end)/2;
        ll a = _query(2*ind+1, start, mid, l, r);
        ll b = _query(2*ind+2, mid+1, end, l, r);
        if (a == NEG_INF) return b;
        else if (b == NEG_INF) return a;
        return getFunc(a, b);
    };
public:
    LazySegmentTree(int numItemsx, getTwoNodeValueFunc get, updateOneNodeValueFunc update) {
        numItems = numItemsx;
        getFunc = get;
        updateFunc = update;
        buildTree();
    };
    void update(ll value, int l, int r) {
        return _update(value, 0, 0, numItems-1, l, r);
    };
    ll query(int l, int r) {
        return _query(0, 0, numItems-1, l, r);
    };
};

struct P {
    int l;
    int r;
    ll val;
};
vector<P> v;
ll dp[NMAX] = {NEG_INF};
vector<ll> lefts[NMAX];
vector<int> rightToLefts[NMAX];
vector<ll> rights[NMAX];

ll solve(int n, int m) {
    for (int i = 0; i <= n; i++) dp[i] = NEG_INF;
    ll t = 0;
    for (int i = 0; i < m; i++) {
        if (v[i].l <= 1 && v[i].r >= 1) {
            t += v[i].val;
        }
    }
    dp[1] = t;
    // printf("%d %lld\n", 1, dp[1]);
    ll rs = dp[1];
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            ll t = 0;
            for (int k = 0; k < m; k++) {
                if (v[k].l <= i && v[k].r >= i && (v[k].l > j || v[k].r < j)) {
                    t += v[k].val;
                }
            }
            dp[i] = max(dp[i], dp[j]+t);
        }
        // printf("%d %lld\n", i, dp[i]);
        rs = max(dp[i], rs);
    }
    return max(ll(0), rs);
}

// ll solve1(int n, int m, LazySegmentTree tree) {
//     ll rs = 0;
//     for (int j = 0; j < lefts[1].size(); j++) {
//         rs += lefts[1][j];
//     }
//     tree.update(rs, 1, 1);
//     for (int i = 2; i <= n; i++) {
//         for (int j = 0; j < lefts[i].size(); j++) {
//             tree.update(lefts[i][j], 1, i-1);
//         }
//         dp[i] = tree.query(1, i-1);
//         // printf("%lld\n", dp[i]);
//         tree.update(dp[i], i, i);
//         for (int j = 0; j < rights[i].size(); j++) {
//             if (rightToLefts[i][j]-1 >= 1) {
//                 tree.update(rights[i][j], 1, rightToLefts[i][j]-1);
//             }
//         }
//         rs = max(rs, dp[i]);
//     }
//     return max(ll(0), rs);
// }


ll solve1(int n, int m, LazySegmentTree tree) {
    ll rs = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < lefts[i].size(); j++) {
            tree.update(lefts[i][j], 0, i-1);
        }
        dp[i] = tree.query(0, i-1);
        // printf("%lld\n", dp[i]);
        tree.update(dp[i], i, i);
        for (int j = 0; j < rights[i].size(); j++) {
            tree.update(rights[i][j], 0, rightToLefts[i][j]-1);
        }
        rs = max(rs, dp[i]);
    }
    return max(ll(0), rs);
}

int main() {
    int n, m, l, r;
    ll val;
    cin >> n >> m;
    LazySegmentTree tree(n+5, (getTwoNodeValueFunc)getMax, (updateOneNodeValueFunc)updateAdd);
    for (int i = 0; i < m; i++) {
        cin >> l >> r >> val;
        v.push_back({l,r,val});
        lefts[l].push_back(val);
        rightToLefts[r].push_back(l);
        rights[r].push_back(-val);
    }
    // printf("-----------\n");
    // printf("%lld\n", solve(n,m));
    printf("%lld\n", solve1(n,m,tree));
    return 0;
}
