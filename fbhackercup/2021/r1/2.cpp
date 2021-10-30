#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;
const int mod = 1e9+7;
// g++ -std=c++14 -Wshadow -Wall -o s.out -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined 1.cpp && ./s.out
int start_at(int lor, int n, string s) {
    int c = 0;
    char x = '\0';
    char y = '\0';
    if (lor == 0) {
        // left
        x = 'F';
        y = 'X';
    } else {
        x = 'F';
        y = 'O';
    }
    for (int i = 0; i < n; i++) {
        if (s[i] != x && s[i] != y) {
            c++;
            x = 'F';
            if (y == 'X') y = 'O';
            else y = 'X';
        }
    }
    return c;
}
int bf(int n, string s) {
    int rs = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            string ss = s.substr(i, j-i+1);
            int t = min(start_at(0, j-i+1, ss), start_at(1, j-i+1, ss));
            rs = (rs%mod + t%mod)%mod;
        }
    }
    return rs;
}

int solve(int n, string s) {
    vector<int> a(n, 0);
    vector<int> k(n, 0);
    vector<int> dp(n, 0);

    return rs;
}

int main() {
    int t;
    cin >> t;
    for (int c = 0; c < t; c++) {
        int n;
        string s;
        cin >> n;
        cin >> s;
        printf("Case #%d: %d\n", c+1, solve(n, s));
        // printf("Case #%d: %d\n", c+1, bf(n, s));
    }
    return 0;
}