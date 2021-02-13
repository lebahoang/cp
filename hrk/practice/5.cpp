#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;
struct I {
    int val;
    int ind;
};
using getTwoNodeValueFunc = I (*)(I a, I b);
using updateOneNodeValueFunc = I (*)(I a, I b);

I getMin(I a, I b) {
    if (a.val == -1 && a.ind == -1) return b;
    if (b.val == -1 && b.ind == -1) return a;
    if (a.val < b.val) return a;
    if (a.val > b.val) return b;
    if (a.ind < b.ind) return a;
    if (a.ind > b.ind) return b;
    return a;
}

I updateMin(I a, I b) {
    if (a.val == -1 && a.ind == -1) return b;
    if (b.val == -1 && b.ind == -1) return a;
    if (a.val < b.val) return a;
    if (a.val > b.val) return b;
    if (a.ind < b.ind) return a;
    if (a.ind > b.ind) return b;
    return a;
}

I getMax(I a, I b) {
    if (a.val == -1 && a.ind == -1) return b;
    if (b.val == -1 && b.ind == -1) return a;
    if (a.val > b.val) return a;
    if (a.val < b.val) return b;
    if (a.ind < b.ind) return a;
    if (a.ind > b.ind) return b;
    return a;
}

I updateMax(I a, I b) {
    if (a.val == -1 && a.ind == -1) return b;
    if (b.val == -1 && b.ind == -1) return a;
    if (a.val > b.val) return a;
    if (a.val < b.val) return b;
    if (a.ind < b.ind) return a;
    if (a.ind > b.ind) return b;
    return a;
}

bool isNotFound(I x) {
    if (x.val == -1 && x.ind == -1) return true;
    return false;
}
class SimpleSegmentTree {
private:
    int numItems;
    vector<I> tree;
    getTwoNodeValueFunc getFunc;
    updateOneNodeValueFunc updateFunc;
    int getNumberOfNodes() {
        int x = int(ceil(log2(numItems)));
        return ((1-pow(2, x+1))/(1-2)) + 1;
    };
    void buildTree() {
        vector<I> t(getNumberOfNodes(), {-1, -1});
        tree = t;
    };
    void _update(I value, int ind, int start, int end, int l, int r){
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
    I _query(int ind, int start, int end, int l, int r) {
        if (start > r || end < l) {
            return {-1, -1};
        }

        if (start >= l && end <= r) {
            return tree[ind];
        }

        int mid = (start + end)/2;
        I a = _query(2*ind+1, start, mid, l, r);
        I b = _query(2*ind+2, mid+1, end, l, r);
        if (a.val == -1 && a.ind == -1) return b;
        if (b.val == -1 && b.ind == -1) return a;
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
    void update(I value, int ind){
        return _update(value, 0, 0, numItems-1, ind, ind);
    };
    I query(int l, int r) {
        return _query(0, 0, numItems-1, l, r);
    };
};


int solve(vector<int>& a) {
    int rs = 1;
    int n = 100005;
    SimpleSegmentTree tmin(n, (getTwoNodeValueFunc)getMin, (updateOneNodeValueFunc)updateMin);
    SimpleSegmentTree tmax(n, (getTwoNodeValueFunc)getMax, (updateOneNodeValueFunc)updateMax);
    int dp[(int)a.size()][2];
    memset(dp, 0, sizeof(dp));
    for (int i = a.size()-1; i >= 0; i--) {
        if (i < a.size()-1) {
            I x = tmin.query(a[i], n);
            I y = tmax.query(0, a[i]);
            printf("Value %d tmin (%d,%d) tmax (%d,%d)\n", a[i], x.val, x.ind, y.val, y.ind);
            if (!isNotFound(x)) {
                if (x.ind == a.size()-1 || dp[x.ind][1] == 1) {
                    rs++;
                    dp[i][0] = 1;
                } else dp[i][0] = 0;
            } else {
                dp[i][0] = 0;
            }

            if (!isNotFound(y)) {
                if (y.ind == a.size()-1 || dp[y.ind][0] == 1) dp[i][1] = 1;
                else dp[i][1] = 0;
            } else {
                dp[i][1] = 0;
            }
        } else {
            dp[i][0] = 1;
            dp[i][1] = 1;
        }

        tmin.update({a[i], i}, a[i]);
        tmax.update({a[i], i}, a[i]);
    }
    return rs;
}

int main() {
    // vector<int> a = {5,4,2,6,10,12,23,5,2,5,1,3};
    vector<int> a = {10,13,12,14,15};
    printf("%d\n", solve(a));
    return 0;
}