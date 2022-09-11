#include <iostream>
#include <stdio.h>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 15;
int barr[NMAX][NMAX];
int warr[NMAX][NMAX];

int cn, cm;
int carr[NMAX][NMAX];

struct Item {
    int v;
    vector<vector<int>> visited;
};

struct P {
    int i;
    int j;
};

void go(int start, int an, int am, int a[NMAX][NMAX],
        int bn, int bm, int b[NMAX][NMAX], int visited[NMAX],
        int cur, int steps, int totalSteps, int& rs) {
    if (steps == totalSteps) {
        rs = max(rs, cur);
        return;
    }
    
    for (int j = 0; j < am; j++) {
        if (visited[j] == 0) {
            visited[j] = 1;
            int t = a[start][j];
            if (j < bn && start < bm) {
                t = max(t, b[j][start]);
            }
            go(start+1,an,am,a,bn,bm,b,visited,cur+t,steps+1,totalSteps,rs);
            visited[j] = 0;
        }
    }

    return;
}
int solve(int b, int w) {
    int totalSteps = min(b,w);
    int rs = 0;
    int visited[NMAX];
    for (int i = 0; i < NMAX; i++) {
        visited[i] = 0;
    }
    if (b < w) {
        go(0,b,w,barr,w,b,warr,visited,0,0,totalSteps,rs);
    } else {
        go(0,w,b,warr,b,w,barr,visited,0,0,totalSteps,rs);
    }    
    return rs;
}

void go1(int i, int n, int m, int arr[NMAX][NMAX], int visited[NMAX], int cur, int& rs) {
    if (i == n) {
        rs = max(rs, cur);
        return;
    }
    for (int j = 0; j < m; j++) {
        if (visited[j] == 0) {
            visited[j] = 1;
            go1(i+1, n, m, arr, visited, cur+arr[i][j], rs);
            visited[j] = 0;
        }
    }
    return;
}

void go2(int i, int n, int m, int arr[NMAX][NMAX], int visited[NMAX], int path[NMAX][NMAX], int cur, int& rs, vector<P>& rsP) {
    if (i == n) {
        if (cur > rs) {
            rs = cur;
            rsP = {};
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (path[i][j] == 1) {
                        rsP.push_back({i,j});
                    }
                }
            }
        }
        return;
    }
    for (int j = 0; j < m; j++) {
        if (visited[j] == 0) {
            visited[j] = 1;
            path[i][j] = 1;
            go2(i+1, n, m, arr, visited, path, cur+arr[i][j], rs, rsP);
            visited[j] = 0;
            path[i][j] = 0;
        }
    }
    return;
}

bool isNotIn(int j, vector<int> vt) {
    for (int i = 0; i < vt.size(); i++) {
        if (j == vt[i]) return false;
    }
    return true;
}

int solve1(int b, int w) {
    if (b > w) {
        cn = w;
        cm = b;
        for (int i = 0; i < w; i++) {
            for (int j = 0; j < b; j++) {
                carr[i][j] = max(barr[j][i], warr[i][j]);
            }
        }
    } else {
        cn = b;
        cm = w;
        for (int i = 0; i < b; i++) {
            for (int j = 0; j < w; j++) {
                carr[i][j] = max(warr[j][i], barr[i][j]);
            }
        }
    }
    // int rs = 0;
    // int visited[NMAX];
    // for (int i = 0; i < NMAX; i++) {
    //     visited[i] = 0;
    // }
    // go1(0, cn, cm, carr, visited, 0, rs);
    // return rs;
    int rs = 0;
    vector<P> rsP;
    int visited[NMAX];
    int path[NMAX][NMAX];
    for (int i = 0; i < NMAX; i++) {
        visited[i] = 0;
    }
    for (int i = 0; i < NMAX; i++) {
        for (int j = 0; j < NMAX; j++) {
            path[i][j] = 0;
        }
    }
    go2(0, cn, cm, carr, visited, path, 0, rs, rsP);
    printf("Result %d\n", rs);
    for (int i = 0; i < rsP.size(); i++) {
        printf("%d %d\n", rsP[i].i, rsP[i].j);
    }
    printf("---------------\n");

    Item dp[NMAX][NMAX];
    for (int j = 0; j < cm; j++) {
        dp[0][j] = {carr[0][j], {{j}}};
    }
    for (int i = 1; i < cn; i++) {
        for (int j = 0; j < cm; j++) {
            int maxV = 0;
            vector<vector<int>> maxVt;
            for (int k = 0; k < cm; k++) {
                for (int h = 0; h < dp[i-1][k].visited.size(); h++) {
                    if (isNotIn(j, dp[i-1][k].visited[h])) {
                        if (maxV < dp[i-1][k].v) {
                            maxV = dp[i-1][k].v;
                            vector<int> tt(dp[i-1][k].visited[h].begin(),dp[i-1][k].visited[h].end());
                            tt.push_back(j);
                            maxVt = {tt};
                        } else if (maxV == dp[i-1][k].v) {
                            vector<int> tt(dp[i-1][k].visited[h].begin(),dp[i-1][k].visited[h].end());
                            tt.push_back(j);
                            maxVt.push_back(tt);
                        }
                    }
                }
            }
            dp[i][j] = {maxV+carr[i][j], maxVt};
        }
    }
    for (int i = 0; i < cn; i++) {
        for (int j = 0; j < cm; j++) {
            printf("%d ", carr[i][j]);
        }
        printf("\n");
    }
    printf("---------------\n");
    for (int i = 0; i < cn; i++) {
        for (int j = 0; j < cm; j++) {
            printf("%d ", dp[i][j].v);
        }
        printf("\n");
    }
    int maxV = 0;
    for (int j = 0; j < cm; j++) {
        maxV = max(maxV, dp[cn-1][j].v);
    }
    return maxV;
}
int main() {
    int tc;
    cin >> tc;
    int b,w;
    for (int i = 1; i <= tc; i++) {
        cin >> b >> w;
        for (int j = 0; j < b; j++) {
            for (int k = 0; k < w; k++) {
                cin >> barr[j][k];
            }
        }
        for (int j = 0; j < w; j++) {
            for (int k = 0; k < b; k++) {
                cin >> warr[j][k];
            }
        }
        // printf("#%d %d\n", i, solve(b,w));
        printf("#%d %d\n", i, solve1(b,w));
    }
    return 0;
}