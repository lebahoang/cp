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
        // vector<vector<int>> a(r, vector<int>(c, 0));
        vector<vector<int>> barr(r, vector<int>(c, 0));
        vector<int> a(r, 0);
        vector<int> b(r, 0);
        int t = 0;
        for (int i = 0; i < r; i++) {
            int total = 0;
            for (int j = 0; j < c; j++) {
                cin >> t;
                total += t;
            }
            a[i] = total;
        }
        for (int i = 0; i < r; i++) {
            int total = 0;
            for (int j = 0; j < c; j++) {
                cin >> t;
                barr[i][j] = t;
                total += t;
            }
            b[i] = total;
        }
        bool done = false;
        int rem = -1;
        for (int i = 0; i < r; i++) {
            int trem = abs(b[i]-a[i])%x;
            if (rem > 0 && trem != rem) {
                printf("%s\n", N.c_str());
                done = true;
                break;
            } else {
                rem = trem;
            }
        }
        if (!done) {
            if (c%x == 0) {
                printf("%s\n", Y.c_str());
            } else {
                printf("%s\n", N.c_str());
            }
        }
    }
    return 0;
}