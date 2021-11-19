#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <set>
#include <vector>
#include <queue>
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

queue<pair<int, int>> generate(int r, int c) {
    queue<pair<int, int>> q;
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            q.push({i,j});
        }
    }
    return q;
}
pair<string, vector<pair<int, int>>> solve2(int r, int c) {
    pair<string, vector<pair<int, int>>> ans = {};
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            bool done = true;
            queue<pair<int, int>> qt = generate(r, c);
            queue<pair<int, int>> qt2;
            int sz = qt.size();
            pair<int, int> k = {i, j};
            vector<pair<int,int>> t = {};
            int iter = 0;
            // printf("i %d j %d\n", i, j);
            while (!qt.empty()) {
                pair<int, int> x = qt.front();
                qt.pop();
                if (k.first == x.first || k.second == x.second || k.first-k.second == x.first-x.second || k.first+k.second == x.first+x.second) {
                    iter++;
                    if (iter == sz) {
                        done = false;
                        break;
                    }
                    if (i == x.first && j == x.second) continue;
                    qt2.push(x);
                } else {
                    // printf("add %d %d\n", k.first, k.second);
                    t.push_back(k);
                    k = x;
                    while (!qt2.empty()) {
                        auto it = qt2.front();
                        qt2.pop();
                        qt.push(it);
                    }
                    // printf("assign %d %d, left %d\n", k.first, k.second, (int)qt.size());
                    sz = qt.size();
                    iter = 0;
                }
            }
            if (done) {
                t.push_back(k);
                ans.first = "POSSIBLE";
                ans.second = vector<pair<int, int>>(t.begin(), t.end());
                return ans;
            }
        }
    }
    ans.first = "IMPOSSIBLE";
    return ans;
}
void check() {
    int r = 20;
    int c = 20;
    vector<string> nineteen = {};
    vector<string> twenty = {};
    for (int cs = 1; cs <= 100; cs++) {
        auto ans2 = solve2(20, 20);
    }
    // for (int j = 2; j <= c; j++) {
    //     for (int i = 2; i <= r; i++) {
    //         // auto ans1 = solve(i,j);
    //         auto ans2 = solve2(i,j);
    //         // if (ans1.first != ans2.first) {
    //         //     printf("AAAAA i %d, j %d, %s, %s\n", i, j, ans1.first.c_str(), ans2.first.c_str());
    //         //     return;
    //         // }
    //         // string x = "{";
    //         // for (auto it: ans.second) {
    //         //     x += "{" + to_string(it.first) + "," + to_string(it.second) + "},";
    //         // }
    //         // x = "}";
    //         // if (j == 19) nineteen.push_back(x);
    //         // else twenty.push_back(x);
    //     }
    // }
    
}
int main() {
    int t;
    cin >> t;
    for (int cs = 1; cs <= t; cs++) {
        int r,c;
        cin >> r >> c;
        pair<string, vector<pair<int, int>>> t;
        // if (r <= 10 && c <= 10) {
        //     t = solve(r,c);
        // } else {
        //     t = solve2(r,c);
        // }
        t = solve2(r,c);
        if (t.first == "IMPOSSIBLE") {
            t = solve(r,c);
        }
        printf("Case #%d: %s\n", cs, t.first.c_str());
        for (auto x: t.second) {
            printf("%d %d\n", x.first, x.second);
        }
    }
    // check();
    return 0;
}
