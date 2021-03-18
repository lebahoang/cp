#include <cstdio>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <utility>

using namespace std;
using ll = long long;
const string Y = "Yes";
const string N = "No";

bool run_left_to_right(int r, int c, int x, vector<vector<int>>& a, vector<vector<int>>& b) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (a[i][j] == b[i][j]) continue;
            if (j+x > c) continue;
            int t = b[i][j]-a[i][j];
            for (int k = 0; k < x; k++) {
                a[i][j+k] += t;
            }
        }
    }
    for (int j = 0; j < c; j++) {
        for (int i = 0; i < r; i++) {
            if (a[i][j] == b[i][j]) continue;
            if (i+x > r) continue;
            int t = b[i][j]-a[i][j];
            for (int k = 0; k < x; k++) {
                a[i+k][j] += t;
            }
        }
    }
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (a[i][j] != b[i][j]) {
                return false;
            }
        }
    }
    return true;
}
bool run_right_to_left(int r, int c, int x, vector<vector<int>>& a, vector<vector<int>>& b) {
    for (int i = 0; i < r; i++) {
        for (int j = c-1; j >= 0; j--) {
            if (a[i][j] == b[i][j]) continue;
            if (j-x+1 < 0) continue;
            int t = b[i][j]-a[i][j];
            for (int k = 0; k < x; k++) {
                a[i][j-k] += t;
            }
        }
    }
    for (int j = 0; j < c; j++) {
        for (int i = 0; i < r; i++) {
            if (a[i][j] == b[i][j]) continue;
            if (i+x > r) continue;
            int t = b[i][j]-a[i][j];
            for (int k = 0; k < x; k++) {
                a[i+k][j] += t;
            }
        }
    }
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (a[i][j] != b[i][j]) {
                return false;
            }
        }
    }
    return true;
}
int main() {
    int t;
    cin >> t;
    int r, c, x;
    for (int ca = 0; ca < t; ca++) {
        cin >> r >> c >> x;
        vector<vector<int>> a(r, vector<int>(c, 0));
        vector<vector<int>> b(r, vector<int>(c, 0));
        int totalA = 0;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                cin >> a[i][j];
                totalA += a[i][j];
            }
        }
        int totalB = 0;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                cin >> b[i][j];
                totalB += b[i][j];
            }
        }
        vector<vector<int>> a2(a.begin(), a.end());
        vector<vector<int>> b2(b.begin(), b.end());
        if ((totalB-totalA)%x != 0) {
            printf("%s\n", N.c_str());
            continue;
        }
        bool done = run_left_to_right(r, c, x, a, b);
        if (!done) {
            done = run_right_to_left(r,c,x,a2,b2);
        }
        if (done) {
            printf("%s\n", Y.c_str());
        } else {
            printf("%s\n", N.c_str());
        }
    }
    return 0;
}