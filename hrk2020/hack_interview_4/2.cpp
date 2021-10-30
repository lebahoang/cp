#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <utility>

// g++ -std=c++14 -stdlib=libc++ -O2 -o s.out 1.cpp && ./s.out

using namespace std;
string go(int turn, int n, vector<int> b, vector<int> g) {
    int x = 0;
    int y = 0;
    while (x < n && y < n) {
        if (turn == 0) {
            turn = 1;
            if (b[x] <= g[y]) {
                x++;
            } else {
                return "NO";
            }
        } else {
            turn = 0;
            if (g[y] <= b[x]) {
                y++;
            } else {
                return "NO";
            }
        }
    }
    if ((x == n && y == n-1) || (y == n && x == n-1)) return "YES";
    return "NO";
}
void solve(int n, vector<int> b, vector<int> g) {
    sort(b.begin(), b.end());
    sort(g.begin(), g.end());
    
    int turn = 0;
    string rs = "";
    if (b[0] < g[0]) {
        rs = go(turn, n, b, g);
    } else if (b[0] > g[0]) {
        turn = 1;
        rs = go(turn, n, b, g);
    } else {
        string rs1 = go(0, n, b, g);
        string rs2 = go(1, n, b, g);
        if (rs1 == "NO" && rs2 == "NO") rs = "NO";
        else rs = "YES";
    }
    printf("%s\n", rs.c_str());
}
int main() {
    int t;
    int n;
    cin >> t;
    for (int i = 0; i < t; i++) {
        cin >> n;
        vector<int> b;
        vector<int> g;
        int a;
        for (int j = 0; j < n; j++) {
            cin >> a;
            b.push_back(a);
        }
        for (int j = 0; j < n; j++) {
            cin >> a;
            g.push_back(a);
        }
        solve(n, b, g);
    }

    return 0;
}