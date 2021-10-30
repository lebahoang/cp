#include <iostream>
#include <algorithm>
#include <vector>
#include <stdio.h>

using namespace std;
const int NNodes = 1e5 + 9;

int p[NNodes];
int rankAtNode[NNodes];

void initDisjoinSet(int n) {
    for (int i = 0; i < n; i++) {
        p[i] = i;
        rankAtNode[i] = 0;
    }
}

int findSubset(int x) {
    // apply path compression
    // which is the idea: moving the sub tree rooted at x to be a child of root node
    if (x == p[x]) {
        return x;
    }
    p[x] = findSubset(p[x]);
    return p[x];
}

void union2Subsets(int x, int y) {
    // apply union by rank
    // which is the idea: attach the smaller-depth tree into the bigger depth tree
    // more specifically the root node of smaller tree will become a child of the root node
    // of bigger tree
    int xroot = findSubset(x);
    int yroot = findSubset(y);
    if (xroot == yroot) {
        return;
    }
    if (rankAtNode[xroot] >= rankAtNode[yroot]) {
        p[yroot] = xroot;
        if (rankAtNode[xroot] == rankAtNode[yroot] ) {
            rankAtNode[xroot]++;
        }
    } else if (rankAtNode[xroot] < rankAtNode[yroot]) {
        p[xroot] = yroot;
    }
}

int main() {
    int n = 100;
    initDisjoinSet(n);
    int o = 1;
    vector<int> a{4,5,6,7,8,2,3};
    for (int i = 0; i < a.size(); i++) {
        union2Subsets(o, a[i]);
    }
    for (int i = 0; i < a.size(); i++) {
        cout << findSubset(a[i]) << "\n";
    }
    int oo = 10;
    vector<int> aa{40,50,60,70,80,20,30,55,77,88,13,14};
    for (int i = 0; i < aa.size(); i++) {
        union2Subsets(oo, aa[i]);
    }
    for (int i = 0; i < aa.size(); i++) {
        cout << findSubset(aa[i]) << "\n";
    }
    int ooo = 33;
    vector<int> aaa{34,35,36,37,38};
    for (int i = 0; i < aaa.size(); i++) {
        union2Subsets(ooo, aaa[i]);
    }
    for (int i = 0; i < aaa.size(); i++) {
        cout << findSubset(aaa[i]) << "\n";
    }
    union2Subsets(oo, ooo);
    union2Subsets(o, oo);
    cout << findSubset(o) << "   " << findSubset(oo) << "\n";
    return 0;
}