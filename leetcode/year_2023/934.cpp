#include <random>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>

// g++ -std=c++17 -Wshadow -Wall -o s.out -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined 934.cpp && ./s.out
using namespace std;


bool isAtBorder(vector<vector<int>>& g, int n, int i, int j) {
    vector<vector<int>> t = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}  
    };
    for (vector<int>& x: t) {
        int a = x[0];
        int b = x[1];
        if (i+a >= 0 && i+a < n && j+b >= 0 && j+b < n && g[i+a][j+b] == 0) {
            return true;
        }
    }
    return false;
}
void dfs(vector<vector<int>>& g, int n, int i, int j,
    vector<vector<int>>& visited, vector<vector<int>>& rs) {

    if (isAtBorder(g, n, i, j)) {
        rs.push_back({i, j});
    }
    vector<vector<int>> t = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}  
    };
    for (vector<int>& x: t) {
        int a = x[0];
        int b = x[1];
        if (i+a >= 0 && i+a < n && j+b >= 0 && j+b < n && g[i+a][j+b] == 1 && visited[i+a][j+b] == 0) {
            visited[i+a][j+b] = 1;
            dfs(g,n,i+a,j+b,visited,rs);
        }
    }
}
int solve(vector<vector<int>>& g) {
    int n = g.size();
    vector<vector<int>> visited = vector(n, vector<int>(n, 0));
    vector<vector<int>> rs1 = {};
    vector<vector<int>> rs2 = {};
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (g[i][j] == 1 && visited[i][j] == 0) {
                visited[i][j] = 1;
                if (cnt == 0) {
                    dfs(g, n, i, j, visited, rs1);
                    cnt++;
                }
                else if (cnt == 1) dfs(g, n, i, j, visited, rs2);
            }
        }
    }
    int l = rs1.size();
    int m = rs2.size();
    printf("%d %d\n", l, m);
    int ans = 100000;
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < m; j++) {
            int v = abs(rs1[i][0] - rs2[j][0]) + abs(rs1[i][1]- rs2[j][1]) - 1;
            ans = min(ans, v);
        }
    }
    return ans;
}

int main() {
    vector<vector<int>> g = {
        {1,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,1,0}
    };
    printf("%d\n", solve(g));
}