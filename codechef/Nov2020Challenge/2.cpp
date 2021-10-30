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

// g++ -std=c++14 -stdlib=libc++ -O2 -o s.out 2.cpp && ./s.out < x.txt

using namespace std;
struct I {
    int j;
    int sheet;
};

int cal(int i, int j, int k, int sheet) {
    return k+1-abs(j-i)-sheet;
}
int bf() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    int rs = 0;
    vector<bool> used(n+1, false);
    int sheet = 0;
    for (int i = 0; i < s.length(); i++) {
        char c = s[i];
        if (used[i]) continue;
        if (c == 'M' || c == 'I') {
            sheet = 0;
            for (int j = i+1; j < s.length(); j++) {
                char v = s[j];
                if (used[j]) continue;
                if ((v == 'M' || v == 'I') && v != c) {
                    int eff = cal(i, j, k, sheet);
                    if (eff >= 0) {
                        rs++;
                        used[j] = true;
                        break;
                    }
                } else if (v == ':') {
                    sheet++;
                } else if (v == 'X') {
                    break;
                }
            }
        }
    }
    return rs;
}
int bf1(int n, int k, string s) {
    int rs = 0;
    vector<bool> used(n+1, false);
    int sheet = 0;
    for (int i = 0; i < s.length(); i++) {
        char c = s[i];
        if (used[i]) continue;
        if (c == 'M' || c == 'I') {
            sheet = 0;
            for (int j = i+1; j < s.length(); j++) {
                char v = s[j];
                if (used[j]) continue;
                if ((v == 'M' || v == 'I') && v != c) {
                    int eff = cal(i, j, k, sheet);
                    if (eff >= 0) {
                        rs++;
                        used[j] = true;
                        break;
                    }
                } else if (v == ':') {
                    sheet++;
                } else if (v == 'X') {
                    break;
                }
            }
        }
    }
    return rs;
}
void clearQueue(queue<int>& x) {
    while (!x.empty()) {
        x.pop();
    }
}
int solve() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    // printf("%s\n", s.c_str());
    vector<int> prefixSheet(n+1, 0);
    int i = 0;
    for (char x: s) {
        if (x == 'X') {
            prefixSheet[i] = 0;
        }else  {
            if (x != ':') {
                if (i > 0) prefixSheet[i] = prefixSheet[i-1];
            } else {
                if (i == 0) prefixSheet[i] = 1;
                else prefixSheet[i] = prefixSheet[i-1]+1;
            } 
        }
        i++;
    }
    // for (auto x: prefixSheet) {
    //     printf("%d ", x);
    // }
    // printf("\n");
    queue<int> ms;
    queue<int> is;
    int rs = 0;
    int sheet = 0;
    for (int i = 0; i < s.length(); i++) {
        char x = s[i];
        if (x == '_') continue;
        else if (x == ':') sheet++;
        else if (x == 'X') {
            sheet = 0;
            clearQueue(ms);
            clearQueue(is);
            printf("aaa %d %d\n", (int)ms.size(), (int)is.size());
        } else if (x == 'M') {
            bool f = false;
            while(!is.empty()) {
                int j = is.front();
                is.pop();
                int eff = cal(i, j, k, prefixSheet[i]-prefixSheet[j]);
                printf("i %d j %d eff %d\n", i, j, eff);
                if (eff >= 0) {
                    rs++;
                    f = true;
                    break;
                }
            }
            if (!f) {
                ms.push(i);
            }
        } else {
            bool f = false;
            while(!ms.empty()) {
                int j = ms.front();
                ms.pop();
                int eff = cal(i, j, k, prefixSheet[i]-prefixSheet[j]);
                printf("i %d j %d eff %d\n", i, j, eff);
                if (eff >= 0) {
                    rs++;
                    f = true;
                    break;
                }
            }
            if (!f) {
                is.push(i);
            }
        }
    }
    return rs;
}

int solve1(int n, int k, string s) {
    vector<int> prefixSheet(n+1, 0);
    int i = 0;
    for (char x: s) {
        if (x == 'X') {
            prefixSheet[i] = 0;
        }else  {
            if (x != ':') {
                if (i > 0) prefixSheet[i] = prefixSheet[i-1];
            } else {
                if (i == 0) prefixSheet[i] = 1;
                else prefixSheet[i] = prefixSheet[i-1]+1;
            } 
        }
        i++;
    }
    // for (auto x: prefixSheet) {
    //     printf("%d ", x);
    // }
    // printf("\n");
    queue<int> ms;
    queue<int> is;
    int rs = 0;
    int sheet = 0;
    for (int i = 0; i < s.length(); i++) {
        char x = s[i];
        if (x == '_') continue;
        else if (x == ':') sheet++;
        else if (x == 'X') {
            sheet = 0;
            clearQueue(ms);
            clearQueue(is);
        } else if (x == 'M') {
            bool f = false;
            while(!is.empty()) {
                int j = is.front();
                is.pop();
                int eff = cal(i, j, k, prefixSheet[i]-prefixSheet[j]);
                // printf("i %d j %d eff %d\n", i, j, eff);
                if (eff >= 0) {
                    rs++;
                    f = true;
                    break;
                }
            }
            if (!f) {
                ms.push(i);
            }
        } else {
            bool f = false;
            while(!ms.empty()) {
                int j = ms.front();
                ms.pop();
                int eff = cal(i, j, k, prefixSheet[i]-prefixSheet[j]);
                // printf("i %d j %d eff %d\n", i, j, eff);
                if (eff >= 0) {
                    rs++;
                    f = true;
                    break;
                }
            }
            if (!f) {
                is.push(i);
            }
        }
    }
    return rs;
}
// int main() {
//     int t;
//     cin >> t;
//     for (int cs = 0; cs < t; cs++) {
//         printf("%d\n", solve());
//         // printf("%d\n", bf());
//     }
//     return 0;
// }
int main() {
    int t;
    cin >> t;
    for (int cs = 0; cs < t; cs++) {
        int n, k;
        string s;
        cin >> n >> k;
        cin >> s;
        int x = bf1(n,k,s);
        int y = solve1(n,k,s);
        if (x != y) {
            printf("%d %d %s\n", n, k, s.c_str());
        } else {
            // printf("%d %d\n", x, y);
        }
    }
    return 0;
}