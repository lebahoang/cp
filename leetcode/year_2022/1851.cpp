#include <iostream>
#include <cstdio>
#include <algorithm>
#include <unordered_map>
#include <cmath>
#include <vector>
#include <cstring>
#include <random>

// g++ -std=c++17 -Wshadow -Wall -o s.out -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined 1851.cpp && ./s.out
using namespace std;
using ll = int;
using getTwoNodeValueFunc = ll (*)(ll a, ll b);
using updateOneNodeValueFunc = ll (*)(ll a, ll b);

const ll POS_INF = 1000000000;

ll get(ll a, ll b) {
    return min(a, b);
}

ll update(ll a, ll b) {
    return min(a, b);
}
struct Input {
    vector<vector<int>> r;
    vector<int> q;
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
        printf("number of nodes %d\n", getNumberOfNodes());
        vector<ll> t1(getNumberOfNodes(), POS_INF);
        tree = t1;
        vector<ll> t2(getNumberOfNodes(), POS_INF);
        lazy = t2;
    };
    void _update(ll value, int ind, int start, int end, int l, int r) {
        // update value of 1 node in tree
        // [start, end] is an updating index interval of segment tree
        // [l, r] is user input index interval
        if (lazy[ind] != POS_INF) {
            tree[ind] = updateFunc(tree[ind], lazy[ind]);
            if (start != end) {
                lazy[2*ind+1] = updateFunc(lazy[2*ind+1], lazy[ind]);
                lazy[2*ind+2] = updateFunc(lazy[2*ind+2], lazy[ind]);
            }    
            lazy[ind] = POS_INF;
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
        if (lazy[ind] != POS_INF) {
            tree[ind] = updateFunc(tree[ind], lazy[ind]);
            if (start != end) {
                lazy[2*ind+1] = updateFunc(lazy[2*ind+1], lazy[ind]);
                lazy[2*ind+2] = updateFunc(lazy[2*ind+2], lazy[ind]);
            }
            lazy[ind] = POS_INF;
        }
            
        if (start > r || end < l) return POS_INF;

        if (start >= l && end <= r) return tree[ind];

        int mid = (start + end)/2;
        ll a = _query(2*ind+1, start, mid, l, r);
        ll b = _query(2*ind+2, mid+1, end, l, r);
        if (a == POS_INF) return b;
        else if (b == POS_INF) return a;
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

void pp(vector<int>& a) {
    printf("----------\n");
    for (int x: a) printf("%d ", x);
    printf("\n");
}

void pp2d(vector<vector<int>>& a) {
    printf("----------\n");
    for (vector<int>& x: a) printf("[%d %d] ", x[0], x[1]);
    printf("\n");
}
vector<int> solve1(vector<vector<int>>& r, vector<int>& q) {
    int n = (int)q.size();
    vector<int> rs(n, -1);
    int m = (int)r.size();
    int maxV = -1;
    for (int i = 0; i < m; i++) {
        maxV = max(maxV, r[i][0]);
        maxV = max(maxV, r[i][1]);
    }
    for (int i = 0; i < n; i++) {
        maxV = max(maxV, q[i]);
    }
    // maxV = 10000000;
    LazySegmentTree tree(maxV+5, (getTwoNodeValueFunc)get, (updateOneNodeValueFunc)update);
    for (int i = 0; i < m; i++) {
        int k = r[i][1] - r[i][0] + 1;
        tree.update(k, r[i][0], r[i][1]);
    }
    for (int i = 0; i < n; i++) {
        int k = q[i];
        ll v = tree.query(k, k);
        // printf("dsads %lld\n", v);
        if (v == POS_INF) v = -1;
        rs[i] = (int)v;
    }
    return rs;
}
int search1(vector<int>& a, int v) {
    int n = (int)a.size();
    if (a[n-1] <= v) return n-1;
    if (a[0] > v) return -1;
    int l = 0;
    int r = n-1;
    while (l <= r) {
        int mid = (l+r)/2;
        if (a[mid] <= v && a[mid+1] > v) {
            return mid;
        } else if (a[mid] > v) {
            r = mid-1;
        } else {
            l = mid+1;
        }
    }
    return -1;
}
int search2(vector<int>& a, int v) {
    int n = (int)a.size();
    if (a[n-1] < v) return -1;
    if (a[0] >= v) return 0;
    int l = 0;
    int r = n-1;
    while (l <= r) {
        int mid = (l+r)/2;
        if (a[mid] < v && a[mid+1] >= v) {
            return mid+1;
        } else if (a[mid] >= v) {
            r = mid-1;
        } else {
            l = mid+1;
        }
    }
    return -1;
}
vector<int> solve(vector<vector<int>>& r, vector<int>& q) {
    vector<int> s = {};
    unordered_map<int, vector<int>> sa;

    vector<int> e = {};
    unordered_map<int, vector<int>> ea;

    int m = (int)r.size();
    sort(r.begin(), r.end(), [](vector<int>& a, vector<int>& b) {
        if (a[0] != b[0]) return a[0] < b[0];
        return a[1] < b[1];
    });
    int cur = -1;
    vector<int> t = {};
    for (int i = 0; i < m; i++) {
        if (cur == -1 || cur != r[i][0]) {
            if (cur > -1) {
                s.push_back(cur);
                sa[cur] = vector<int>(t.begin(), t.end());
                t.clear();
            }
            cur = r[i][0];
            t.push_back(r[i][1]);
        } else {
            t.push_back(r[i][1]);
        }
    }
    s.push_back(cur);
    sa[cur] = vector<int>(t.begin(), t.end());
    t.clear();

    sort(r.begin(), r.end(), [](vector<int>& a, vector<int>& b) {
        if (a[1] != b[1]) return a[1] < b[1];
        return a[0] < b[0];
    });
    cur = -1;
    for (int i = 0; i < m; i++) {
        if (cur == -1 || cur != r[i][1]) {
            if (cur > -1) {
                e.push_back(cur);
                ea[cur] = vector<int>(t.begin(), t.end());
                t.clear();
            }
            cur = r[i][1];
            t.push_back(r[i][0]);
        } else {
            t.push_back(r[i][0]);
        }
    }
    e.push_back(cur);
    ea[cur] = vector<int>(t.begin(), t.end());
    t.clear();
    
    printf("AAAAAAA\n");
    pp(s);
    for (auto it = sa.begin(); it != sa.end(); it++) {
        printf("%d :\n", it->first);
        pp(it->second);
        printf("++++++++\n");
    }
    printf("BBBBBBBB\n");
    pp(e);
    for (auto it = ea.begin(); it != ea.end(); it++) {
        printf("%d :\n", it->first);
        pp(it->second);
        printf("++++++++\n");
    }
    // search1 search2
    int n = (int)q.size();
    vector<int> rs(n, -1);
    for (int i = 0; i < n; i++) {
        int x = search1(s, q[i]);
        int y = search2(e, q[i]);
        printf("X %d Y %d\n", x, y);
        if (x == -1 || y == -1) rs[i] = -1;
        else {
            while (true) {
                int i1 = search2(sa[s[x]], q[i]);
                int i2 = search1(ea[e[y]], q[i]);
                printf("I1 %d I2 %d\n", i1, i2);
                if (i1 == -1 && i2 == -1) {
                    x--;
                    y++;
                    if (x < 0 || y == (int)e.size()) {
                        rs[i] = -1;
                        break;
                    }
                } else {
                    int v1 = POS_INF;
                    int v2 = POS_INF;
                    if (i1 != -1) {
                        v1 = sa[s[x]][i1] - s[x] + 1;
                    }
                    if (i2 != -1) {
                        v2 = e[y] - ea[e[y]][i2] + 1;
                    }
                    rs[i] = min(v1, v2);
                    break;
                }

            }
        }
    }
    return rs;
}


Input generate_input() {
    random_device dev;
    mt19937 rng(dev());
    // uniform_int_distribution<std::mt19937::result_type> dist(1,10000003);
    uniform_int_distribution<std::mt19937::result_type> dist(1,100);
    int n = 10;
    int m = 10;
    vector<vector<int>> r(m, vector<int>(2, 0));
    for (int i = 0; i < m; i++) {
        r[i][0] = dist(rng);
        r[i][1] = r[i][0] + min(90, (int)dist(rng));
    }
    vector<int> q(n, 0);
    for (int i = 0; i < n; i++) {
        q[i] = dist(rng);
    }
    Input x{r, q};
    return x;
}

int main() {
    // vector<vector<int>> r = {
    //     {1,4}, {2,4}, {3,6}, {4,4}
    // };
    // vector<int> q = {2,3,4,5};
    // vector<vector<int>> r = {
    //     {2,3}, {2,5}, {1,8}, {20,25}
    // };
    // vector<int> q = {2,19,5,22};
    vector<vector<int>> r = {
        {21,22}, {20,36}, {20,57}, {17,69}, {2,74}, {46,78}, {44, 103}, {75, 110}, {92, 119}, {56, 132}
    };
    vector<int> q = {62};
    vector<int> rs = solve(r, q);
    vector<int> rs1 = solve1(r, q);
    

    // Input x = generate_input();
    // vector<int> rs = solve(x.r, x.q);
    // vector<int> rs1 = solve1(x.r, x.q);
    for (int i = 0; i < (int)rs.size(); i++) {
        // printf("%d ", v);
        if (rs[i] != rs1[i]) {
            printf("I %d %d %d\n", q[i], rs1[i], rs[i]);
            pp2d(r);
            pp(q);
            break;
        }
    }
    printf("\n");
    return 0;
}