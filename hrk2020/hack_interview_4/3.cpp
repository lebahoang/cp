#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <queue>
#include <cstring>
#include <utility>

// https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/

using namespace std;
using ll = long long;
const int NMAX = 303;
int a[NMAX][NMAX];
vector<pair<int, int>> w[NMAX*NMAX];
class Comperator {
public:
    int operator() (const pair<int, int>& a, const pair<int, int>& b) {
        // we want min heap
        return a.first >= b.first;
    }
};

int solve(int n, int m) {
    vector<int> dist(NMAX*NMAX, -(1e9+2));
    priority_queue<pair<int, int>, vector<pair<int,int>>, Comperator> q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x = i*m + j;
            int y = 0;
            int ww = 0;
            if (i-1 >= 0) {
                y = (i-1)*m + j;
                ww = abs(a[i][j]-a[i-1][j]);
                w[x].push_back({ww, y});
                w[y].push_back({ww, x});
            }
            if (i+1 < n) {
                y = (i+1)*m + j;
                ww  = abs(a[i][j] - a[i+1][j]);
                w[x].push_back({ww, y});
                w[y].push_back({ww, x});
            }
            if (j-1 >= 0) {
                y = i*m + j-1;
                ww = abs(a[i][j] - a[i][j-1]);
                w[x].push_back({ww, y});
                w[y].push_back({ww, x});
            }
            if (j+1 < m) {
                y = i*m + j+1;
                ww = abs(a[i][j] - a[i][j+1]);
                w[x].push_back({ww, y});
                w[y].push_back({ww, x});
            }
        }
    }

    dist[0] = 0;
    q.push({0, 0});
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();
        for (auto p: w[u]) {
            int d = p.first;
            int v = p.second;
            if (dist[v] < 0 || dist[v] > max(dist[u], d)) {
                dist[v] = max(dist[u], d);
                q.push({dist[v], v});
            }
        }
    }
    
    int last = (n-1)*m + m-1;
    return dist[last];
}
int main() {
    int n,m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    printf("%d\n", solve(n, m));
    return 0;
}