def go(i, j, a, grid, dp):
    key = ''.join([str(x) for x in a])
    if key in dp:
        return dp[key]
    

def sovle(grid):
    n = len(grid)
    m = len(grid[0])
    a = []
    s = []
    for i in range(n):
        for j in range(m):
            if grid[i][j] == 1:
                s = [i,j]
            a.append(1)
    dp = {}
    return go(s[0], s[1], a, grid, dp)
