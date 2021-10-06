#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;
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
int solve(int n, string s) {
    return min(start_at(0, n, s), start_at(1, n, s));
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
    }
    return 0;
}