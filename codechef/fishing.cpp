#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

// g++ -std=c++14 -Wshadow -Wall -o s.out -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined fishing.cpp && ./s.out < x.txt
/*
if k = 1
    for i in range(N):
        for j in range(i):
            if dist[j][i] + time[j] <= time[i]:
                dp[i] = max(dp[i], dp[j]+1)
*/
using namespace std;
void dfs(int i, int j, int t, int cur, int& rs, int r, int c, int k, int l,
    vector<vector<bool>>& visited,
    vector<vector<int>>& a) {

    
    if (t == l) {
        // printf("i %d j %d cur %d\n", i, j, cur);
        rs = max(rs, cur);
        return;
    }
    if (i+1 < r) {
        if (t+1 >= a[i+1][j] && t+1 <= min(a[i+1][j]+k-1, l) && !visited[i+1][j]) {
            visited[i+1][j] = true;
            dfs(i+1,j,t+1,cur+1,rs,r,c,k,l,visited,a);
            visited[i+1][j] = false;
            dfs(i+1,j,t+1,cur,rs,r,c,k,l,visited,a);
        } else {
            dfs(i+1,j,t+1,cur,rs,r,c,k,l,visited,a);
        }
    }
    if (i-1 >= 0) {
        if (t+1 >= a[i-1][j] && t+1 <= min(a[i-1][j]+k-1, l) && !visited[i-1][j]) {
            visited[i-1][j] = true;
            dfs(i-1,j,t+1,cur+1,rs,r,c,k,l,visited,a);
            visited[i-1][j] = false;
            dfs(i-1,j,t+1,cur,rs,r,c,k,l,visited,a);
        } else {
            dfs(i-1,j,t+1,cur,rs,r,c,k,l,visited,a);
        }
    }
    if (j+1 < c) {
        if (t+1 >= a[i][j+1] && t+1 <= min(a[i][j+1]+k-1, l) && !visited[i][j+1]) {
            visited[i][j+1] = true;
            dfs(i,j+1,t+1,cur+1,rs,r,c,k,l,visited,a);
            visited[i][j+1] = false;
            dfs(i,j+1,t+1,cur,rs,r,c,k,l,visited,a);
        } else {
            dfs(i,j+1,t+1,cur,rs,r,c,k,l,visited,a);
        }
    }
    if (j-1 >= 0) {
        if (t+1 >= a[i][j-1] && t+1 <= min(a[i][j-1]+k-1, l) && !visited[i][j-1]) {
            visited[i][j-1] = true;
            dfs(i,j-1,t+1,cur+1,rs,r,c,k,l,visited,a);
            visited[i][j-1] = false;
            dfs(i,j-1,t+1,cur,rs,r,c,k,l,visited,a);
        } else {
            dfs(i,j-1,t+1,cur,rs,r,c,k,l,visited,a);
        }
    }
    
    if (t+1 >= a[i][j] && t+1 <= min(a[i][j]+k-1, l) && !visited[i][j]) {
        visited[i][j] = true;
        dfs(i,j,t+1,cur+1,rs,r,c,k,l,visited,a);
        visited[i][j] = false;
        dfs(i,j,t+1,cur,rs,r,c,k,l,visited,a);
    } else {
        dfs(i,j,t+1,cur,rs,r,c,k,l,visited,a);
    }
}
int bf(int x, int y, int r, int c, int k, int l, vector<vector<int>>& a) {
    int rs = 0;
    int cur = 0;
    if (a[x][y] <= 1) cur++;
    vector<vector<bool>> visited(r, vector<bool>(c, false));
    dfs(x,y,1,cur,rs,r,c,k,l,visited,a);
    return rs;
}
int dist(int x1, int y1, int x2, int y2) {
    return abs(x2-x1) + abs(y2-y1);
}
void dfs2(int start, int x, int y, int n, int cur, int& rs, vector<vector<int>>& b, vector<int>& dp, vector<vector<bool>>& visited) {
    printf("start %d, N %d\n", start, n);
    rs = max(rs, cur);
    int xx = -1;
    int yy = -1;
    int t = -1;
    if (start == -1) {
        xx = x;
        yy = y;
        t = 1;
    } else {
        xx = b[start][0];
        yy = b[start][1];
        t = b[start][2];
    }
    for (int i = start+1; i < n; i++) {
        if (dist(xx,yy,b[i][0],b[i][1]) + t <= b[i][2] \
            && !visited[b[i][0]][b[i][1]] \
            && cur+1 > dp[i]) {
            
            visited[b[i][0]][b[i][1]] = true;
            dp[i] = cur+1;
            dfs2(i, x, y, n, dp[i], rs, b, dp, visited);
            visited[b[i][0]][b[i][1]] = false;
        }
    }
}
int solve(int x, int y, int r, int c, int k, int l, vector<vector<int>>& a) {
    vector<vector<int>> b = {};
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            for (int kk = 0; kk < k; kk++) {
                if (a[i][j]+kk > l) break;
                if (dist(i,j,x,y)+1 > a[i][j]+kk) continue;
                b.push_back({i,j,a[i][j]+kk});
            }
        }
    }
    sort(b.begin(), b.end(), [](vector<int>& i, vector<int>& j){
        return i[2] < j[2];
    });
    int cur = 0;
    int rs = -1;
    int n = (int)b.size();
    vector<vector<bool>> visited(r, vector<bool>(c, false));
    vector<int> dp(n, 0);
    dfs2(-1, x, y, n, cur, rs, b, dp, visited);
    return rs;
}
int main() {
    int r, c, k, l;
    cin >> r >> c >> k >> l;
    int x, y;
    cin >> x >> y;
    vector<vector<int>> a(r, vector<int>(c, -1));
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> a[i][j];
        }
    }
    // printf("BF: %d\n", bf(x,y,r,c,k,l,a));
    printf("Solve: %d\n", solve(x,y,r,c,k,l,a));
    return 0;
}