#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>
using namespace std;
// g++ -std=c++14 -Wshadow -Wall -o s.out -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined 3.cpp && ./s.out
pair<string, vector<vector<int>>> solve(int n, int m, int a, int b) {
    // int limit = m + 2*(n-1);
    // if (a < limit || b < limit) {
    //     return {"Impossible", {{}}};
    // }
    vector<vector<int>> rs(n, vector<int>(m, 0));
    for (int j = 0; j < m; j++) rs[0][j] = 1;
    for (int i = 1; i < n-1; i++) {
        rs[i][0] = 1;
        rs[i][m-1] = 1;
    }
    rs[n-1][0] = b-m-(n-2);
    rs[n-1][m-1] = a-m-(n-2);
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m-1; j++) {
            rs[i][j] = 1000;
        }
    }
    if (rs[n-1][0] <= 0 || rs[n-1][m-1] <= 0) {
        return {"Impossible", {{}}};
    }
    return {"Possible", rs};
}

int main() {
    int t;
    cin >> t;
    for (int c = 0; c < t; c++) {
        int n, m, a, b;
        cin >> n >> m >> a >> b;
        pair<string, vector<vector<int>>> rs = solve(n, m, a, b);
        printf("Case #%d: %s\n", c+1, rs.first.c_str());
        if (rs.first == "Possible") {
            for (int i = 0; i < n; i++) {
                string r = to_string(rs.second[i][0]);
                for (int j = 1; j < m; j++) {
                    r += " " + to_string(rs.second[i][j]);
                }
                printf("%s\n", r.c_str()); 
            }
            // for (int i = 0; i < n; i++) {
            //     for (int j = 0; j < m; j++) {
            //         printf("%d ", rs.second[i][j]);
            //     }
            //     printf("\n");
            // }
        }
        
    }
    return 0;
}