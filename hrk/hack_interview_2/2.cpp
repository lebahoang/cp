#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;
struct Node {
    char x;
    int val;
};
char arr[300005];

using getTwoNodeValueFunc = Node (*)(Node a, Node b);
using updateOneNodeValueFunc = Node (*)(Node a, Node b);

Node updateMax(Node a, Node b) {
    if (a.x < b.x) {
        return Node{b.x, b.val};
    } else if (a.x > b.x) {
        return Node{a.x, a.val};
    }
    return Node{a.x, a.val+b.val};
}

Node getMax(Node a, Node b) {
    if (a.x < b.x) {
        return Node{b.x, b.val};
    } else if (a.x > b.x) {
        return Node{a.x, a.val};
    }
    return Node{a.x, a.val+b.val};
}


class SimpleSegmentTree {
private:
    int numItems;
    vector<Node> tree;
    getTwoNodeValueFunc getFunc;
    updateOneNodeValueFunc updateFunc;
    int getNumberOfNodes() {
        int x = int(ceil(log2(numItems)));
        return ((1-pow(2, x+1))/(1-2)) + 1;
    };
    void buildTree() {
        vector<Node> t(getNumberOfNodes(), Node{'.', 0});
        tree = t;
    };
    void _update(Node value, int ind, int start, int end, int l, int r){
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
    Node _query(int ind, int start, int end, int l, int r) {
        if (start > r || end < l) {
            return Node{'.', -1};
        }

        if (start >= l && end <= r) {
            return tree[ind];
        }

        int mid = (start + end)/2;
        Node a = _query(2*ind+1, start, mid, l, r);
        Node b = _query(2*ind+2, mid+1, end, l, r);
        if (a.val == -1) return b;
        if (b.val == -1) return a;
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
    void update(Node value, int ind){
        return _update(value, 0, 0, numItems-1, ind, ind);
    };
    Node query(int l, int r) {
        return _query(0, 0, numItems-1, l, r);
    };
};

int main() {
    int n, q;
    cin >> n;
    string k;
    cin >> k;
    SimpleSegmentTree tree(n, (getTwoNodeValueFunc)getMax, (updateOneNodeValueFunc)updateMax);
    for (int i = 0; i < n; i++) {
        tree.update(Node{char(tolower(k[i])), 1}, i);
    }
    cin >> q;
    int s,e;
    for (int i = 0; i < q; i++) {
        cin >> s >> e;
        printf("%d\n", tree.query(s, e).val);
    }
    return 0;
}