#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <utility>

// g++ -std=c++17 -O2 -o s.out 2.cpp && ./s.out < x.txt
using namespace std;

int main() {
    int t;
    cin >> t;
    for (int cs = 1; cs <= t; cs++) {
        int x,y;
        string s;
        cin >> x >> y >> s;
        int cost = 0;
        int i = 0;
        while (i < s.length()) {
            if (s[i] == '?') {
                i++;
                continue;
            }
            int j = i+1;
            while (j < s.length() && (s[j] == '?' || s[i] == s[j])) {
                j++;
            }
            if (j < s.length()) {
                if (s[i] == 'C' && s[j] == 'J') {
                    cost += x;
                } else {
                    cost += y;
                }
            }
            i = j;
        }
        printf("Case #%d: %d\n", cs, cost);
    }
    return 0;
}