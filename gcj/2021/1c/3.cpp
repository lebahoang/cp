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
const int INF = 1e9+2;
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
            y[i] = 1;
        } else {
            c++;
        }
    }
    x.push_back(c);
}
bool check(int i, int j, string& a, string& b) {
    int az = (int)a.length();
    int bz = (int)b.length();
    if (i )
}
int solve(string& a, string& b, vector<int>& x1, vector<int>& y1, vector<int>& x2) {
    int rs = INF;
    int az = (int)a.length();
    int bz = (int)b.length();
    if ((int)x2.size() == 1) {
        if ((int)x1.size() == 1) {
            if (a[0] == b[0]) {
                return 0;
            }
            return 1;
        }
        if (b[0] == '0') {
            return (int)x1.size();
        }
    }
    
    for (int j = 0; j < bz; j++) {
        int i = az-(bz-j+1)+1;

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
        vector<int> y1((int)a.length(), -1);
        get(a, x1, y1);
        vector2string(x1);
        vector2string(y1);
        vector<int> x2 = {};
        vector<int> y2((int)b.length(), -1);
        get(b, x2, y2);
        vector2string(x2);
        vector2string(y2);
    }
    return 0;
}
