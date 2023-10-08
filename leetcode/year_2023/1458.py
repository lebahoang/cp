def run(a, b,i,j,dp):
    if dp[i][j] > -(10**9):
        return dp[i][j]
    f1 = f2 = False
    rs = a[i]*b[j]
    if i-1 >= 0:
        rs = max(rs, run(a,b,i-1,j,dp))
        f1 = True
    if j-1 >= 0:
        rs = max(rs, run(a,b,i,j-1,dp))
        f2 = True
    if f1 and f2:
        rs = max(rs, run(a,b,i-1,j-1,dp)+(a[i]*b[j]))
    dp[i][j] = rs
    return rs

def solve(a,b):
    n = len(a)
    m = len(b)
    dp = [[-(10**9) for _ in range(m)] for _ in range(n)]
    rs = run(a,b,n-1,m-1,dp)
    for i in range(n):
        for j in range(m):
            print(i,j,dp[i][j])
    return rs


a = [-3,-8,3,-10,1,3,9]
b = [9,2,3,7,-9,1,-8,5,-1, -1]
print(solve(a,b))
