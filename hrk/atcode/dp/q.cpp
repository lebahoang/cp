#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstring>
#include <string>
#include <queue>

using namespace std;
using ll = long long;

const int NS = 2 * 1e5 + 5;
ll h[NS];
ll a[NS];
ll dp[NS];

using getTwoNodeValueFunc = ll (*)(ll a, ll b);
using updateOneNodeValueFunc = ll (*)(ll a, ll b);
const ll NEG_INF = -1e12;

ll getMax(ll a, ll b) {
    return max(a, b);
}

ll update(ll a, ll b) {
    return max(a, b);
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


int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    SimpleSegmentTree tree(n+1, (getTwoNodeValueFunc)getMax, (updateOneNodeValueFunc)update);
    ll ans = a[0];
    dp[0] = a[0];
    tree.update(dp[0], h[0]);
    for (int i = 1; i < n; i++) {
        ll maxV = tree.query(1, h[i]-1);
        if (maxV == NEG_INF) maxV = 0;
        dp[i] = maxV + a[i];
        tree.update(dp[i], h[i]);
        if (ans < dp[i]) {
            ans = dp[i];
        }
    }
    printf("%lld\n", ans);
    return 0;
}