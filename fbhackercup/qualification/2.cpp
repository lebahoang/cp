#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>

using namespace std;

int main() {
    int t;
    cin >> t;
    for (int c = 0; c < t; c++) {
        int n;
        string s;
        cin >> n;
        cin >> s;
        int a = 0;
        int b = 0;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == 'A') a++;
            else b++;
        }
        // printf("%d %d\n", a, b);
        if (abs(a-b) == 1) printf("Case #%d: Y\n", c+1);
        else printf("Case #%d: N\n", c+1);
    }
    return 0;
}