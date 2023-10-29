def dfs1(i,j,n,m,h,v):
    if i == 0 or j == 0:
        return True
    c = [[-1, 0], [1, 0], [0, -1], [0, 1]]
    f = False
    for x in c:
        a = i+x[0]
        b = j+x[1]
        if a >= 0 and a < n and b >= 0 and b < m and h[i][j] >= h[a][b] and (a,b) not in v:
            v[(a,b)] = 1
            f = dfs1(a,b,n,m,h,v)
            if f:
                break
    return f
def dfs2(i,j,n,m,h,v):
    if i == n-1 or j == m-1:
        return True
    c = [[-1, 0], [1, 0], [0, -1], [0, 1]]
    f = False
    for x in c:
        a = i+x[0]
        b = j+x[1]
        if a >= 0 and a < n and b >= 0 and b < m and h[i][j] >= h[a][b] and (a,b) not in v:
            v[(a,b)] = 1
            f = dfs2(a,b,n,m,h,v)
            if f:
                break
    return f
def run(h):
    n = len(h)
    m = len(h[0])
    # print(n,m)
    rs = []
    for i in range(n):
        for j in range(m):
            v1 = {}
            v2 = {}
            if dfs1(i,j,n,m,h,v1) and dfs2(i,j,n,m,h,v2):
                rs.append([i,j])
    # print(dp1[0][98], dp2[0][98])
    return rs

print(run([[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]))