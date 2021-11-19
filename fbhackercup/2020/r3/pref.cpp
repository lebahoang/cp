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
#include <map>
#include <unordered_map>

using namespace std;

void test_case() {
	int n, k;
	scanf("%d%d", &n, &k);
	vector<pair<int,int>> in(n);
	vector<int> ss;
	for(int i = 0; i < n; ++i) {
		scanf("%d%d", &in[i].first, &in[i].second);
		// position, type
		ss.push_back(in[i].first);
	}
	sort(ss.begin(), ss.end());
	ss.resize( unique(ss.begin(),ss.end()) - ss.begin() );
	map<int,int> pos_mapping;
	int len = 0;
	for(int pos : ss) {
		pos_mapping[pos] = len++;
	}
	for(pair<int,int>& p : in) {
		assert(pos_mapping.count(p.first));
		p.first = pos_mapping[p.first];
	}
	for (auto it = pos_mapping.begin(); it != pos_mapping.end(); it++) {
		printf("p.first %d value %d\n", it->first, it->second);
	}
	printf("------------\n");
	for (int i = 0; i < n; i++) {
		printf("i %d p %d r %d\n", i, in[i].first, in[i].second);
	}
	// dp[pos][skipped] - smallest number of intervals used
	const int INF = 1e9 + 5;
	vector<vector<int>> dp(len + 1, vector<int>(k + 1, INF));
	dp[0][0] = 0;
	for(int L = 0; L < len; ++L) {
		bool any_one = false;
		for(pair<int,int> p : in) {
			if(p.first == L && p.second == 1) {
				any_one = true;
			}
		}
		if(!any_one) {
			for(int skip = 0; skip <= k; ++skip) {
				dp[L+1][skip] = min(dp[L+1][skip], dp[L][skip]);
			}
		}
		for(int R = L; R < len; ++R) {
			vector<pair<int,int>> they;
			for(int i = 0; i < n; ++i) {
				if(L <= in[i].first && in[i].first <= R) {
					printf("aaaa %d %d %d\n", in[i].first, i, in[i].second);
					they.emplace_back(i, in[i].second); // time, type
				}
			}
			int best_skipped = INF;
			int bad = 0;
			for(pair<int,int> p : they) {
				if(p.second == 0) {
					bad++;
				}
			}
			best_skipped = bad;
			for(pair<int,int> p : they) {
				if(p.second == 0) {
					bad--;
				}
				else {
					bad++;
				}
				best_skipped = min(best_skipped, bad);
			}
			printf("L %d R %d best %d\n", L, R, best_skipped);
			for(int skip = 0; skip + best_skipped <= k; ++skip) {
				int skip2 = skip + best_skipped;
				dp[R+1][skip2] = min(dp[R+1][skip2], dp[L][skip] + 1);
			}
		}
	}
	int answer = INF;
	for(int skip = 0; skip <= k; ++skip) {
		answer = min(answer, dp[len][skip]);
	}
	if(answer == INF) {
		answer = -1;
	}
	printf("%d\n", answer);
}

int main() {
	int T;
	scanf("%d", &T);
	for(int nr = 1; nr <= T; ++nr) {
		// cerr << nr << " ";
		printf("Case #%d: ", nr);
		test_case();
	}
	// cerr << endl;
}
