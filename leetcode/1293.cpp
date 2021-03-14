#include <vector>

using namespace std;
int dfs(int ans, int step,
	vector<vector<int>>& grid, int k, int used, int i, int j,
	int n, int m, vector<vector<bool>>& visited, vector<vector<int>>& dist) {

	if (i == n-1 && j == m-1) {
		if (ans == -1 || ans > step) {
			ans = step;
		}
		return ans;
	}
	if (i-1 >= 0 && j >= 0 && visited[i-1][j] == 0) {
		visited[i-1][j] = 1;
		if (grid[i-1][j] == 1 && used < k) {
			if (dist[i-1][j] == -1 || dist[i-1][j] > step+1) {
				dist[i-1][j] = step+1;
				ans = dfs(ans, step+1, grid, k, used+1, i-1, j, n, m, visited, dist);
			}
				
		} else if (grid[i-1][j] == 0) {
			if (dist[i-1][j] == -1 || dist[i-1][j] > step) {
				dist[i-1][j] = step;
				ans = dfs(ans, step+1, grid, k, used, i-1, j, n, m, visited, dist);
			}
		}
		visited[i-1][j] = 0;
	}
	if (i+1 < n && j >= 0 && visited[i+1][j] == 0) {
		visited[i+1][j] = 1;
		if (grid[i+1][j] == 1 && used < k) {
			if (dist[i+1][j] == -1 || dist[i+1][j] > step+1) {
				dist[i+1][j] = step+1;
				ans = dfs(ans, step+1, grid, k, used+1, i+1, j, n, m, visited, dist);
			}
			
		} else if (grid[i+1][j] == 0) {
			if (dist[i+1][j] == -1 || dist[i+1][j] > step) {
				dist[i+1][j] = step;
				ans = dfs(ans, step+1, grid, k, used, i+1, j, n, m, visited, dist);
			}
		}
		visited[i+1][j] = 0;
	}
	if (i >= 0 && j-1 >= 0 && visited[i][j-1] == 0) {
		visited[i][j-1] = 1;
		if (grid[i][j-1] == 1 && used < k) {
			if (dist[i][j-1] == -1 || dist[i][j-1] > step+1) {
				dist[i][j-1] = step+1;
				ans = dfs(ans, step+1, grid, k, used+1, i, j-1, n, m, visited, dist);
			}
			
		} else if (grid[i][j-1] == 0) {
			if (dist[i][j-1] == -1 || dist[i][j-1] > step) {
				dist[i][j-1] = step;
				ans = dfs(ans, step+1, grid, k, used, i, j-1, n, m, visited, dist);
			}
			
		}
		visited[i][j-1] = 0;
	}
	if (i >= 0 && j+1 < m && visited[i][j+1] == 0) {
		visited[i][j+1] = 1;
		if (grid[i][j+1] == 1 && used < k) {
			if (dist[i][j+1] == -1 || dist[i][j+1] > step+1) {
				dist[i][j+1] = step+1;
				ans = dfs(ans, step+1, grid, k, used+1, i, j+1, n, m, visited, dist);
			}
		} else if (grid[i][j+1] == 0) {
			if (dist[i][j+1] == -1 || dist[i][j+1] > step) {
				dist[i][j+1] = step;
				ans = dfs(ans, step+1, grid, k, used, i, j+1, n, m, visited, dist);
			}
		}
		visited[i][j+1] = 0;
	}
	return ans;
}
int solve(vector<vector<int>>& grid, int k) {
	int ans = -1;
	int n = (int)grid.size();
	int m = (int)grid[0].size();
	int step = 0;
	int used = 0;
	vector<vector<bool>> visited(n, vector<bool>(m, false));
	vector<vector<int>> dist(n, vector<int>(m, -1));
	return dfs(ans, step, grid, k, used, 0, 0, n, m, visited, dist);
}
int main() {
	0,1,0,0,0,1,0,0
	0,1,0,1,0,1,0,1
	0,0,0,1,0,0,1,0
    return 0;
}