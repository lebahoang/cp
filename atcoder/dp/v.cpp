#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <vector>
#include <string>
#include <string.h>
#include <queue>

using namespace std;

using ll = long long;
const int NNODES = 1e5 + 6;
vector<int> v[NNODES];
int fatherOf[NNODES];

ll down[NNODES], up[NNODES], prefix[NNODES], suffix[NNODES];

ll dfsDown(int root, int m) {
    vector<int> l;
    ll temp = 1;
    for(int node: v[root]) {
        if (fatherOf[root] == node) {
            continue;
        }
        fatherOf[node] = root;
        temp = ((temp % m) * (1 + (dfsDown(node, m)%m)) % m ) % m;

        // calculate prefix, suffix
        l.push_back(node);
    }

    ll t = 1;
    for (int i = 0; i < l.size(); i++) {
        // pair<int, int> a(root, l[i]);
        prefix[l[i]] = t;
        t = ((t%m) * ((1 + (down[l[i]]%m))%m)) % m;
        // printf("sss %d, %d, %lld\n", root, l[i], prefix[{root, l[i]}]);
    }
    t = 1;
    for (int i = l.size()-1; i >= 0; i--) {
        // pair<int, int> a(root, l[i]);
        suffix[l[i]] = t;
        t = ((t%m) * ((1 + (down[l[i]]%m))%m)) % m;
    }
    down[root] = temp%m;
    return down[root];
}

ll dfsUp(int root, int m) {
    if (up[root] > 1) {
        return up[root];
    } 
    if (fatherOf[root] == -1) {
        up[root] = 1;
        return up[root];
    }
    ll upV = dfsUp(fatherOf[root], m);
    ll kk = ((prefix[root]%m) * (suffix[root]%m)) % m;
    up[root] = (((kk * (upV%m)) % m) + 1) %m;
    return up[root];
}

void solve(int n, int m) {
    int root = 1;
    fatherOf[root] = -1;
    dfsDown(root, m);
    for (int i = 1; i <= n; i++) {
        dfsUp(i, m);
    }
    queue<int> q;
    q.push(root);
    while (q.size() > 0) {
        int it = q.front();
        q.pop();
        dfsUp(it, m);
        for (int node: v[it]) {
            if (node == fatherOf[it]) {
                continue;
            }
            q.push(node);
        }
    }
}

int main() {
    memset(down, -1, sizeof(down));
    memset(up, -1, sizeof(up));
    memset(prefix, 1, sizeof(prefix));
    memset(suffix, 1, sizeof(suffix));
    int n,m;
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        int a,b;
        cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    solve(n, m);
    for (int i = 1; i <= n; i++) {
        // printf("father of %d %d\n", i, fatherOf[i]);
        // printf("down %d %d\n", i, down[i]);
        // printf("up %d %d\n", i, up[i]);
        printf("%lld\n", (down[i] * up[i])%m);
    }
	return 0;
}