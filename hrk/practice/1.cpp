#include <unistd.h>
#include <ios>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstring>

using namespace std;
using ll = long long;
using getTwoNodeValueFunc = ll (*)(ll a, ll b);
using updateOneNodeValueFunc = ll (*)(ll a, ll b);

const ll NEG_INF = -1e12;
ll updateAdd(ll a, ll b) {
    return a+b;
}
ll getMax(ll a, ll b) {
    return max(a,b);
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
        int nn = getNumberOfNodes();
        vector<ll> t1(nn, 0);
        tree = t1;
        vector<ll> t2(nn, 0);
        lazy = t2;
        printf("%d\n", nn);
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
    LazySegmentTree() {};
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


int main() {
    // int n, m;
    // cin >> n >> m;
    // LazySegmentTree tree(n+1, (getTwoNodeValueFunc)getMax, (updateOneNodeValueFunc)updateAdd);
    // int l, r;
    // ll k;
    // for (int i = 0; i < m; i++) {
    //     cin >> l >> r >> k;
    //     tree.update(k, l, r);
    // }
    // printf("%lld\n", tree.query(1, n));

    LazySegmentTree trees[10];
    for (int i = 0; i < 10; i++) {
        LazySegmentTree tree(1000000, (getTwoNodeValueFunc)getMax, (updateOneNodeValueFunc)updateAdd);
        trees[i] = tree;
    }
    for (int j = 0; j < 100000; j++) {
        for (int k = 0; k < 10; k++) {
            trees[k].update(1000000000, 0, 999999);
        }
    }
    printf("OK\n");
    return 0;
}