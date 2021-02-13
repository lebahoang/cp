def strangePrinter(S):
    memo = {}
    def dp(i, j):
        if i > j: return 0
        if (i, j) not in memo:
            ans = dp(i+1, j) + 1
            for k in range(i+1, j+1):
                if S[k] == S[i]:
                    ans = min(ans, dp(i, k-1) + dp(k+1, j))
            memo[i, j] = ans
        return memo[i, j]

    rs = dp(0, len(S)-1)
    return rs, memo


def go(s, i, j, dp):
    if dp[i][j] != -1:
        return dp[i][j]
    if i == j:
        dp[i][j] = 1
        return dp[i][j]

    dp[i][j] = go(s, i+1, j, dp)+1
    for k in range(i+1, j+1):
        if s[i] == s[k]:
            if k < j:
                dp[i][j] = min(dp[i][j], go(s,i,k-1,dp)+go(s,k+1,j,dp))
            else:
                dp[i][j] = min(dp[i][j], go(s,i,k-1,dp))
    return dp[i][j]

def solve664(s):
    if s == '': return 0
    n = len(s)
    dp = [[-1 for j in range(n)] for i in range(n)]
    rs = go(s, 0, n-1, dp)


    # _, memo = strangePrinter(s)
    # for j in range(n):
    #     for i in range(n):
    #         if i+j < n and (i,i+j) in memo and memo[i,i+j] != dp[i][i+j]:
    #             print(i, i+j, memo[i,i+j], dp[i][i+j], s[i:i+j+1])

    return rs


# 19 23 3 4 dcdbd
# 25 30 3 4 baabcb
# 40 45 4 5 dcdabd
# 22 28 3 4 bddbaab
# 24 30 4 5 dbaabcb
# 35 41 4 5 cacbddc
# 22 29 4 5 bddbaabc
# 23 30 4 5 ddbaabcb
# 22 30 4 5 bddbaabcb
# 21 30 5 6 dbddbaabcb


# s = 'cc'
# s = 'dcdbd'
# s = 'dcddbacca'
s = 'dcddbaccadbccddabbcdcdbddbaabcbbdaccacbddcdabdb'


# s = 'baacdddaaddaaaaccbddbcabdaabdbbcdcbbbacbddcabcaaa'
# s = 'bacdadacbdbcabdabdbcdcbacbdcabca'
# s = 'acaca'
# print(strangePrinter(s))
print(solve664(s))
