#include <cstdint>
#include <utility>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// #1 Additional explanations regardint the number of topological
// sortings of a tree. The clasic formula using combinations with repetitions
// may be straight forward or more easy to understand, but it may be hard to
// apply it with ease. On the other hand, looking closely at those combinations
// it's easy to see that a lot of the reduce and the final answer looks like
// N! / (subtree_size[1] * subtree_size[2] * .. * subtree_size[n])

using ll = long long;
const ll kMod = 1e9+7;
struct I {
    double ratio;
    ll sum;
    int node;
};
ll Pow(ll a, ll p) {
    ll res = 1;
    while (p) {
        if (p & 1) {
            res = (1LL * res%kMod * a%kMod) % kMod;
            // res = res * a;
        }
        a = (1LL * a%kMod * a%kMod) % kMod;
        // a = a*a;
        p /= 2;
    }

    return res;
}

// computes X! % kMod and 1 / X % kMod in O(kMaxN)
void Initialise(vector<ll>& fact, vector<ll>& inv_number, int n) {
    fact[0] = fact[1] = 1;
    for (int i = 2; i <= n; i++) {
        fact[i] = (1LL * i%kMod * fact[i - 1]%kMod) % kMod;
        // fact[i] = i * fact[i-1];
    }
    
    ll inv_fact = Pow(fact[n], kMod - 2);
 
    for (int i = n; i > 0; i--) {
        inv_number[i] = (1LL * inv_fact%kMod * fact[i - 1]%kMod) % kMod;
        inv_fact = (1LL * inv_fact%kMod * i%kMod) % kMod;
    }

    inv_number[0] = 1;
}

// roots the tree in node and computes the subtree_size for itself and all it's
// children (unvisited nodes)
void ComputeSubtree(int node, vector<bool>& visited, vector<vector<int>>& neighbour, vector<int>& subtree_size) {
    visited[node] = true;
    // printf("node %d\n", node);
    for (auto itr : neighbour[node]) {
        if (visited[itr]) {
            continue;
        }

        ComputeSubtree(itr, visited, neighbour, subtree_size);
        // printf("Child node %d\n", itr);
        subtree_size[node] += subtree_size[itr];
    }    

    subtree_size[node] += 1;
    // printf("node %d, size %d\n", node, subtree_size[node]);

    // nice hack. If you only do a DF on a tree you can do this so you don't
    // have to make the visited array equal to false afterwards.
    visited[node] = false;
}

bool cmp(I a, I b) {
    if (a.ratio > b.ratio) return true;
    if (a.ratio < b.ratio) return false;
    if (a.node > b.node) return true;
    return false;
}

// The answer for node is "sum"
// add it to the global result and change it to match the wanted sum for each child
// and solve for the recursively
void Solve(double ratio, int node, ll sum, vector<I>& ans,
    vector<bool>& visited, vector<vector<int>>& neighbour,
    vector<int>& subtree_size, vector<ll>& inv_number, int n) {

    I add{ratio, sum, node+1};
    ans.push_back(add);
    visited[node] = true;
    for (auto itr : neighbour[node]) {
        if (visited[itr]) {
            continue;
        }

        // if you have trouble understanding this formula read (#1) on the top of the source.
        // if we move the "root" from node to itr, subtree_size[itr] changes from subtree_size[itr]
        // to n and subtree_size[node] (root) changes from n to .. (n - subtree_size[itr])
        // we first must get rid of the previous / subtree_size[itr] and just add the new / (n - subtree_size[itr])
        double new_ratio = ratio*subtree_size[itr]/(n-subtree_size[itr]);
        ll new_sum = ((1LL * sum%kMod * subtree_size[itr]%kMod)%kMod * inv_number[n-subtree_size[itr]]%kMod)% kMod;
        Solve(new_ratio, itr, new_sum, ans, visited, neighbour, subtree_size, inv_number, n);
    }

    visited[node] = false;
}

int main() {
    int t;
    cin >> t;
    for (int cs = 0; cs < t; cs++) {
        int n, k;
        cin >> n >> k;
        vector<ll> fact(n+5, 0);
        vector<ll> inv_number(n+5, 0);
        Initialise(fact, inv_number, n+2);
        vector<vector<int>> neighbour(n+5, vector<int>{});
        vector<bool> visited(n+5, false);
        vector<bool> visited2(n+5, false);
        vector<int> subtree_size(n+5, 0);
        for (int i = 1; i < n; i++) {
            int a, b;
            cin >> a >> b;
            a -= 1;
            b -= 1;
            neighbour[a].push_back(b);
            neighbour[b].push_back(a);
        }
        // printf("1111\n");

        int root = 0;
        ComputeSubtree(root, visited, neighbour, subtree_size);
        // printf("dadas\n");

        // computing the answer for the root. (node 0, for example, it doesn't matter at all)
        ll root_answer = fact[n];
        for (int i = 0; i < n; i++) {
            root_answer = (1LL * root_answer%kMod * inv_number[subtree_size[i]]%kMod) % kMod;
        }

        vector<I> ans = {};
        Solve(1.0, root, root_answer, ans, visited2, neighbour, subtree_size, inv_number, n);
        sort(ans.begin(), ans.end(), cmp); 
        printf("%d %lld\n", ans[k-1].node, ans[k-1].sum);
    }
    return 0;
}
