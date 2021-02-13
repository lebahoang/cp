#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>

using namespace std;
string check(int i, int j, string in, string out) {
    if (i < j) {
        while (i < j) {
            if (out[i] != 'Y' || in[i+1] != 'Y') {
                return "N";
            }
            i++;
        }
        return "Y";
    } else {
        while (i > j) {
            if (out[i] != 'Y' || in[i-1] != 'Y') {
                return "N";
            }
            i--;
        }
        return "Y";
    }
}
string solve(int n, string in, string out) {
    string rs = "";
    for (int i = 0; i < n; i++) {
        string t = "";
        for (int j = 0; j < n; j++) {
            if (i == j) {
                t += "Y";
            } else {
                t += check(i, j, in, out);
            }
        }
        rs += t + "\n";
    }
    return rs;
}
int main() {
    int t;
    cin >> t;
    for (int c = 0; c < t; c++) {
        int n;
        string in, out;
        cin >> n;
        cin >> in;
        cin >> out;
        string rs = solve(n, in, out);
        printf("Case #%d:\n", c+1);
        printf("%s", rs.c_str());
    }
    return 0;
}