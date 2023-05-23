#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstring>
#include <random>

using namespace std;
using ll = long long;
using getTwoNodeValueFunc = ll (*)(ll a, ll b);
using updateOneNodeValueFunc = ll (*)(ll a, ll b);

const ll NEG_INF = -1e12;

ll getMax(ll a, ll b) {
    return max(a, b);
}

ll getAdd(ll a, ll b) {
    return a+b;
}

ll update(ll a, ll b) {
    return max(a, b);
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
        printf("%d\n", (int)tree.size());
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

int main() {
    // vector<ll> arr = {1,2,3,4,5,6,7,8,9,10};
    // int n = arr.size();
    // SimpleSegmentTree tree(n, (getTwoNodeValueFunc)getMax, (updateOneNodeValueFunc)update);
    // for (int i = 0; i < n; i++) {
    //     tree.update(arr[i], i);
    // }

    // vector<vector<int>> arr = {
    //     {2,4,5},
    //     {2,5,6},
    //     {5,7,10}
    // };
    // int n = 2e5 + 5;
    // LazySegmentTree tree(n, (getTwoNodeValueFunc)getMax, (updateOneNodeValueFunc)updateAdd);
    // for (int i = 0; i < arr.size(); i++) {
    //     int l = arr[i][0];
    //     int r = arr[i][1];
    //     ll val = ll(arr[i][2]);
    //     tree.update(val, l, r);
    // }

    // random_device rd; // obtain a random number from hardware
    // mt19937 eng(rd()); // seed the generator
    // uniform_int_distribution<> distribution(0, n-1); // define the range
    // int nTimes = 2e5 + 7;
    // for (int i = 0; i < nTimes; i++) {
    //     int l = distribution(eng);
    //     int r = min(n, l+10);
    //     // printf("%d %d %lld\n", l, r, tree.query(l, r));
    // }
    // printf("%lld\n", tree.query(2,3));
    // return 0;

    int n = 1000;
    SimpleSegmentTree trees[n];
    for (int i = 0; i < n; i++) {
        SimpleSegmentTree tree(5e6+5, (getTwoNodeValueFunc)getAdd, (updateOneNodeValueFunc)updateAdd);
        trees[i] = tree;
    }
    printf("OK\n");
    for (int i = 0; i < n; i++) {
        trees[i].update(5,3);
        printf("%lld\n", trees[i].query(3, 3+525600));
    }
    return 0;
}