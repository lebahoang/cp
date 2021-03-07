#include <cstdio>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <utility>

using namespace std;

void dfs1(int node, int n, int parent,
    vector<vector<int>>& neighbor,
    int nvisited, vector<bool> visited,
    vector<pair<int, int>>& rs, int& ans) {

    visited[node] = true;
    nvisited++;
    if (nvisited == n) {
        return;
    }
    for (int x: neighbor[node]) {
        if (x == parent) continue;
        dfs1(x, n, node, neighbor, )
    }
}

// g++ -std=c++14 -O2 -o s.out 2.cpp && ./s.out < x.txt
int minimumCost(int nodes, vector<int> from, vector<int> to, vector<int> w, int u, int v) {
 
}

int main() {

    return 0;
}