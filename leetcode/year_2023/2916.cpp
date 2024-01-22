#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstring>
#include <random>

// g++ -std=c++17 -Wall -lm -O2 -o s.out 2916.cpp && time ./s.out < x.txt
// g++ -std=c++17 -Wshadow -Wall -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined -o s.out 2916.cpp && ./s.out < x.txt

using namespace std;
using ll = long long;
using getTwoNodeValueFunc = ll (*)(ll a, ll b);
using updateOneNodeValueFunc = ll (*)(ll a, ll b);

const ll NEG_INF = -1e12;

ll getTotal(ll a, ll b) {
    return a+b;
}

ll updateTotal(ll a, ll b) {
    return a+b;
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
            tree[ind] = updateFunc(tree[ind], (end - start + 1) * lazy[ind]);
            if (start != end) {
                lazy[2*ind+1] = updateFunc(lazy[2*ind+1], lazy[ind]);
                lazy[2*ind+2] = updateFunc(lazy[2*ind+2], lazy[ind]);
            }    
            lazy[ind] = 0;
        }
            
        if (start > r || end < l) return;
        if (start >= l && end <= r) {
            tree[ind] = updateFunc(tree[ind], (end - start + 1) * value);
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
            tree[ind] = updateFunc(tree[ind], (end - start + 1) * lazy[ind]);
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
    LazySegmentTree(int numItemsx, getTwoNodeValueFunc getF, updateOneNodeValueFunc updateF) {
        numItems = numItemsx;
        getFunc = getF;
        updateFunc = updateF;
        buildTree();
    };
    void update(ll value, int l, int r) {
        return _update(value, 0, 0, numItems-1, l, r);
    };
    ll query(int l, int r) {
        return _query(0, 0, numItems-1, l, r);
    };
};

int solve(vector<int>& arr) {
    ll mod = 1e9+7;
    int n = arr.size();
    LazySegmentTree tree(n+5, (getTwoNodeValueFunc)getTotal, (updateOneNodeValueFunc)updateTotal);
    vector<int> lastAppear(100005, -1);
    vector<ll> total(n+5, 0);
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        int num = arr[i];
        int lastInd = lastAppear[num];
        if (i > 0) {
            if (lastInd+1 <= i-1) {
                ll y = (i-1)-(lastInd+1)+1;
                ll d = tree.query(lastInd+1, i-1);
                // printf("I %d, lastInd %d,Y %lld, d %lld\n", i, lastInd, y, d);
                total[i] = (total[i-1]%mod + y%mod + (2*d)%mod)%mod;
            } else {
                total[i] = total[i-1]%mod;
            }
            total[i] = (total[i]%mod + 1)%mod;
        } else {
            total[i] = 1;
        }
        tree.update(1, lastInd+1, i);
        lastAppear[num] = i;
        ans = (ans%mod + total[i]%mod)%mod;
    }
    return (int)ans;
}
int main() {
    vector<int> arr = {1,2,3,4,5,2,3,2,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3};
    printf("Ans: %d\n", solve(arr));
    return 0;
}