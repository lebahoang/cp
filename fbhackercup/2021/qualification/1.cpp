#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;
bool is_vowel(vector<char>& a, char x) {
    for (char &y: a) {
        if (y == x) return true;
    }
    return false;
}
int find_max(unordered_map<char, int>& m) {
    int rs = -1;
    for (auto it = m.begin(); it != m.end(); it++) {
        if (it->second > rs) {
            rs = it->second;
        }
    }
    return rs;
}
int solve(string s) {
    int s1 = 0;
    int s2 = 0;
    vector<char> a = {'A', 'E', 'I', 'O', 'U'};
    unordered_map<char, int> m = {{'A', 0}, {'E', 0}, {'I', 0}, {'O', 0}, {'U', 0}};
    unordered_map<char, int> n;
    for (char &x: s) {
        if (is_vowel(a,x)) {
            m[x]++;
            s1++;
        } else {
            if (n.find(x) == n.end()) {
                n[x] = 1;
            } else {
                n[x]++;
            }
            s2++;
        }
    }

    int total = 1e9;
    
    for (auto it = m.begin(); it != m.end(); it++) {
        int target = it->second;
        int t = s2 + 2*(s1-target);
        // printf("target %d, t %d\n", target, t);
        total = min(total, t);
    }
    
    
    if (s2 > 0) {
        for (auto it = n.begin(); it != n.end(); it++) {
            int target = it->second;
            int t = s1 + 2*(s2-target);
            // printf("target %d, t %d\n", target, t);
            total = min(total, t);
        }
    } else {
        total = min(total, s1);
    }
    
    return total;
}

int main() {
    int t;
    cin >> t;
    for (int c = 0; c < t; c++) {
        string s;
        cin >> s;
        printf("Case #%d: %d\n", c+1, solve(s));
    }
    return 0;
}