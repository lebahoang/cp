#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstring>
#include <random>
#include <map>
#include <set>
using namespace std;
// g++ -std=c++17 -Wshadow -Wall -o s.out -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined 2508.cpp && ./s.out

bool can_pair(set<tuple<int, int>>& s, int i, int j) {
    tuple<int, int> t;
    if (i > j) {
        t = make_tuple(j, i);
    } else {
        t = make_tuple(i, j);
    }
    if (s.find(t) == s.end()) return true;
    return false;
}

vector<int> getLeftNodes(vector<int>& nodes, int i, int j) {
    vector<int> rs = {};
    for (int x: nodes) {
        if (x != i && x != j) {
            rs.push_back(x);
        }
    }
    return rs;
}

int solve(int n, vector<vector<int>>& edges) {
    vector<int> cnt = vector(n+2, 0);
    set<tuple<int, int>> s;
    for (vector<int>& x: edges) {
        int a = x[0];
        int b = x[1];
        cnt[a]++;
        cnt[b]++;
        if (a > b) {
            s.insert(make_tuple(b, a));
        } else {
            s.insert(make_tuple(a, b));
        }
    }
    int oddCnt = 0;
    vector<int> nodes = {};
    for (int i = 1; i <= n; i++) {
        if (cnt[i]%2 == 1) {
            oddCnt++;
            nodes.push_back(i);
            // printf("oddCnt %d, node %d\n", oddCnt, i);
        }
    }
    // printf("oddCnt %d\n", oddCnt);
    if (oddCnt > 4) return false;
    if (oddCnt%2 == 1) return false;
    if (oddCnt == 0) return true;
    if (oddCnt == 2) {
        if (can_pair(s, nodes[0], nodes[1])) return true;
        if (n-oddCnt > 0) {
            for (int i = 1; i <= n; i++) {
                if (i == nodes[0] || i == nodes[1]) continue;
                if (can_pair(s, nodes[0], i) && can_pair(s, nodes[1], i)) {
                    return true;
                }
            }
        }
        return false;
    }
    for (int i = 1; i < 4; i++) {
        if (can_pair(s, nodes[0], nodes[i])) {
            vector<int> left = getLeftNodes(nodes, nodes[0], nodes[i]);
            if (can_pair(s, left[0], left[1])) {
                // printf("Pair [%d-%d] and [%d-%d]\n", nodes[0], nodes[i], left[0], left[1]);
                return true;
            }
        }
    }
    return false;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n = 5;
    vector<vector<int>> edges = {
        {1,2},
        {2,3},
        {3,4},
        {4,2},
        {1,4},
        {2,5}
    };
    // int n = 4;
    // vector<vector<int>> edges = {
    //     {1,2},
    //     {3,4}
    // };
    // int n = 4;
    // vector<vector<int>> edges = {
    //     {1,2},
    //     {1,3},
    //     {1,4}
    // };
    bool rs = solve(n, edges);
    if (rs) printf("true\n");
    else printf("false\n");
}