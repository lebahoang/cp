#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#include <string>
#include <set>
#include <vector>
#include <utility>

// g++ -std=c++17 -Wshadow -Wall -o s.out -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined 3.cpp && ./s.out < x.txt
using namespace std;
void vector2string(vector<int> a) {
    string x = "";
    for(int i: a) {
        x.append(" " + to_string(i)); 
    }
    printf("%s\n", x.c_str());
}
void get(string& arr, vector<int>& x, vector<int>& y) {
    char cur = '_';
    int c = 0;
    for (int i = 0; i < (int)arr.length(); i++) {
        if (cur == '_' || cur != arr[i]) {
            if (cur != '_')
                x.push_back(c);
            c = 1;
            cur = arr[i];
            y.push_back(i);
        } else {
            c++;
        }
    }
    x.push_back(c);
}
bool check(int j, string& a, string& b) {
    int bz = (int)b.size();
    if (bz-j > (int)a.size()) return false;
    if (j > 0 && a[j-1] == a[j]) return false;
    int i = (int)a.size()-1;
    while (j < bz) {
        
    }
}
int solve(string& a, string& b, vector<int>& x1, vector<int>& y1, vector<int>& x2, vector<int>& y2) {
    for (int j = (int)b.size()-1; j >= 0; j--) {

    }
}
int main() {
    int t;
    cin >> t;
    for (int cs = 1; cs <= t; cs++) {
        string a;
        string b;
        cin >> a >> b;
        printf("%s %s\n", a.c_str(), b.c_str());
        vector<int> x1 = {};
        vector<int> y1 = {};
        get(a, x1, y1);
        vector2string(x1);
        vector2string(y1);
        vector<int> x2 = {};
        vector<int> y2 = {};
        get(b, x2, y2);
        vector2string(x2);
        vector2string(y2);
    }
    return 0;
}
