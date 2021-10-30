#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <map>
#include <stack>
#include <queue>
#include <vector>
#include <utility>

// g++ -std=c++14 -stdlib=libc++ -O2 -o s.out 3.cpp && ./s.out < x.txt
using namespace std;
using ll = long long;

vector<pair<int, int>> has[40][10][10];
void dfs2(vector<vector<int>>& a,
          vector<vector<int>>& b,
          int n, int i, bool& done) {

    if (i == n) {
        done = true;
        return;
    }
    for (int x = 0; x <= 9; x++) {
        bool f = true;
        b[i+1][0] = x;
        int y = 0;
        for (int j = 0; j < n; j++) {
            int t = a[i][j] - b[i][j] - b[i][j+1] - b[i+1][j];
            if (t < 0 || t > 9) {
                f = false;
                break;
            }
            b[i+1][j+1] = t;
            y++;
        }
        if (f) {
            dfs2(a, b, n, i+1, done);
            if (done) return;
        }
        for (int j = 0; j <= y; j++) {
            b[i+1][j] = 0;
        }
    }
}
void dfs(vector<vector<int>>& a, int n, int j, int k, int h, int& countj, vector<vector<int>>& b, bool& done) {
    if (countj == n) {
        // for (int i = 0; i < 2; i++) {
        //     for (int j = 0; j < n+1; j++) {
        //         printf("%d ", b[i][j]);
        //     }
        //     printf("\n");
        // }
        // printf("----------\n");
        dfs2(a, b, n, 1, done);
        return;
    };
    int num = a[0][j];
    for (auto x: has[num][k][h]) {
        int kk = x.first;
        int hh = x.second;
        b[0][j+1] = kk;
        b[1][j+1] = hh;
        countj++;
        dfs(a, n, j+1, kk, hh, countj, b, done);
        if (done) return;
        countj--;
    }
}
int main() {
    int n;
    cin >> n;
    vector<vector<int>> a(n+1, vector<int>(n+1, 0));
    vector<vector<int>> b(n+2, vector<int>(n+2, 0));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    for (int x = 0; x <= 36; x++) {
        for (int i = 0; i <= 9; i++) {
            for (int j = 0; j <= 9; j++) {
                for (int k = 0; k <= 9; k++) {
                    for (int h = 0; h <= 9; h++) {
                        if (i+j+k+h == x) {
                            has[x][i][j].push_back({k,h});
                        }
                    }
                }
            }
        }
    }
    for (int k = 0; k <= 9; k++) {
        for (int h = 0; h <= 9; h++) {
            b[0][0] = k;
            b[1][0] = h;
            int countj = 0;
            bool done = false;
            dfs(a, n, 0, k, h, countj, b, done);
            if (done) {
                for (int x = 0; x <= n; x++) {
                    for (int y = 0; y <= n; y++) {
                        printf("%d", b[x][y]);
                    }
                    printf("\n");
                }
                // printf("-------\n");
                return 0;
            }
        }
    }
    return 0;
}