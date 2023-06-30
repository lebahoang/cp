def solve(a, c):
    aa = []
    n = len(a)
    for i in range(n):
        aa.append((a[i], i))
    aa = sorted(aa, key=lambda x: x[0])
    print(aa)
    prefix = [0]*n
    prefix_m = [0]*n
    sum_c = [0]*n
    sum = [0]*n
    sum_c[0] = c[aa[0][1]]
    for i in range(1, n):
        ci = aa[i][1]
        if i == 1:
            prefix[i] = aa[i][0] - aa[i-1][0]
            prefix_m[i] = prefix[i] * c[ci]
            sum[i] = prefix_m[i]
        else:
            prefix[i] = prefix[i-1] + (aa[i][0] - aa[i-1][0])
            prefix_m[i] = prefix[i] * c[ci]
            sum[i] = sum[i-1] + prefix_m[i]
        sum_c[i] = sum_c[i-1] + c[ci]

    print(prefix, prefix_m, sum, sum_c)
    rs = 1e18
    for i in range(0, n):
        if i == 0:
            print(i, sum[n-1])
            rs = min(rs, sum[n-1])
        elif i == n-1:
            print(i, prefix[i]*sum_c[i-1] - sum[i-1])
            rs = min(rs, prefix[i]*sum_c[i-1] - sum[i-1])
        else:
            x = (sum[n-1]-sum[i]) - prefix[i]*(sum_c[n-1] - sum_c[i])
            y = prefix[i]*sum_c[i-1] - sum[i-1]
            t = x+y
            print(i, t)
            rs = min(rs, t)
    return rs


# rs = solve([1, 3, 5, 2], [2, 3, 1, 14])
# print(rs)
rs = solve([1, 1, 1, 10], [1, 2, 1, 999999])
print(rs)
