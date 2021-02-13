import sys


def solve(A):
    n = len(A)
    m = len(A[0])
    dp = [[[[False for jj in range(m)] for ii in range(n)] for j in range(m)] for i in range(n)]
    for i in range(n):
        for j in range(m):
            dp[i][j][0][0] = True if A[i][j] == 1 else False
            for jj in range(1, m):
                if j+jj < m and dp[i][j][0][jj-1] and A[i][j+jj] == 1:
                    dp[i][j][0][jj] = True

            for ii in range(1, n):
                if i+ii < n and dp[i][j][ii-1][0] and A[i+ii][j] == 1:
                    dp[i][j][ii][0] = True

    for i in range(n):
        for j in range(m):
            for ii in range(1, n):
                for jj in range(1, m):
                    if i+ii < n and j+jj < m:
                        if (dp[i][j][ii-1][jj] and dp[i+ii][j][0][jj]):
                            dp[i][j][ii][jj] = True

    maxV = -1
    maxInds = None
    for i in range(n):
        for j in range(m):
            for ii in range(n):
                for jj in range(m):
                    # print(i,j,ii,jj,dp[i][j][ii][jj])
                    if dp[i][j][ii][jj]:
                        if maxV == -1 or maxV < (ii+1)*(jj+1):
                            maxV = (ii+1)*(jj+1)
                            maxInds = (i,j,ii,jj)

    # print(maxInds)
    return maxV


def solve1(A):
    n = len(A)
    m = len(A[0])
    dp = [[[False for j in range(m)]for i in range(m)] for i in range(n)]
    for i in range(n):
        for k in range(m):
            for j in range(m):
                if k == 0:
                    if A[i][j] == 1:
                        dp[i][j][j+k] = True
                elif j+k < m:
                    if dp[i][j][j+k-1] and A[i][j+k] == 1:
                        dp[i][j][j+k] = True

    maxV = 0
    for a in range(m):
        for b in range(a, m):
            i = 0
            maxVV = 0
            c = 0
            while i < n:
                if dp[i][a][b]:
                    c += 1
                else:
                    if maxVV < c*(b-a+1):
                        maxVV = c*(b-a+1)
                    c = 0
                i += 1
            if c > 0:
                if maxVV < c*(b-a+1):
                    maxVV = c*(b-a+1)
            if maxV < maxVV: maxV = maxVV
    return maxV


# A = [
#     [1,1,1,1],
#     [0,1,1,1],
#     [1,0,1,1],
#     [1,1,1,1]
# ]

A = [
  [1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1],
  [1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
  [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
  [0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1],
  [1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1],
  [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
  [1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1],
  [1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0],
  [1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1],
  [1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1],
  [1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
  [1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
  [1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1],
  [1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1],
  [1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1]
]

print(solve1(A))




