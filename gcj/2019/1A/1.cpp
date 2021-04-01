#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <set>
#include <vector>
#include <utility>

// g++ -std=c++17 -O2 -o s.out 1.cpp && ./s.out < x.txt
using namespace std;
void dfs(int x, int y, int r, int c,
    vector<vector<int>>& visited, int nv,
    vector<pair<int, int>>& path, pair<string, vector<pair<int, int>>>& ans) {
    
    // printf("nv %d\n", nv);
    if (nv == r*c) {
        ans.first = "POSSIBLE";
        ans.second = vector<pair<int, int>>(path.begin(), path.end());
        return;
    }
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            if (visited[i][j] == 1 || i == x || j == y || i-j == x-y || i+j == x+y) {
                continue;
            }
            visited[i][j] = 1;
            path.push_back({i,j});
            dfs(i,j,r,c,visited,nv+1,path,ans);
            path.pop_back();
            visited[i][j] = 0;
            if (ans.first != "") return;
            break;
        }
    }
}
pair<string, vector<pair<int, int>>> solve(int r, int c) {
    pair<string, vector<pair<int, int>>> ans;

    vector<vector<int>> visited(r+1, vector<int>(c+1, 0));
    vector<pair<int, int>> path = {};
    int f = 0;
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            visited[i][j] = 1;
            path.push_back({i,j});
            dfs(i,j,r,c,visited,1,path,ans);
            path.pop_back();
            visited[i][j] = 0;
            // printf("i %d j %d, ans %s\n", i, j, ans.first.c_str());
            if (ans.first != "") {
                f = 1;
                break;
            };
        }
        if (f == 1) break;
    }
    // int i = 1;
    // int j = 2;
    // visited[i][j] = 1;
    // path.push_back({i,j});
    // dfs(i,j,r,c,visited,1,path,ans);
    // path.pop_back();
    // visited[i][j] = 0;
    // printf("i %d j %d, ans %s\n", i, j, ans.first.c_str());
    if (ans.first == "") ans.first = "IMPOSSIBLE";
    return ans;
}
void check() {
    int r = 20;
    int c = 20;
    vector<string> nineteen = {};
    vector<string> twenty = {};
    for (int j = 19; j <= c; j++) {
        for (int i = 1; i <= r; i++) {
            auto ans = solve(i,j);
            string x = "{";
            for (auto it: ans.second) {
                x += "{" + to_string(it.first) + "," + to_string(it.second) + "},";
            }
            x = "}";
            if (j == 19) nineteen.push_back(x);
            else twenty.push_back(x);
        }
    }
    
}
int main() {
    // int t;
    // cin >> t;
    // for (int cs = 1; cs <= t; cs++) {
    //     int r,c;
    //     cin >> r >> c;
    //     pair<string, vector<pair<int, int>>> t = solve(r,c);
    //     printf("Case #%d: %s\n", cs, t.first.c_str());
    //     for (auto x: t.second) {
    //         printf("%d %d\n", x.first, x.second);
    //     }
    // }
    check();
    return 0;
}
