def get_bin(x, l):
    rs = bin(x)[2:]
    if len(rs) < l:
        rs = '0'*(l-len(rs)) + rs
    return rs

# def get_sum(a, n):
#     cnt = [0 for _ in range(n)]
#     rs = ''
#     for i in range(n-1, -1, -1):
#         # t = get_bin(a[i] + cnt[i], n)
#         t = bin(a[i] + cnt[i])[2:]
#         # print(a[i]+cnt[i], 'iii')
#         rs = t[-1] + rs
#         jj = i-1
#         for j in range(len(t)-2, -1, -1):
#             if t[j] == '1':
#                 cnt[jj] += 1
#             jj -= 1
#     # print(rs)
#     return int(rs, 2)

def get_sum(a, n):
    cnt = [0 for _ in range(n)]
    rs = 0
    j = 0
    for i in range(n-1, -1, -1):
        rs += 2**j * a[i]
        j += 1
    # print(rs)
    return rs

def solve(a, b, c, d):
    n = 50
    a1 = [[0,0] for _ in range(n)]
    for i in range(c, d+1):
        t = get_bin(i, n)
        for v in range(len(t)):
            if t[v] == '1':
                a1[v][1] += 1
            else:
                a1[v][0] += 1
    # print(a1)
    mod = 1000000007
    rs = 0
    for i in range(a, b+1):
        x = [0 for _ in range(n)]
        t = get_bin(i, n)
        for j in range(n):
            if t[j] == '0' and a1[j][1] > 0:
                x[j] += a1[j][1]
            elif t[j] == '1' and a1[j][0] > 0:
                x[j] += a1[j][0]
        rs = (rs%mod + get_sum(x, n)%mod) % mod
        # print(i, x, get_sum(x, n), rs)
    return rs

for _ in range(10):
    print(solve(1,5000,1,5000))

# 0010
# 0111
# ----
# 0101


# 0010
# 1000
# ----
# 1010


100
101

