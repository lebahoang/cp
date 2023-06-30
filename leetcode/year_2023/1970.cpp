#include <random>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;
// g++ -std=c++17 -Wshadow -Wall -o s.out -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined 1970.cpp && ./s.out
void initDisjoinSet(int n, vector<int>& p, vector<int>& rankAtNode) {
    for (int i = 0; i < n; i++) {
        p[i] = i;
        rankAtNode[i] = 0;
    }
}

int findSubset(int x, vector<int>& p) {
    // apply path compression
    // which is the idea: moving the sub tree rooted at x to be a child of root node
    if (x == p[x]) {
        return x;
    }
    p[x] = findSubset(p[x], p);
    return p[x];
}

void union2Subsets(int x, int y, vector<int>& p, vector<int>& rankAtNode) {
    // apply union by rank
    // which is the idea: attach the smaller-depth tree into the bigger depth tree
    // more specifically the root node of smaller tree will become a child of the root node
    // of bigger tree
    int xroot = findSubset(x, p);
    int yroot = findSubset(y, p);
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

int solve(int r, int c, vector<vector<int>>& g) {
    int n = g.size();
    vector<int> p(n+1, 0);
    vector<int> rankAtNode(n+1, 0);
} 
int main() {
    return 0;
}