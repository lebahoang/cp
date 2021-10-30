#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

void dfs(vector<vector<int>>& neighbor, vector<vector<int>>& d, int s, int node, int calD, vector<bool>& visited) {
    visited[node] = true;
    if (d[s][node] > calD) {
        d[s][node] = calD;
    }
    for (int j: neighbor[node]) {
        if (!visited[j] || calD+1 < d[s][j]) {
            dfs(neighbor, d, s, j, calD+1, visited);
        }
    }
}
int solve(string s, int k, vector<string>& x) {
    vector<vector<int>> d(26, vector<int>(26, 1e9));
    vector<vector<int>> neighbor(26, vector<int>{});
    vector<bool> visited(26, false);
    for (string &i: x) {
        neighbor[i[0]-'A'].push_back(i[1]-'A');
    }
    // dfs
    for (int i = 0; i < 26; i++) {
        dfs(neighbor, d, i, i, 0, visited);
        // printf("I %c\n", i+'A');
    }
    int total = 1e9;
    for (int j = 0; j < 26; j++) {
        int t = 0;
        for (char& i: s) {
            int val = d[i-'A'][j];
            if (val == 1e9) {
                t = 1e9;
                break;
            }
            t += val;
        }
        if (t < 1e9) total = min(total, t);
    }
    if (total == 1e9) return -1;
    return total;
}
int main() {
    int t;
    cin >> t;
    for (int c = 0; c < t; c++) {
        string s;
        int k;
        cin >> s;
        cin >> k;
        vector<string> x(k, "");
        for (int i = 0; i < k; i++) {
            cin >> x[i];
        }
        printf("Case #%d: %d\n", c+1, solve(s, k, x));
    }
    return 0;
}