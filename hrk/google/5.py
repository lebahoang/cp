import sys

def solve(A):
    n = len(A)
    dp = [0 for i in range(n)]
    dp[0] = 1 if int(A[0]) > 0 else 0
    for i in range(1, n):
        a = int(A[i])
        b = int(A[i-1:i+1]) if A[i-1] != '0' else 0
        if a > 0:
            dp[i] += dp[i-1]
        if b > 0 and b < 27:
            if i == 1:
                dp[i] += 1
            else:
                dp[i] += dp[i-2]
    
    return dp[n-1]


# A = '32925665678138257423442343752148360796465852883409126159293254159974370974059818198867156827877059067081419274873853679038'
# print(solve(A))


def solve1(A):
    n = len(A[0])
    m = len(A)
    dp = [[0 for j in range(n)] for i in range(m)]

    topdown = [0 for i in range(m)]
    for i in range(m):
        topdown_max = 0
        for j in range(n):
            if i-2 < 0:
                dp[i][j] = A[i][j]
                topdown_max = max(topdown_max, dp[i][j])
            else:
                dp[i][j] = topdown[i-2] + A[i][j]
                topdown_max = max(topdown_max, dp[i][j])
        if i-1 < 0: topdown[i] = topdown_max
        else: topdown[i] = max(topdown[i-1], topdown_max)

    leftright = [0 for i in range(n)]
    for j in range(n):
        leftright_max = 0
        for i in range(m):
            if j-2 < 0:
                dp[i][j] = max(dp[i][j], A[i][j])
                leftright_max = max(leftright_max, dp[i][j])
            else:
                dp[i][j] += leftright[j-2]
                leftright_max = max(leftright_max, dp[i][j])
        if j-1 < 0: leftright[j] = leftright_max
        else: leftright[j] = max(leftright[j-1], leftright_max)

    maxV = 0
    for i in range(m):
        for j in range(n):
            if maxV < dp[i][j]: maxV = dp[i][j]
    return maxV

            

# A = [
#   [74, 37, 82, 1],
#   [66, 38, 16, 1]
# ]
# A = [
#   [16, 5, 54, 55, 36, 82, 61, 77, 66, 61],
#   [31, 30, 36, 70, 9, 37, 1, 11, 68, 14]
# ]
# A = [
#     [1,1,999,1,1,1,1,1],
#     [999,1,1,1,999,1,1,1]
# ]
# A = [
#     [999, 1, 999, 1, 999, 1, 1],
#     [1,   1, 1,   1, 1,   1, 999]
# ]
A = [
    [1]
]
print(solve1(A))




