import math

def find_min_for_sub_matrix(n,m):
    # fix column iterate row
    dp = [-1 for _ in range(n+1)]
    for l in range(1, n+1):
        # if global_dp[l][m] != -1:
        #     dp[l] = global_dp[l][m]
        #     continue
        if l == 1:
            dp[l] = m
        elif l == 2:
            if m > 1:
                dp[l] = min(2*m, (m-m%l)//2 + (m%l)*l)
            else:
                dp[l] = l
        else:
            if l == m:
                dp[l] = 1
            else:
                for j in range(1, l//2+2):
                    if dp[l] == -1 or dp[l] > dp[j]+dp[l-j]:
                        dp[l] = dp[j]+dp[l-j]
        # global_dp[l][m] = dp[l]



    # fix row iterate column
    dp2 = [-1 for _ in range(m+1)]
    for l in range(1, m+1):
        # if global_dp[n][l] != -1:
        #     dp2[l] = global_dp[n][l]
        #     continue
        if l == 1:
            dp2[l] = n
        elif l == 2:
            if m > 1:
                dp2[l] = min(2*n, (n-n%l)//2 + (n%l)*l)
            else:
                dp2[l] = l
        else:
            if l == n:
                dp2[l] = 1
            else:
                for j in range(1, l//2+2):
                    if dp2[l] == -1 or dp2[l] > dp2[j]+dp2[l-j]:
                        dp2[l] = dp2[j]+dp2[l-j]
        # global_dp[n][l] = dp2[l]

    # print(dp)
    # print(dp2)
    # print(min(dp[-1], dp2[-1]))
    return min(dp[-1], dp2[-1])


n = 5
m = 11
min_v = -1
if n == m:
    min_v = 1
else:
    dp = [[-1 for _ in range(m+1)] for _ in range(n+1)]
    for l in range(1, n//2+1):
        a = -1
        if dp[l][m] == -1:
            dp[l][m] = find_min_for_sub_matrix(l, m)
            a = dp[l][m]
        else:
            print('COOL')
            a = dp[l][m]
        b = -1
        if dp[n-l][m] == -1:
            dp[n-l][m] = find_min_for_sub_matrix(n-l, m)
            b = dp[n-l][m]
        else:
            print('COOL')
            b = dp[n-l][m]
        if min_v == -1 or min_v > a+b:
            min_v = a+b
    for l in range(1, m//2+1):
        a = -1
        if dp[n][l] == -1:
            dp[n][l] = find_min_for_sub_matrix(n, l)
            a = dp[n][l]
        else:
            print('COOL')
            a = dp[n][l]
        
        b = -1
        if dp[n][m-l] == -1:
            dp[n][m-l] = find_min_for_sub_matrix(n, m-l)
            b = dp[n][m-l]
        else:
            print('COOL')
            b = dp[n][m-l]
        if min_v == -1 or min_v > a+b:
            min_v = a+b
print('final', min_v)
