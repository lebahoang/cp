def solve(n: int, m: int, k: int) -> int:
    if k > m:
        return 0
    mod = 10**9+7
    dp = []
    prefix = []
    sum = []
    for _ in range(n+3):
        t = []
        for _ in range(m+3):
            tt = []
            for _ in range(k+3):
                tt.append(0)
            t.append(tt)
        dp.append(t)
    for _ in range(n+3):
        t = []
        t1 = []
        for _ in range(k+3):
            t.append([0]*(m+3))
            t1.append(0)
        prefix.append(t)
        sum.append(t1)
    for x in range(1, k+1):
        for i in range(1, n+1):
            for j in range(1, m+1):
                if i == 1:
                    if x == 1:
                        dp[i][j][x] = 1
                    else:
                        continue
                else:
                    if j > 1:
                        t1 = (prefix[i-1][x-1][j-1]%mod * i%mod)%mod
                        dp[i][j][x] = (dp[i][j][x]%mod + t1)%mod
                        t2 = (dp[i-1][j][x]%mod * i%mod)%mod
                        dp[i][j][x] = (dp[i][j][x]%mod + t2)%mod
                    else:
                        if x == 1:
                            dp[i][j][x] = 1
                        else:
                            continue

                if j == 1:
                    prefix[i][x][j] = dp[i][j][x]
                else:
                    t = (prefix[i][x][j-1]%mod + dp[i][j][x]%mod)%mod
                    prefix[i][x][j] = t
                sum[i][x] = (sum[i][x]%mod + dp[i][j][x]%mod)%mod
                print('dp[{:d}][{:d}][{:d}]'.format(i,j,x), dp[i][j][x])
                print('prefix[{:d}][{:d}]'.format(i, x), prefix[i][x])
                print('sum[{:d}][{:d}]'.format(i,x), sum[i][x])
    return sum[n][k]


n = 2
m = 3
k = 1
print('n=', n, ' m=', m, ' k=', k)
print(solve(n,m,k))