#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <set>
using namespace std;
const int mod = 1e9+7;
// g++ -std=c++14 -Wshadow -Wall -o s.out -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined 1.cpp && ./s.out


int main() {
    int t;
    cin >> t;
    for (int cs = 0; cs < t; cs++) {
        printf("Case #%d:\n", cs+1);
        int r,c;
        cin >> r >> c;
        string last = "";
        for (int i = 0; i < r; i++) {
            string x = "";
            string y = "";
            for (int j = 0; j < c; j++) {
                if (i == 0 && j == 0) {
                    x.append("..");
                    y.append("..");
                } else {
                    x.append("+-");
                    y.append("|.");
                }
                if (i == r-1) {
                    last.append("+-");
                }
            }
            x.append("+");
            y.append("|");
            printf("%s\n", x.c_str());
            printf("%s\n", y.c_str());
        }
        last.append("+");
        printf("%s\n", last.c_str());
    }
    return 0;
}