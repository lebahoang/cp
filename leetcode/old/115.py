# s = 'babgbag'
# s = 'ababababa'
# t = ''

# def solve(s,t):
#     ls = len(s)
#     lt = len(t)
#     if ls == 0 or lt == 0:
#         return 0
#     dp = [[0 for j in range(lt)] for i in range(ls)]

#     if s[0] == t[0]: dp[0][0] = 1
#     for i in range(ls):
#         for j in range(lt):
#             if i-1 >= 0:
#                 dp[i][j] = dp[i-1][j]
#                 if s[i] == t[j]:
#                     if j-1 >= 0:
#                         dp[i][j] += dp[i-1][j-1]
#                     else:
#                         dp[i][j] += 1

#     return dp[ls-1][lt-1]
# print(solve(s,t))

def add(m1, key, val):
    # print(m1,m2)
    m = {}
    for k,v in m1.items():
        m[k] = v[:]
    if key in m:
        m[key][-1] += val
    return m
    

def merge(m1, m2):
    # print(m1, m2)
    m = {}
    for k,v in m1.items():
        m[k] = v[:]
    for k,v in m2.items():
        if k in m:
            m[k].extend(v[:])
        else:
            m[k] = v[:]
    return m

def calculate_max(m):
    print(m)
    t = 0
    for v in m.values():
        for x in v:
            t += x**2
    return t


def go(s, i, j, dp):
    # print(i,j)
    if dp[i][j][0] != -1:
        return dp[i][j]
    if i == j:
        dp[i][j] = [1, {s[i]: [1]}]
        return dp[i][j]

    t, m = go(s, i+1, j, dp)
    dp[i][j][0] = t+1
    dp[i][j][1] = merge(m, {s[i]: [1]})
    for k in range(i+1, j+1):
        if s[i] == s[k]:
            if k < j:
                t1, m1 = go(s,i,k-1,dp)
                t2, m2 = go(s,k+1,j,dp)
                m = merge(add(m1, s[k], 1),m2)
                if dp[i][j][0] > t1+t2 or calculate_max(dp[i][j][1]) < calculate_max(m):
                    dp[i][j][0] = t1+t2
                    dp[i][j][1] = m
            else:
                t1, m1 = go(s,i,k-1,dp)
                m = add(m1, s[k], 1)
                if dp[i][j][0] > t1 or calculate_max(dp[i][j][1]) < calculate_max(m):
                    dp[i][j][0] = t1
                    dp[i][j][1] = m
    return dp[i][j]

def solve546(s):
    if not s: return 0
    n = len(s)
    dp = [[[-1, {}] for j in range(n)] for i in range(n)]
    go(s, 0, n-1, dp)
    m = {}
    # for i in range(n):
    #     for j in range(i, n):
    #         print(i,j,dp[i][j])
    print(dp[0][n-1])

    return calculate_max(dp[0][n-1][1])


# print(solve546([6, 10, 1, 7, 1, 3, 10, 2, 1, 3]))
print(solve546([1,2,1,2,1]))
# print(solve546([i for i in range(2, 103)]))


