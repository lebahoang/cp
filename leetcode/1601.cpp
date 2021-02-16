#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <vector>
using namespace std;

int solve(int n, vector<vector<int>>& req) {
    int ans = -1;
    int len = (int)req.size();
    vector<int> bs(n+1, 0);
    for (int i = 0; i < (1 << len); i++) {
        bool valid = true;
        int c = 0;
        for (int j = 0; j < len; j++) {
            if ((i & (1 << j)) != 0) {
                bs[req[j][0]]--;
                bs[req[j][1]]++;
                c++;
            }
        }   
        for (int& x: bs) {
            if (x != 0) {
                valid = false;
            }
            x = 0;
        }

        if (valid) ans = max(ans, c);
    }
    return ans;
}
int main() {
    // int n = 5;
    // vector<vector<int>> req = {{0,1},{1,0},{0,1},{1,2},{2,0},{3,4}};
    int n = 3;
    vector<vector<int>> req = {{0,0}, {1,2}, {2,1}};
    printf("%d\n", solve(n, req));
    return 0;
}