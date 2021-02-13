#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
#include <cstring>
using namespace std;

const int NMAX = 103;
int dist[NMAX][NMAX];
vector<int> v[NMAX];
vector<int> vAtDist[NMAX];

void bfs(int n, int s) {
    vector<int> visited(n+1, 0);
    queue<pair<int, int>> q;
    q.push({s,0});
    while (!q.empty()) {
        pair<int,int> it = q.front();
        q.pop();
        visited[it.first] = 1;
        dist[s][it.first] = it.second;
        for (auto j: v[it.first]) {
            if (visited[j] == 1) continue;
            q.push({j, it.second+1});
        }
    }
}

bool isDone(vector<pair<int, int>> s) {
    int c = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i].first > 0) {
            // printf("%d %d \n", s[i].second, s[i].first);
            c++;
        }
    }
    if (c > 1) return false;
    return true;
}

int solve(int n, int k) {
    vector<pair<int, int>> s(n+1, {0, 0});
    for (int i = 1; i <= n; i++) {
        int c = 0;
        for (int x = 1; x <= n; x++) {
            if (dist[i][x] > k) {
                vAtDist[i].push_back(x);
                c++;
            }
        }
        if (c > 0) s[i] = {c, i};
    }
    int rs = 0;
    while (!isDone(s)) {
        vector<pair<int, int>> ss(s.begin(), s.end());
        sort(ss.begin(), ss.end());
        int t = ss[ss.size()-1].first;
        int ind = ss.size()-1;
        pair<int, int> i = ss[ind];
        s[i.second].first = 0;
        for (int x: vAtDist[i.second]) {
            s[x].first--;
        }
        rs++;
        ss.clear();
    }
    return rs;
}
int main() {
    int n, k;
    cin >> n >> k;
    int a, b;
    for (int i = 1; i < n; i++) {
        cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    for (int i = 1; i <= n; i++) {
        bfs(n, i);
    }
    printf("%d\n", solve(n, k));
    return 0;
}