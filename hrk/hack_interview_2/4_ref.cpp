#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;
#define sim template < class c
#define ris return * this
#define dor > debug & operator <<
#define eni(x) sim > typename \
  enable_if<sizeof dud<c>(0) x 1, debug&>::type operator<<(c i) {
sim > struct rge { c b, e; };
sim > rge<c> range(c i, c j) { return rge<c>{i, j}; }
sim > auto dud(c* x) -> decltype(cerr << *x, 0);
sim > char dud(...);
struct debug {
#ifdef LOCAL
~debug() { cerr << endl; }
eni(!=) cerr << boolalpha << i; ris; }
eni(==) ris << range(begin(i), end(i)); }
sim, class b dor(pair < b, c > d) {
  ris << "(" << d.first << ", " << d.second << ")";
}
sim dor(rge<c> d) {
  *this << "[";
  for (auto it = d.b; it != d.e; ++it)
    *this << ", " + 2 * (it == d.b) << *it;
  ris << "]";
}
#else
sim dor(const c&) { ris; }
#endif
};
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "

const int nax = 1e6 + 5;
char _s[nax];

int main() {
    int t;
    scanf("%d", &t);
    for (int x = 0; x < t; x++) {
        int n, k;
        scanf("%d%d", &n, &k);
        scanf("%s", _s);
        vector<int> a(n);
        for(int i = 0; i < n; ++i) {
            a[i] = _s[i] - '0';
        }
        vector<int> intervals;
        int going = 1;
        for(int i = 1; i < n; ++i) {
            if(a[i] == a[i-1]) {
                going++;
            }
            else {
                intervals.push_back(going);
                going = 1;
            }
        }
        intervals.push_back(going);
        
        // int L = 0, R = (int) intervals.size() - 1;
        int window = (int) intervals.size() - 2 - 2 * k;
        int answer = n;
        if(window <= 0) {
            answer = 0;
        }
        else {
            printf("%d \n", window);
            for (int i = 0; i < (int)intervals.size(); i++) {
                printf("%d ", intervals[i]);
            }
            printf("\n");
            vector<int> pref((int) intervals.size() + 1);
            for(int i = 0; i < (int) intervals.size(); ++i) {
                pref[i] = intervals[i];
                if(i) pref[i] += pref[i-1];
            }
            for(int start = 1; start < n; ++start) {
                int end = start + window - 1;
                if(end < (int) intervals.size() - 1) {
                    printf("%d %d %d\n", start-1, end, pref[end] - pref[start-1]);
                    for (int k = start-1; k <= end; k++) {
                        printf("%d ", intervals[k]);
                    }
                    printf("\n");
                    answer = min(answer, pref[end] - pref[start-1]);
                }
            }
        }
        // int answer = n;
        
        printf("%d\n", answer);
    }
}

