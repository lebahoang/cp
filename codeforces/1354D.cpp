#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstring>
#include <random>
// g++ -std=c++17 -Wall -lm -O2 -o s.out 1354D.cpp && time ./s.out < x.txt
// g++ -std=c++17 -Wshadow -Wall -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined -o s.out 1354D.cpp && ./s.out < x.txt
using namespace std;
using ll = int;
using getTwoNodeValueFunc = ll (*)(ll a, ll b);
using updateOneNodeValueFunc = ll (*)(ll a, ll b);
    
const ll NEG_INF = int(-1e9);
    
ll getAdd(ll a, ll b) {
    return a+b;
}
    
ll updateAdd(ll a, ll b) {
    return a+b;
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

struct FenwickTree {
    vector<int> bit;  // binary indexed tree
    int n;

    FenwickTree(int n) {
        this->n = n;
        bit.assign(n, 0);
    }

    FenwickTree(vector<int> a) : FenwickTree(a.size()) {
        for (size_t i = 0; i < a.size(); i++)
            add(i, a[i]);
    }

    int sum(int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void add(int idx, int delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }
};
     
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, q;
    // cin >> n >> q;
    scanf("%d%d",&n,&q);
    vector<int> a(n+5, 0);
    // SimpleSegmentTree tree(n+5, (getTwoNodeValueFunc)getAdd, (updateOneNodeValueFunc)updateAdd);
    FenwickTree tree(n+5);
    int cur = -1;
    ll cnt = 0;
    for (int i = 0; i < n; i++) {
        int ind;
        // cin >> ind;
        scanf("%d", &ind);
        if (cur == -1 || cur != ind) {
            if (cur != -1) {
                tree.add(cur, cnt);
                a[cur] += cnt;
            }
            cur = ind;
            cnt = 1;
        } else {
            cnt++;
        }
    }
    tree.add(cur, cnt);
    a[cur] += cnt;
    for (int i = 0; i < q; i++) {
        int x;
        // cin >> x;
        scanf("%d", &x);
        if (x > 0) {
            tree.add(x, 1);
            a[x]++;
        } else {
            x = -x;
            ll v = tree.sum(1);
            if (v >= x) {
                tree.add(1, -1);
                a[1]--;
                continue;
            }
            int l = 2;
            int r = n;
            while (l <= r) {
                int mid = (l+r)/2;
                // v = tree.query(1, mid);
                ll vprev = tree.sum(mid-1);
                v = vprev + a[mid];
                if (vprev < x && v >= x) {
                    tree.add(mid, -1);
                    a[mid]--;
                    break;
                } else if (vprev >= x) {
                    r = mid-1;
                } else {
                    l = mid+1;
                }
            }
        }
    }
    int ans = 0;
    if (tree.sum(1) > 0) {
        ans = 1;
    } else {
        int l = 1;
        int r = n;
        while (l <= r) {
            int mid = (l+r)/2;
            ll vprev = tree.sum(1, mid-1);
            ll v = vprev + a[mid];
            if (vprev == 0 && v > 0) {
                ans = mid;
                break;
            } else if (vprev > 0) {
                r = mid-1;
            } else {
                l = mid+1;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}