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

// g++ -std=c++14 -stdlib=libc++ -O2 -o s.out 41.cpp && ./s.out < x.txt
// g++ -std=c++14 -stdlib=libc++ -O2 -o s.out 41.cpp && ./s.out < ~/Downloads/running_on_fumes_chapter_1_input.txt > out41.txt
using namespace std;
// const int INT_MAX = 2e9 + 3;
void coinChangeMin(vector<int>& coins, int index, int amount, int count, int& min_count)
{
    if (amount == 0) min_count = min(min_count, count);
    if (index < 0) return;

    for (int i = amount / coins[index]; i >= 0; --i)
    {
        if (count + i >= min_count) return; // We use larger coins first. 
        coinChangeMin(coins, index - 1, amount - coins[index] * i, count + i, min_count);
    }
}
int minMoney(int amount, vector<int> coins) {
    sort(coins.begin(), coins.end());
    int min_count = INT_MAX;
    coinChangeMin(coins, coins.size() - 1, amount, 0, min_count);
    return min_count == INT_MAX ? 0 : min_count;
}
int main() {
    printf("%d\n", minMoney(100000000, vector<int>{3,5,7,9,12,14,15}));
    return 0;
}