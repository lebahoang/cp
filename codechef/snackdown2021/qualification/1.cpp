#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
using namespace std;
// g++ -std=c++14 -Wshadow -Wall -o s.out -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined 2.cpp && ./s.out

int main() {
    int t;
    cin >> t;
    for (int cs = 0; cs < t; cs++) {
        vector<int> a(3, 0);
        int k;
        for (int i = 0; i < 5; i++) {
            cin >> k;
            a[k]++;
        }
        if (a[1] > a[2]) printf("INDIA\n");
        else if (a[2] > a[1]) printf("ENGLAND\n");
        else printf("DRAW\n");
    }
    return 0;
}