#include <random>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>

// g++ -std=c++17 -Wshadow -Wall -o s.out -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined 446.cpp && ./s.out
using namespace std;
using ll = long long;
int solve(vector<int>& a) {
    int rs = 0;
    int n = (int)a.size();
    // dp1[i][x] number of sub seq which end at i and the difference is x and the length of sub seq is 2
    vector<unordered_map<ll, int>> dp1(n, unordered_map<ll, int>());
    // dp2[i][x] number of sub seq which end at i and the difference is x and the length of sub seq is >= 3
    vector<unordered_map<ll, int>> dp2(n, unordered_map<ll, int>());

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            ll x = (ll)a[i]-a[j];
            if (dp1[i].find(x) != dp1[i].end()) {
                dp1[i][x] += 1;
            } else {
                dp1[i][x] = 1;
            }

            if (dp2[j].find(x) != dp2[j].end()) {
                if (dp2[i].find(x) != dp2[i].end()) {
                    dp2[i][x] += dp2[j][x];
                } else {
                    dp2[i][x] = dp2[j][x];
                }
            }
            if (dp1[j].find(x) != dp1[j].end()) {
                if (dp2[i].find(x) != dp2[i].end()) {
                    dp2[i][x] += dp1[j][x];
                } else {
                    dp2[i][x] = dp1[j][x];
                }
            }
        }
        for (auto k = dp2[i].begin(); k != dp2[i].end(); k++) {
            rs += k->second;
        }
        // for (auto k = dp1[i].begin(); k != dp1[i].end(); k++) {
        //     printf("dp1[%d][%d] = %d\n", i, k->first, k->second);
        // }
        // for (auto k = dp2[i].begin(); k != dp2[i].end(); k++) {
        //     printf("dp2[%d][%d] = %d\n", i, k->first, k->second);
        // }
    }
    return rs;
}
int main() {
    vector<int> arr = {2,6,4,6,8,10,12,15,64,100};
    // vector<int> arr = {0,2000000000,-294967296};
    printf("%d\n", solve(arr));
    return 0;
}