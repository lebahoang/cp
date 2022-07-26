#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <queue>
#include <utility>


// g++ -std=c++14 -Wshadow -Wall -o s.out -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined 2111.cpp && ./s.out

using namespace std;
struct I {
    int s;
    int e;
    int l;
};
int ceilIndex(std::vector<int>& v, int l, int r, int key)
{
    while (r - l > 1) {
        int m = l + (r - l) / 2;
        if (v[m] > key)
            r = m;
        else
            l = m;
    }
 
    return r;
}
 
I lis(std::vector<int>& v)
{
    if (v.size() == 0)
        return I{-1, -1, -1};

    vector<pair<int, int>> p = {};
    vector<int> tail(v.size(), 0);
    int length = 1; // always points empty slot in tail
    
    int f = 0;
    int s = 0;
    tail[0] = v[0];
    for (int i = 1; i < v.size(); i++) {
 
        // new smallest value
        if (v[i] < tail[0]) {
            tail[0] = v[i];
            if (i > f+1) p.push_back({f, length});
            f = i;
            s = i;
        }
        // v[i] extends largest subsequence
        else if (v[i] >= tail[length - 1]) {
            tail[length] = v[i];
            length++;
            if (!p.empty() && length == p.back().second+1) p.erase(p.begin());
            s = i;
        }
        // v[i] will become end candidate of an existing
        // subsequence or Throw away larger elements in all
        // LIS, to make room for upcoming greater elements
        // than v[i] (and also, v[i] would have already
        // appeared in one of LIS, identify the location
        // and replace it)
        else {
            int ind = ceilIndex(tail, -1, length - 1, v[i]);
            // printf("i %d VAL %d IND %d\n", i, v[i], ind);
            tail[ind] = v[i];
        }
            
    }
    p.push_back({f, length});
    // printf("LENGTH %d\n", length);
    for (auto i: p) {
        // printf("%d %d\n", v[i.first], tail[length-1]);
        if (v[i.first] <= tail[length-1]) {
            return I{i.first, s, length};
        }
    }
    return I{-1, -1, -1};
}

int solve(vector<int>& a, int k) {
    int rs = 0;
    int n = (int)a.size();
    vector<int> x = {};
    for (int i = 0; i < k; i++) {
        int j = i;
        while(j < n) {
            x.push_back(a[j]);
            j += k;
        }
        int m = (int)x.size();
        I p = lis(x);
        // printf("LIS %d %d\n", p.s, p.e);
        rs += m - (p.e - p.s + 1) + (p.e - p.s + 1) - p.l;
        x.clear();
    }
    return rs;
}

int main() {
    // vector<int> a = {4,1,1,1,5,1,1,1,6,7,2,3,4};
    // vector<int> a = {2, 5, 3, 7, 11, 8, 10, 13, 6};
    // vector<int> a = {7,8,9,1,2,3,4,5,6,7};
    vector<int> a = {4,1,5,2,6,2};
    // pair<int, int> p = lis(a);
    // printf("%d %d\n", p.first, p.second);
    int k = 3;
    printf("%d\n", solve(a, k));
    return 0;
}