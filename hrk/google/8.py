def print_all(ind, dp, t, rs):
    if ind == -1:
        rs.append(' '.join(t[::-1]))
        return
    for w, dp_ind in dp[ind]:
        t.append(w)
        print_all(dp_ind, dp, t, rs)
        t.pop(-1)



def solve140(s, wordDict):
    n = len(s)
    t = {}
    for w in wordDict:
        t[w] = True
    wordDict = t
    dp = [[] for i in range(n)]
    for i in range(n):
        if s[:i+1] in wordDict:
            dp[i].append((s[:i+1], -1))

        for j in range(i):
            if len(dp[j]) > 0 and s[j+1:i+1] in wordDict:
                dp[i].append((s[j+1:i+1], j))


    rs = []
    print_all(n-1, dp, [], rs)
    return rs


# s = 'pineapplepenapple'
# wordDict = ["apple", "pen", "applepen", "pine", "pineapple"]

# s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
# wordDict = ["a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"]
# print(solve(s, wordDict))

def get(i, w, A, dp):
    rs = []
    rs_ind = []
    for k in range(len(A)-1, -1, -1):
        rs_t = []
        rs_ind_t = []
        t = k
        h = i
        y = w
        while t >= 0 and h >= 1 and y >= 0:
            x = dp[t][h][y]
            if not x:
                if t == k:
                    rs_t = []
                    break
                rs_t.append(A[t+1])
                rs_ind_t.append(t+1)
                h -= 1
                y -= A[t+1]
            else:
                if t == 0:
                    rs_t.append(A[t])
                    rs_ind_t.append(t)
                t -= 1

        rs_t = rs_t[::-1]
        rs_ind_t = rs_ind_t[::-1]
        print(rs_t)
        if len(rs_t) == i:
            if len(rs) == 0 or rs < rs_t:
                rs = rs_t
                rs_ind = rs_ind_t
    return rs_ind

def get_smaller(A, a,b):
    if len(a) == 0:
        return b
    if len(b) == 0:
        return a
    if len(a) < len(b):
        return a
    if len(a) > len(b):
        return b

    x = [A[x] for x in a]
    y = [A[x] for x in b]
    if x < y:
        return a
    return b


def solve1(A):
    A = sorted(A)
    print(A)
    total = sum(A)
    n = len(A)
    # print('total', total, 'n', n)
    # dp = [[[[] for k in range(total+1)]for j in range(n+1)] for i in range(n)]
    # for i in range(n):
    #     dp[i][1][A[i]] = [i]
    # for i in range(1, n):
    #     for j in range(1, n+1):
    #         for k in range(total+1):
    #             if len(dp[i-1][j][k]) > 0:
    #                 dp[i][j][k] = dp[i-1][j][k]
    #             if k-A[i] >= 0:
    #                 if i-1 >= 0 and j-1 >= 0 and len(dp[i-1][j-1][k-A[i]]) > 0:
    #                     x = dp[i-1][j-1][k-A[i]][:]
    #                     x.append(i)
    #                     dp[i][j][k] = get_smaller(A, dp[i][j][k], x)


    dp = [[[False for k in range(total+1)]for j in range(n+1)] for i in range(n)]
    for i in range(n):
        dp[i][1][A[i]] = True
    for i in range(1, n):
        for j in range(1, n+1):
            for k in range(total+1):
                if dp[i-1][j][k]:
                    dp[i][j][k] = True
                if k-A[i] >= 0:
                    if i-1 >= 0 and j-1 >= 0 and dp[i-1][j-1][k-A[i]]:
                        dp[i][j][k] = True


    d = [0 for i in range(n)]
    for i in range(1,n//2+1):
        if total*i%n == 0:
            w = total*i//n
            if dp[n-1][i][w]:
                rs = get(i,w,A,dp)
                print(i,w,rs)
                if len(rs) > 0:
                    a = []
                    b = []
                    for i in rs:
                        a.append(A[i])
                        d[i] = 1
                    for i in range(n):
                        if d[i] == 0:
                            b.append(A[i])
                    return a,b
    return []


# A = [9,1,2,24]
# A = [6,0,2,2,2,6]
# A = [1, 7, 15, 29, 11, 9]
# A = [1,1,1,1]
A = [ 47, 14, 30, 19, 30, 4, 32, 32, 15, 2, 6, 24 ]
# A = [ 33, 2, 12, 25, 38, 11, 46, 17, 19, 47, 13, 0, 39, 42, 8, 4 ]
print(solve1(A))
                    










