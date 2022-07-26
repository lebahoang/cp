#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <utility>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;
// g++ -std=c++14 -Wshadow -Wall -o s.out -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined 2183.cpp && ./s.out
struct I {
    map<int, int> m;
    int cnt;
};
void sieve(vector<int>& spf, int maxN)
{
    spf[1] = 1;
    for (int i=2; i<maxN; i++)
 
        // marking smallest prime factor for every
        // number to be itself.
        spf[i] = i;
 
    // separately marking spf for every even
    // number as 2
    for (int i=4; i<maxN; i+=2)
        spf[i] = 2;
 
    for (int i=3; i*i<maxN; i++)
    {
        // checking if i is prime
        if (spf[i] == i)
        {
            // marking SPF for all numbers divisible by i
            for (int j=i*i; j<maxN; j+=i)
 
                // marking spf[j] if it is not
                // previously marked
                if (spf[j]==j)
                    spf[j] = i;
        }
    }
}

void getFactorization(int x, vector<int>& spf, map<int, int>& set) {
    int t = -1;
    int cnt = 0;
    while (x != 1)
    {
        if (t == -1 || t != spf[x]) {
            if (t != -1) {
                set[t] = cnt;
            }
            t = spf[x];
            cnt = 1;
        } else {
            cnt++;
        }
        x = x / spf[x];
    }
    set[t] = cnt;
}

bool canSelfCombine(map<int, int>& x, map<int, int>& setk) {
    int cnt = 0;
    for (auto it = setk.begin(); it != setk.end(); it++) {
        int number = it->first;
        int kCnt = it->second;
        if (x.find(number) != x.end()) {
            if (x[number]*2 >= kCnt) cnt++;
        }
    }
    if (cnt == (int)setk.size()) return true;
    return false;
}

bool canCombine(map<int, int>& x, map<int, int>& y, map<int, int>& setk) {
    int cnt = 0;
    for (auto it = setk.begin(); it != setk.end(); it++) {
        int number = it->first;
        int kCnt = it->second;
        int total = 0;
        if (x.find(number) != x.end()) {
            total += x[number];
        }
        if (y.find(number) != y.end()) {
            total += y[number];
        }
        if (total >= kCnt) cnt++;
    }
    if (cnt == setk.size())
        return true;
    return false;
}

long long solve(vector<int>& nums, int k) {
    vector<int> x(100005, 0);
    vector<int> spf(100005, 0);
    sieve(spf, 100005);
    map<int, int> setk;
    map<int, int> set;
    getFactorization(k, spf, setk);


    vector<int> numsB = {};
    vector<string> mp = {};
    long long rs = 0;
    long long cnta = 0;
    long long cntb = 0;
    int n = (int)nums.size();
    unordered_map<string, I> m;
    for (int i = 0; i < n; i++) {
        x[nums[i]]++;
        if (nums[i]%k == 0) {
            cnta++;
        } else {
            cntb++;
            if (x[nums[i]] == 1) numsB.push_back(nums[i]);
        }
    }
    rs = cnta*(cnta-1)/2 + cnta*cntb;
    for (int i: numsB) {
        if (x[i] > 0) {
            set.clear();
            getFactorization(i, spf, set);
            string str = "";
            map<int, int> v;
            for (auto t = set.begin(); t != set.end(); t++) {
                if (setk.find(t->first) != setk.end()) {
                    str.append(to_string(t->first));
                    str.append("-");
                    if (setk[t->first] >= t->second) {
                        v[t->first] = t->second;
                        str.append(to_string(t->second));
                    } else {
                        v[t->first] = setk[t->first];
                        str.append(to_string(setk[t->first]));
                    }
                    str.append(";");
                }
            }
            if (str != "") {
                if (m.find(str) == m.end()) {
                    mp.push_back(str);
                    m[str] = I{v ,x[i]};
                } else {
                    m[str].cnt += x[i];
                }
            }
        }
    }
    // for (string s: mp) printf("mp %s\n", s.c_str());
    long long rs2 = 0;
    for (int i = 0; i < (int)mp.size(); i++) {
        string str = mp[i];
        I it = m[str];
        if (canSelfCombine(it.m, setk)) {
            rs2 += it.cnt*(it.cnt-1)/2;
        }

        for (int j = i+1; j < (int)mp.size(); j++) {
            string str2 = mp[j];
            I it2 = m[str2];
            if (canCombine(it.m, it2.m, setk)) {
                rs2 += it.cnt*it2.cnt;
            }
        }

    }
    // printf("RS %lld\n", rs);
    rs += rs2;
    // printf("RS2 %lld, RS %lld\n", rs2, rs);

    return rs;
}
int main() {
    // vector<int> spf(100005, 0);
    // sieve(spf, 100005);
    // vector<pair<int, int>> ret;
    // unordered_set<int> set;
    // getFactorization(98736, spf, ret, set);
    // for (auto x: ret) {
    //     printf("%d %d\n", x.first, x.second);
    // }

    // srand(time(0));
    // int l = 1;
    // int r = 100000;
    // vector<int> nums = {};
    // for (int i = 0; i < 100001; i++) {
    //     nums.push_back((rand()%(r-l+1)) + l);
    // }
    // int k = 8;

    // vector<int> nums = {8,10,2,5,9,6,3,8,2};
    // int k = 6;

    // vector<int> nums = {100,17,3,77,64,74,11,43,10,37};
    // int k = 20;
    vector<int> nums = {6,6,6,6,6,6,10,10,10};
    int k = 4;
    printf("%lld\n", solve(nums, k));
    return 0;
}