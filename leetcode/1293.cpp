#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>

using namespace std;
int dist[41][41][1605];
void dfs(int& ans, int step,
	vector<vector<int>>& grid, int k, int used, int i, int j,
	int n, int m, vector<vector<bool>>& visited) {

	if (i == n-1 && j == m-1) {
		if (ans == -1 || ans > step) {
			ans = step;
		}
	}
	if (i-1 >= 0 && j >= 0 && visited[i-1][j] == 0) {
		visited[i-1][j] = 1;
		if (grid[i-1][j] == 1 && used < k) {
			if (dist[i-1][j][used+1] == -1 || dist[i-1][j][used+1] > step+1) {
				dist[i-1][j][used+1] = step+1;
				dfs(ans, step+1, grid, k, used+1, i-1, j, n, m, visited);
			}	
		} else if (grid[i-1][j] == 0) {
			if (dist[i-1][j][used] == -1 || dist[i-1][j][used] > step+1) {
				dist[i-1][j][used] = step+1;
				dfs(ans, step+1, grid, k, used, i-1, j, n, m, visited);
			}
		}
		visited[i-1][j] = 0;
	}
	if (i+1 < n && j >= 0 && visited[i+1][j] == 0) {
		visited[i+1][j] = 1;
		if (grid[i+1][j] == 1 && used < k) {
			if (dist[i+1][j][used+1] == -1 || dist[i+1][j][used+1] > step+1) {
				dist[i+1][j][used+1] = step+1;
				dfs(ans, step+1, grid, k, used+1, i+1, j, n, m, visited);
			}
			
		} else if (grid[i+1][j] == 0) {
			if (dist[i+1][j][used] == -1 || dist[i+1][j][used] > step+1) {
				dist[i+1][j][used] = step+1;
				dfs(ans, step+1, grid, k, used, i+1, j, n, m, visited);
			}
		}
		visited[i+1][j] = 0;
	}
	if (i >= 0 && j-1 >= 0 && visited[i][j-1] == 0) {
		visited[i][j-1] = 1;
		if (grid[i][j-1] == 1 && used < k) {
			if (dist[i][j-1][used+1] == -1 || dist[i][j-1][used+1] > step+1) {
				dist[i][j-1][used+1] = step+1;
				dfs(ans, step+1, grid, k, used+1, i, j-1, n, m, visited);
			}
			
		} else if (grid[i][j-1] == 0) {
			if (dist[i][j-1][used] == -1 || dist[i][j-1][used] > step+1) {
				dist[i][j-1][used] = step+1;
				dfs(ans, step+1, grid, k, used, i, j-1, n, m, visited);
			}
			
		}
		visited[i][j-1] = 0;
	}
	if (i >= 0 && j+1 < m && visited[i][j+1] == 0) {
		visited[i][j+1] = 1;
		if (grid[i][j+1] == 1 && used < k) {
			if (dist[i][j+1][used+1] == -1 || dist[i][j+1][used+1] > step+1) {
				dist[i][j+1][used+1] = step+1;
				dfs(ans, step+1, grid, k, used+1, i, j+1, n, m, visited);
			}
		} else if (grid[i][j+1] == 0) {
			if (dist[i][j+1][used] == -1 || dist[i][j+1][used] > step+1) {
				dist[i][j+1][used] = step+1;
				dfs(ans, step+1, grid, k, used, i, j+1, n, m, visited);
			}
		}
		visited[i][j+1] = 0;
	}
}
int solve(vector<vector<int>>& grid, int k) {
	int ans = -1;
	int n = (int)grid.size();
	int m = (int)grid[0].size();
	int step = 0;
	int used = 0;
	vector<vector<bool>> visited(n, vector<bool>(m, false));
	// vector<vector<vector<int>>> dist(n, vector<vector<int>>(m, vector<int>(k+1, 100000)));
	memset(dist, -1, sizeof(dist));
    printf("%d %d %d\n", n, m, k);
	dfs(ans, step, grid, k, used, 0, 0, n, m, visited);
    return ans;
}

struct I {
	int i;
	int j;
	int k;
	int step;
};
int solve2(vector<vector<int>>& grid, int k) {
	int ans = -1;
	int n = (int)grid.size();
	int m = (int)grid[0].size();
	vector<vector<vector<int>>> dist(n, vector<vector<int>>(m, vector<int>(k+1, 100000)));
	queue<I> q = {};
	q.push(I{0,0,0,0});
	while (!q.empty()) {
		I it = q.front();
		q.pop();
		if (it.i == n-1 && it.j == m-1) {
			if (ans == -1 || ans > it.step) {
				ans = it.step;
			}
		}
		vector<pair<int, int>> ds = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
		for (auto x: ds) {
			if (it.i + x.first >= 0 && it.i + x.first < n && it.j + x.second >= 0 && it.j + x.second < m) {
				int a = it.i+x.first;
				int b = it.j+x.second;
				if (grid[a][b] == 1) {
					if (it.k+1 <= k && dist[a][b][it.k+1] > it.step+1) {
						dist[a][b][it.k+1] = it.step+1;
						q.push(I{a,b,it.k+1,it.step+1});
					}
				} else {
					if (it.k <= k && dist[a][b][it.k] > it.step+1) {
						dist[a][b][it.k] = it.step+1;
						q.push(I{a,b,it.k,it.step+1});
					}
				}	
			}
		}
	}
	return ans;
}
int main() {
	printf("%d\n", solve());
	return 0;
}