#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

long long cost(vector<long long>& b, vector<long long>& prefix, int k, int j, int i, int x) {
    int k_left = x-j;
    int k_right = i-x;
    if (x > 0 && j > 0)
        return k_left*b[x] - k_left*(k_left+1)/2 - (prefix[x-1]-prefix[j-1]) 
             + prefix[i]-prefix[x] - k_right*b[x] - k_right*(k_right+1)/2;
    else if (x > 0 && j == 0) {
        return k_left*b[x] - k_left*(k_left+1)/2 - prefix[x-1] 
             + prefix[i]-prefix[x] - k_right*b[x] - k_right*(k_right+1)/2;
    }
    return prefix[i]-prefix[x] - k_right*b[x] - k_right*(k_right+1)/2;
}

int solve(vector<int>& a, int k) {
    vector<long long> b = {};
    for (int i = 1; i <= (int)a.size(); i++) {
        if (a[i-1] == 1) b.push_back((long long)i);
    }
    int n = (int)b.size();
    vector<long long> prefix(n, 0);
    for (int i = 0; i < n; i++) {
        if (i == 0) prefix[i] = b[i];
        else prefix[i] = prefix[i-1]+b[i];
    }
    long long rs = 1e10;
    for (int i = 0; i < n; i++) {
        int j = i-k+1;
        if (j >= 0) {
            if (k%2 == 0) {
                int x = (i+j)/2;
                int y = x+1;
                rs = min({rs, cost(b,prefix,k,j,i,x), cost(b,prefix,k,j,i,y)});
            } else {
                int x = (i+j)/2;
                rs = min(rs, cost(b,prefix,k,j,i,x));
            }
        }
    }
    return (int)rs;
}
int main() {
    // vector<int> a = {1,0,0,1,0,1};
    vector<int> a = {1,1,0,1};
    int k = 2;
    printf("%d\n", solve(a,k));
    return 0;
}
