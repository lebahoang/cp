#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <map>
#include <set>
using namespace std;
using ll = long long;
const int mod = 1e9+7;

// For test speed: g++ -std=c++17 -Wall -lm -O2 -o s.out 2.cpp && time ./s.out < x.txt
// g++ -std=c++17 -Wshadow -Wall -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined -o s.out 717E.cpp && ./s.out < x.txt

bool dfs(int parent, int node, vector<vector<int>>& nei, vector<int>& color, vector<int>& t) {
    bool has = false;
    t.push_back(node);
    if (color[node] == -1) {
        has = true;
        color[node] = 1;
    }
    int n = (int)nei[node].size();
    for (int i = 0; i < n; i++) {
        if (nei[node][i] == parent) continue;
        bool cHas = dfs(node, nei[node][i], nei, color, t);
        has = has | cHas;
        t.push_back(node);
        if (node == 1 && i == n-1 && color[node] == 1) continue;
        if (color[node] == 1) color[node] = -1;
        else color[node] = 1;
    }
    return has;
}
int main() {
    int n;
    cin >> n;
    vector<int> color(n+1, 0);
    for (int i = 0; i < n; i++) {
        cin >> color[i+1];
    }
    int a = -1;
    int b = -1;
    vector<vector<int>> nei(n+1, vector<int>());
    for (int i = 0; i < n; i++) {
        cin >> a >> b;
        nei[a].push_back(b);
        nei[b].push_back(a);
    }
    vector<int> rs = {};
    while (true) {
        vector<int> trs = {};
        int root = 1;
        bool has = dfs(-1, root, nei, color, trs);
        for (int& x: trs) {
            printf("%d ", x);
        }
        printf("----------\n");
        if (!has) break;
        else {
            rs.insert(rs.end(), trs.begin(), trs.end());
        }
    }
    for (int& x: rs) {
        printf("%d ", x);
    }
    printf("\n");
    return 0;
}
