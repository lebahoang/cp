#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <utility>

using namespace std;
using ll = long long;
using getTwoNodeValueFunc = ll (*)(ll a, ll b);
using updateOneNodeValueFunc = ll (*)(ll a, ll b);

const ll NEG_INF = -1e12;
ll c[1000007];
ll dp[1000007];

ll getMin(ll a, ll b) {
    return min(a, b);
}

ll updateAdd(ll a, ll b) {
    return  a+b;
}

class SimpleSegmentTree {
private:
    int numItems;
    vector<ll> tree;
    getTwoNodeValueFunc getFunc;
    updateOneNodeValueFunc updateFunc;
    int getNumberOfNodes() {
        int x = int(ceil(log2(numItems)));
        return ((1-pow(2, x+1))/(1-2)) + 1;
    };
    void buildTree() {
        vector<ll> t(getNumberOfNodes(), 0);
        tree = t;
    };
    void _update(ll value, int ind, int start, int end, int l, int r){
        // update value of 1 node in tree
        // [start, end] is an updating index interval of segment tree
        // print(start, end, l, r)
        if (start > r || end < l) {
            return;
        }

        if (start >= l && end <= r) {
            tree[ind] = updateFunc(tree[ind], value);
            return;
        }
            
        int mid = (start+end)/2;
        _update(value, 2*ind+1, start, mid, l, r);
        _update(value, 2*ind+2, mid+1, end, l, r);

        tree[ind] = getFunc(tree[2*ind+1], tree[2*ind+2]);
    };
    ll _query(int ind, int start, int end, int l, int r) {
        if (start > r || end < l) {
            return NEG_INF;
        }

        if (start >= l && end <= r) {
            return tree[ind];
        }

        int mid = (start + end)/2;
        ll a = _query(2*ind+1, start, mid, l, r);
        ll b = _query(2*ind+2, mid+1, end, l, r);
        if (a == NEG_INF) return b;
        if (b == NEG_INF) return a;
        return getFunc(a, b);
    };
public:
    SimpleSegmentTree () {};
    SimpleSegmentTree (int numItemsx, getTwoNodeValueFunc get, updateOneNodeValueFunc update) {
        numItems = numItemsx;
        getFunc = get;
        updateFunc = update;
        buildTree();
    };
    void update(ll value, int ind){
        return _update(value, 0, 0, numItems-1, ind, ind);
    };
    ll query(int l, int r) {
        return _query(0, 0, numItems-1, l, r);
    };
};

ll solve(int n, int m) {
    if (n <= m) return 0;
    SimpleSegmentTree tree(n+1, (getTwoNodeValueFunc)getMin, (updateOneNodeValueFunc)updateAdd);
    dp[0] = 0;
    tree.update(dp[0], 0);
    for (int i = 1; i < n; i++) {
        // ll t = 1e18;
        // for (int j = max(0, i-m); j < i; j++) {
        //     if (j == 0) {
        //         t = dp[j];
        //     } else if (c[j] > 0) {
        //         t = min(t, dp[j] + c[j]);
        //     }
        // }
        // dp[i] = t;
        ll minV = tree.query(max(0, i-m), i-1);
        dp[i] = minV;
        if (c[i] == 0) {
            tree.update(1e18, i);
        } else {
            tree.update(dp[i] + c[i], i);
        }
    }
    if (dp[n-1] >= 1e18) return -1;
    return dp[n-1];
}
int main() {
    int t;
    cin >> t;
    int n, m;
    for (int cc = 0; cc < t; cc++) {
        cin >> n >> m;
        for (int j = 0; j < n; j++) {
            cin >> c[j]; 
        }
        printf("Case #%d: %lld\n", cc+1, solve(n, m));
    }
    return 0;
}