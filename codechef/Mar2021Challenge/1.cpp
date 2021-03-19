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
struct F {
    double a;
    double b;
};

F find_line(int x1, int y1, int x2, int y2) {
    F rs{0,0};
    rs.a = (1.0*(y2-y1))/(x2-x1);
    rs.b = (1.0*y2)-x2*rs.a;
    return rs;
}
bool is_intersect(F line, double x, double y) {
    if (line.a*x + line.b < y) {
        return true;
    }
    return false;
}
int main() {
    int t;
    cin >> t;
    int n;
    for (int ca = 0; ca < t; ca++) {
        cin >> n;
        vector<int> h(n+1, 0);
        vector<int> hj(n+1, 0);
        for (int i = 1; i <= n; i++) {
            cin >> h[i];
        }
        int rs = -1;
        for (int i = n; i > 0; i--) {
            if (i == n) {
                hj[i] = i;
            } else {
                int j = i+1;
                while (true) {
                    if (j == n) {
                        hj[i] = j;
                        break;
                    }
                    F line = find_line(i, h[i], hj[j], h[hj[j]]);
                    if (!is_intersect(line, j, h[j])) {
                        j = hj[j];
                    } else {
                        hj[i] = j;
                        break;
                    }
                }
            }
            rs = max(rs, hj[i]-i);
        }
        printf("%d\n", rs);
    }
    return 0;
}