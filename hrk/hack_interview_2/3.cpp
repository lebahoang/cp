#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;
int isFriendOf2[1000005];
vector<int> node[1000005];

bool dfs(int v) {
    if (isFriendOf2[v] == 1) return false;
    for (int i = 0; i < node[v].size(); i++) {
        if (node[v][i] != 1 && isFriendOf2[node[v][i]] == 1) return false;
    }
    return true;
}

string solve(int n, int m) {
    vector<int> res;
    // get all friends of 1
    vector<int> fof1;
    for (int i = 0; i < node[1].size(); i++) {
        if (node[1][i] != 2) fof1.push_back(node[1][i]);
    }
    // check each of these friends whether she/he could be invited
    for (int i = 0; i < fof1.size(); i++) {
        if (dfs(fof1[i])) {
            res.push_back(fof1[i]);
        }
    }
    sort(res.begin(), res.end());
    if (res.size() == 0) return "-1";
    string rs = "";
    for (int i = 0; i < res.size(); i++) {
        if (i < res.size()-1) {
            if (i == 0 || res[i] != res[i-1]) {
                rs += to_string(res[i]) + " ";
            }
        } else {
            if (res[i] != res[i-1]) {
                rs += to_string(res[i]);
            }
        }
    }
    return rs;
}

int main() {
    int t;
    cin >> t;
    int n,m,a,b;
    for (int i = 0; i < t; i++) {
        cin >> n >> m;
        for (int j = 0; j < m; j++) {
            cin >> a >> b;
            if (a == b) continue;
            // printf("%d %d \n", a, b);
            node[a].push_back(b);
            node[b].push_back(a);
            if (a == 2) isFriendOf2[b] = 1;
            if (b == 2) isFriendOf2[a] = 1;
        }
        printf("%s\n", solve(n, m).c_str());
        for (int k = 0; k <= 1000000; k++) {
            isFriendOf2[k] = 0;
            node[k].clear();
        }
    }
    return 0;
}