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

// g++ -std=c++14 -stdlib=libc++ -O2 -o s.out 4.cpp && ./s.out < x.txt
using namespace std;
// const int NNodes = 1e3 + 9;

// vector<int> sstrinng[NNodes];
// int p[NNodes];
// int rankAtNode[NNodes];

// void initDisjoinSet(int n) {
//     for (int i = 0; i < n; i++) {
//         sstrinng[i] = {};
//         p[i] = i;
//         rankAtNode[i] = 0;
//     }
// }

// int findSubset(int x) {
//     // apply path compression
//     // which is the idea: moving the sub tree rooted at x to be a child of root node
//     vector<int> z1 = sstrinng[x];
//     vector<int> z2 = sstrinng[p[x]]; 
//     if (is_reversable(z1, z2)) {
//         return x;
//     }
//     p[x] = findSubset(p[x]);
//     return p[x];
// }

// void union2Subsets(int x, int y) {
//     // apply union by rank
//     // which is the idea: attach the smaller-depth tree into the bigger depth tree
//     // more specifically the root node of smaller tree will become a child of the root node
//     // of bigger tree
//     int xroot = findSubset(x);
//     int yroot = findSubset(y);
//     if (xroot == yroot) {
//         return;
//     }
//     if (rankAtNode[xroot] >= rankAtNode[yroot]) {
//         p[yroot] = xroot;
//         if (rankAtNode[xroot] == rankAtNode[yroot] ) {
//             rankAtNode[xroot]++;
//         }
//     } else if (rankAtNode[xroot] < rankAtNode[yroot]) {
//         p[xroot] = yroot;
//     }
// }

bool is_reversable(vector<int> x, vector<int> y) {
    int x_size = (int)x.size();
    int y_size = (int)y.size();
    // if (y[y_size-1] == 0) y_size--;
    if (x_size != y_size) return false;
    vector<vector<int>> m(1005);
    for (int i = 0; i < (int)x.size(); i++) {
        int v = x[i];
        m[v].push_back(i);
    }
    for (int i = 0; i < (int)x.size(); i++) {
        int v = y[i];
        if ((int)m[v].size() == 0) return false;
        // if (abs(m[v]-i)%2 != 0) return false;
        bool f = false;
        for (int k: m[v]) {
            if (abs(k-i)%2 == 0) {
                f = true;
                break;
            }
        }
        if (!f) return false;
    }
    return true;
}

void solve(string s) {
    int rs = 0;
    int n = s.length();
    for (int l = 1; l <= n; l++) {
        // init dsu
        int ss = 0;
        vector<vector<int>> sets = {};
        // calculate 0s
        int c = 0;
        vector<int> a = {};
        
        for (int i = 0; i < l; i++) {
            if (s[i] == '0') c++;
            else {
                a.push_back(c);
                c = 0;
            }
        }
        if (c > 0) {
            a.push_back(c);
        } else {
            a.push_back(0);
        }
        sets.push_back(a);
        ss++;
        
        int i = l;
        int len = (int)a.size()-1;
        while (i < n) {
            if (s[i] == '0') a[len]++;
            else {
                a.push_back(0);
                len++;
            }
            if (s[i-l] == '0') {
                a[0]--;
                // if (a[0] == 0) {
                //     a.erase(a.begin());
                //     len--;
                // }
            } else {
                a.erase(a.begin());
                len--;
            }
            // printf("Sets:\n");
            // for (vector<int> it: sets) {
            //     for (int v: it) {
            //         printf("%d ", v);
            //     }
            //     printf("\n");
            // }
            // printf("I %d, a:\n", i);
            // for (int j = 0; j < (int)a.size(); j++) {
            //     // if (j == (int)a.size()-1 && a[j] == 0) continue;
            //     printf("%d ", a[j]);
            // }
            // printf("\n");
            bool f = true;
            for (vector<int> it: sets) {
                if (is_reversable(it, a)) {
                    f = false;
                    break;
                }
            }
            // printf("KQ %d\n", f);
            // printf("-----\n");
            if (f) {
                // vector<int> cp;
                // if (a[len] > 0) cp = vector<int>(a.begin(), a.end());
                // else cp = vector<int>(a.begin(), a.begin()+len);
                // sets.push_back(cp);s
                sets.push_back(a);
                ss++;
            }
            i++;
        }
        // printf("For size %d result %d \n", l, ss);
        rs += ss;
    }
    printf("%d\n", rs);
}
int main() {
    int t;
    cin >> t;
    string s;
    for (int cs = 0; cs < t; cs++) {
        cin >> s;
        solve(s);
    }
    return 0;
}