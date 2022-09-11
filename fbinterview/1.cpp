#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
// Write any include statements here
struct X {
  double val;
  double t;
  double d;
};
using getTwoNodeValueFunc = X (*)(X a, X b);
using updateOneNodeValueFunc = X (*)(X a, X b);

const double NEG_VAL = -(1e9+7);
X getMax(X a, X b) {
  if(a.val >= b.val) return a;
  return b; 
}

X updateMax(X a, X b) {
  if (b.t == -1 && b.d == -1) {
    if (a.t != -1 && a.d != -1) {
        if (b.val == 0) {
            a.val = a.d*a.t;
        } else {
            a.val += a.d * b.val;
        }
    } else {
        // printf("A[%.6f %.6f %.6f] B[%.6f %.6f %.6f]\n", a.val, a.d, a.t, b.val, b.d, b.t);
        if (a.val == NEG_VAL) a.val = b.val;
        else a.val += b.val;
    }
    return a;
  } else {
    if(a.val >= b.val) return a;
    return b;
  }
}


class LazySegmentTree {
private:
    int numItems;
    vector<X> tree;
    vector<X> lazy;
    getTwoNodeValueFunc getFunc;
    updateOneNodeValueFunc updateFunc;
    int getNumberOfNodes() {
        int x = int(ceil(log2(numItems)));
        return ((1-pow(2, x+1))/(1-2)) + 1;
    };
    void buildTree() {
        vector<X> t1(getNumberOfNodes(), X{0, 0, 0});
        tree = t1;
        vector<X> t2(getNumberOfNodes(), X{NEG_VAL, -1, -1});
        lazy = t2;
    };
    void _update(X value, int ind, int start, int end, int l, int r) {
        // update value of 1 node in tree
        // [start, end] is an updating index interval of segment tree
        // [l, r] is user input index interval
        if (lazy[ind].val > NEG_VAL) {
            tree[ind] = updateFunc(tree[ind], lazy[ind]);
            if (start != end) {
                lazy[2*ind+1] = updateFunc(lazy[2*ind+1], lazy[ind]);
                lazy[2*ind+2] = updateFunc(lazy[2*ind+2], lazy[ind]);
            }    
            lazy[ind] = X{NEG_VAL, -1, -1};
        }

        if (start > r || end < l) return;
        if (start >= l && end <= r) {
            printf("start %d end %d value [%.6f %.6f %.6f]\n", start, end, value.d, value.t, value.val); 
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
    X _query(int ind, int start, int end, int l, int r) {
        if (lazy[ind].val > NEG_VAL) {
            tree[ind] = updateFunc(tree[ind], lazy[ind]);
            if (start != end) {
                lazy[2*ind+1] = updateFunc(lazy[2*ind+1], lazy[ind]);
                lazy[2*ind+2] = updateFunc(lazy[2*ind+2], lazy[ind]);
            }
            lazy[ind] = X{NEG_VAL, -1, -1};
        }
            
        if (start > r || end < l) return X{NEG_VAL, -1, -1};

        if (start >= l && end <= r) return tree[ind];

        int mid = (start + end)/2;
        X a = _query(2*ind+1, start, mid, l, r);
        X b = _query(2*ind+2, mid+1, end, l, r);
        if (a.val == NEG_VAL) return b;
        else if (b.val == NEG_VAL) return a;
        return getFunc(a, b);
    };
public:
    LazySegmentTree(int numItemsx, getTwoNodeValueFunc get, updateOneNodeValueFunc update) {
        numItems = numItemsx;
        getFunc = get;
        updateFunc = update;
        buildTree();
    };
    void update(X value, int l, int r) {
        return _update(value, 0, 0, numItems-1, l, r);
    };
    X query(int l, int r) {
        return _query(0, 0, numItems-1, l, r);
    };
};

double bf(int N, vector<int> H, vector<int> D, int B) {
    double rs = -1.0;
    for (int i = 0; i < N; i++) {
        double t = (double)H[i]/(1.0 * B);
        double d = (double)D[i];
        double ans = 0;
        for (int j = 0; j < N; j++) {
            if (i == j) continue;
            double tj = (double)H[j]/(1.0 * B);
            double ansT = t*d + 1.0*t*D[j] + 1.0*tj*D[j];
            printf("DI %.6f TI %.6f DJ %.6f TJ %.6f ANST %.6f\n", d, t, (double)D[j], tj, ansT-t*d);
            ans = max(ans, ansT);
        }
        printf("BRUTEFORCE DI %.6f TI %.6f ANS %.6f\n", d, t, ans);
        rs = max(rs, ans);
    }
    return rs;
}

// double getMaxDamageDealt(int N, vector<int> H, vector<int> D, int B) {
//   SimpleSegmentTree tree1(N+5, (getTwoNodeValueFunc)getMax, (updateOneNodeValueFunc)updateMax);
//   SimpleSegmentTree tree2(N+5, (getTwoNodeValueFunc)getMax, (updateOneNodeValueFunc)updateMax);
//   SimpleSegmentTree tree3(N+5, (getTwoNodeValueFunc)getMax, (updateOneNodeValueFunc)updateMax);
//   for (int i = 0; i < N; i++) {
//     double t = (double)H[i]/(1.0 * B);
//     double d = (double)D[i];
//     tree1.update(X{d, t, d}, i);
//     tree2.update(X{d*t, t, d}, i);
//     tree3.update(X{d+t*d, t, d}, i);
//   }
//   double rs = -1.0;
//   for (int i = 0; i < N; i++) {
//     double t = (double)H[i]/(1.0 * B);
//     double d = (double)D[i];
//     X k1 = INIT_VAL;
//     X k2 = INIT_VAL;
//     X k3 = INIT_VAL;
//     if (i-1 >= 0) {
//       k1 = tree1.query(0, i-1);
//       k2 = tree2.query(0, i-1);
//       k3 = tree3.query(0, i-1);
//     }
//     if (i+1 < N) {
//       X v = tree1.query(i+1, N-1);
//       X vv = tree2.query(i+1, N-1);
//       X vvv = tree3.query(i+1, N-1);
//       if (v.val > k1.val) k1 = v;
//       if (vv.val > k2.val) k2 = vv;
//       if (vvv.val > k3.val) k3 = vvv;
//     }
//     double ans1 = t*d + t*k1.d + k1.t*k1.d;
//     double ans2 = t*d + t*k2.d + k2.t*k2.d;
//     double ans3 = t*d + t*k3.d + k3.t*k3.d;
//     // printf("DI %.6f TI %.6f {k1: D %.6f T %.6f ANS1 %.6f} {k2: D %.6f T %.6f ANS2 %.6f}\n", d, t, k1.d, k1.t, ans1, k2.d, k2.t, ans2);
//     rs = max({rs, ans1, ans2, ans3});
//   }
//   return rs;
// }

double getMaxDamageDealt(int N, vector<int> H, vector<int> D, int B) {
    LazySegmentTree tree(N, (getTwoNodeValueFunc)getMax, (updateOneNodeValueFunc)updateMax);
    for (int i = 0; i < N; i++) {
        double t = (double)H[i]/(1.0 * B);
        double d = (double)D[i];
        tree.update(X{t*d, t, d}, i, i);
    }
    for (int j = 0; j < N; j++) {
        X x = tree.query(j,j);
        printf("%.6f ", x.val);
    }
    printf("\n------\n");
    double rs = 0;
    for (int i = 0; i < N; i++) {
        double t = (double)H[i]/(1.0 * B);
        double d = (double)D[i];
        // tree.update(X{t, -1, -1}, 0, N-1);
        double ans = 0;
        if (i-1 >= 0) {
            tree.update(X{t, -1, -1},0, i-1);
            X v = tree.query(0, i-1);
            tree.update(X{-t, -1, -1},0, i-1);
            tree.query(0, i-1);
            ans = max(ans, v.val);
        }
        if (i+1 < N) {
            tree.update(X{t, -1, -1},i+1, N-1);
            X v = tree.query(i+1, N-1);
            tree.update(X{-t, -1, -1},i+1, N-1);
            tree.query(i+1, N-1);
            ans = max(ans, v.val);
        }
        ans += t*d;
        printf("DI %.6f TI %.6f ANST %.6f ANS %.6f\n", d, t, ans-t*d, ans);
        rs = max(rs, ans);
        // tree.update(X{-t, -1, -1}, 0, N-1);
        // tree.query(0, N-1);
        // for (int j = 0; j < N; j++) {
        //     X x = tree.query(j,j);
        //     printf("%.6f ", x.val);
        // }
        // printf("\n");
    }
    return rs;
}

// int main() {
//     // int N = 3;
//     // vector<int> H = {2,1,4};
//     // vector<int> D = {3,1,2};
//     // int B = 4;
//     // printf("%.9f\n", getMaxDamageDealt(N, H, D, B));
//     return 0;
// }

int main() {
    int t;
    cin >> t;
    for (int cs = 0; cs < t; cs++) {
        int n;
        cin >> n;
        vector<int> h(n, 0);
        vector<int> d(n, 0);
        for (int i = 0; i < n; i++) {
            cin >> h[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> d[i];
        }
        int b;
        cin >> b;
        double rs1 = bf(n, h, d, b);
        double rs2 = getMaxDamageDealt(n, h, d, b);
        if (rs1 != rs2) {
            printf("RS1 %.9f, RS2 %.9f, N %d B %d\n", rs1, rs2, n, b);
            for (int i = 0; i < n; i++) {
                printf("%d ", h[i]);
            }
            printf("\n");

            for (int i = 0; i < n; i++) {
                printf("%d ", d[i]);
            }
            printf("\n");
        }
    }
    return 0;
}