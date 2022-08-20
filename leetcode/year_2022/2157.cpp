#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>

// g++ -std=c++17 -Wshadow -Wall -o s.out -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined 2157.cpp && ./s.out
using namespace std;
using ll = long long;

vector<int> solve(vector<string>& words) {
    int n = (int)words.size();
    vector<vector<string>> ws(n, vector<string>{});
    unordered_map<string, vector<string>> map;

    for (int ind = 0; ind < n; ind++) {
        string x = words[ind];
        int m = (int)x.length();
        for (int i = 0; i < m; i++) {
            string a = "";
            if (i < n-1) {
                a = x.substr(0, i).append(x.substr(i+1));
            } else {
                a = x.substr(0, i);
            }
            sort(a.begin(), a.end());
            ws[ind].push_back(a);
            if (map.find(a) == map.end()) {
                map[a] = {x};
            } else {
                map[a].push_back(x);
            }
        }
        sort(x.begin(), x.end());
        if (map.find(x) == map.end()) {
            map[x] = {x};
        } else {
            map[x].push_back(x);
        }
    }
    for (auto i = map.begin(); i != map.end(); i++) {
        printf("K %s\n", i->first.c_str());
        for (string& x: i->second) {
            printf("%s ", x.c_str());
        }
        printf("\n");
    }
    
    vector<int> rs(2, 0);
    rs[0] = 1;
    for (int i = 0; i < n; i++) {
        bool f = false;
        for (string& a: ws[i]) {
            if (map.find(a) != map.end()) {
                int sz = map[a].size();
                if (sz > 1) {
                    f = true;
                    break;
                } 
            }
        }
        if (!f) {
            rs[0]++;
        }
    }
    printf("RS: %d %d\n", rs[0], rs[1]);
    return rs;
}
int main() {
    vector<string> words = {"ab", "bc", "cde"};
    solve(words);
    return 0;
}