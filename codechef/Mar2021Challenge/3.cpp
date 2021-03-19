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
        bool done = true;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (a[i][j] != b[i][j]) {
                    done = false;
                    break;
                }
            }
        }
        if (done) {
            printf("%s\n", Y.c_str());
        } else {
            printf("%s\n", N.c_str());
        }
    }
    return 0;
}