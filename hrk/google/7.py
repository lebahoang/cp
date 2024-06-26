def calculate(s):
    x = 0
    y = 0
    for i in s:
        if i == 'W': x += 1
        else: y += 1
    return x*y
def do(A,B,dp,i,k):
    if dp[i][k] > -1:
        return dp[i][k]
    if k == 1:
        dp[i][k] = calculate(A[:i+1])
        return dp[i][k]

    for j in range(i):
        if j+1 < k-1: continue
        x = do(A,B,dp,j,k-1)
        y = calculate(A[j+1:i+1])
        if dp[i][k] == -1 or dp[i][k] > x+y:
            dp[i][k] = x+y
    return dp[i][k]

def solve(A,B):
    n = len(A)
    # print('lenA', n)
    dp = [[-1 for j in range(B+1)] for i in range(n)]
    rs = do(A,B,dp,n-1,B)
    # print(dp)
    return rs


# A = 'BWWWWBBWWBWBWWBBBBBWBWWBBBWWWWBBBW'
# B = 28
# A = 'WBWB'
# B = 4
#print(solve(A,B))


def solve1(A):
    n = len(A)
    dp = [[False for j in range(n)] for i in range(n)]
    for k in range(1, n):
        for i in range(n):
            if i+k < n:
                if A[i] == '(' and A[i+k] == ')':
                    if k == 1:
                        dp[i][i+k] = True
                    elif k == 3 and A[i+1] == ')' and A[i+k-1] == '(':
                        dp[i][i+k] = True
                    elif dp[i+1][i+k-1]:
                        dp[i][i+k] = True
                    else:
                        for j in range(i+1, i+k-1):
                            if dp[i][j] and dp[j+1][i+k]:
                                dp[i][i+k] = True
                                break


    maxV = 0
    for k in range(1, n):
        for i in range(n):
            if i+k < n and dp[i][i+k]:
                if maxV == -1 or maxV < k+1:
                    maxV = k+1
    return maxV

def solve2(A):
    n = len(A)
    dp = [0 for i in range(n)]
    for i in range(1, n):
        if A[i] == ')':
            if A[i-1] == '(':
                dp[i] = 2
                if i-2 >= 0:
                    dp[i] += dp[i-2]
            else:
                t = i-dp[i-1]-1
                if t >= 0 and A[t] == '(':
                    dp[i] = dp[i-1]+2
                    if i-dp[i] >= 0:
                        dp[i] += dp[i-dp[i]]

    maxV = 0
    for i in range(n):
        if maxV < dp[i]:
            maxV = dp[i]
    return maxV


# A = '(())(())'
# A = '((()))()'
# A = '))))'
# A = '((())()(()((())())(()()))))))(((((()'
A = "((())())(()))(()()(()(()))(()((((()))))))((()())()))()()(()(((((()()()())))()())(()()))((((((())))((()))()()))))(()))())))()))()())((()()))))(()(((((())))))()((()(()(())((((())(())((()()(()())))())(()(())()()))())(()()()))()(((()())(((()()())))(((()()()))(()()))()))()))))))())()()((()(())(()))()((()()()((())))()(((()())(()))())())))(((()))))())))()(())))()())))())()((()))((()))()))(((())((()()()(()((()((())))((()()))())(()()(()))))())((())))(()))()))))))()(()))())(()())))))(()))((())(()((())(((((()()()(()()())))(()())()((()(()()))(()(())((()((()))))))))(()(())()())()(()(()(()))()()()(()()())))(())(()((((()()))())))(())((()(())())))))())()()))(((())))())((()(()))(()()))((())(())))))(()(()((()((()()))))))(()()()(()()()(()(())()))()))(((()(())()())(()))())))(((()))())(()((()))(()((()()()(())()(()())()(())(()(()((((())()))(((()()(((()())(()()()(())()())())(()(()()((()))))()(()))))(((())))()()))(()))((()))))()()))))((((()(())()()()((()))((()))())())(()((()()())))))))()))(((()))))))(()())))(((()))((()))())))(((()(((())))())(()))))(((()(((((((((((((())(((()))((((())())()))())((((())(((())))())(((()))))()())()(())())(()))))()))()()()))(((((())()()((()))())(()))()()(()()))(())(()()))()))))(((())))))((()()(()()()()((())((((())())))))((((((()((()((())())(()((()))(()())())())(()(())(())(()((())((())))(())())))(()()())((((()))))((()(())(()(()())))))))))((()())()()))((()(((()((()))(((((()()()()()(()(()((()(()))(()(()((()()))))()(()()((((((()((()())()))((())()()(((((()(()))))()()((()())((()())()(())((()))()()(()))"
# A = ')()))(())((())))))())()(((((())())((()())(())((((())))())((()()))(()(((()()(()((()()))(())()))((('

print(solve1(A))
print(solve2(A)) 

