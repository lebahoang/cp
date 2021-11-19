# import sys
# import functools
# import math

# def cmpFunc(a,b):
#     if a[0] < b[0]: return -1
#     elif a[0] > b[0]: return 1

#     if a[1] < b[1]: return -1
#     elif a[1] > b[1]: return 1

#     if a[2] < b[2]: return -1
#     elif a[2] > b[2]: return 1

#     return 0

# a = [(1,2,3), (4,5,6), (1,244,677)]

# print(sorted(a, key=functools.cmp_to_key(cmpFunc)))

# def findLongestCommonStringFromIndex(a, b, ind):
#     n = len(a)
#     m = len(b)
#     i = ind
#     j = 0
#     maxV = -1
#     maxSubstring = ''
#     while i < n and j < m:
#         if a[i] == b[j]:
#             i += 1
#             j += 1
#         else:
#             if maxV == -1 or maxV < i-ind+1:
#                 maxV = i-ind+1
#                 maxSubstring = a[ind:i]
#             if i == ind:
#                 j += 1
#             i = ind
#     if maxV == -1 or maxV < i-ind+1:
#         maxV = i-ind+1
#         maxSubstring = a[ind:i]
#     return maxV, maxSubstring

# # a = 'abcdeffxyzaaaajjjjjjjjjjxxxxxxxxxxxxxxxxxxxkkk'
# # b = 'abcdefkkcdeffttttjjjjjjjjjjkkk'

# a = 'a'*1000
# b = 'a'*1000


# n = len(a)
# m = len(b)

# maxV = -1
# maxSubstring = ''
# for i in range(n):
#     x, y = findLongestCommonStringFromIndex(a,b,i)
#     if maxV == -1 or maxV < x:
#         maxV = x
#         maxSubstring = y
# print(maxSubstring)

# c = 0
# s = 999999999999
# # s = 1000000000000

# ss = int(s**0.5) * 2
# for i in range(2, ss+1):
#     if (2*s+i-i**2) > 0 and (2*s+i-i**2)%(2*i) == 0:
#         #print((2*s+i-i**2)/(2*i))
#         c += 1
# print(ss)
# print('c', c)

# n = 200
# k = 20
# if n < k:
#     print(0)
# else:
#     n = n-k

#     # dp = {}
#     dp = [[[0 for k in range(n+1)] for j in range(k+1)] for i in range(n+1)]
#     for i in range(n+1):
#         # dp[i, 1, i] = 1
#         dp[i][1][i] = 1
#     for i in range(n+1):
#         for j in range(2, k+1):
#             for a in range(n+1):
#                 if i-a >= 0:
#                     c = 0
#                     for b in range(a+1):
#                         # if (i-a,j-1,b) in dp:
#                         #     c += dp[i-a,j-1,b]
#                         if dp[i-a][j-1][b] > 0:
#                             c += dp[i-a][j-1][b]
#                     if c > 0:
#                         # dp[i,j,a] = c
#                         dp[i][j][a] = c

             
#     # print(dp)
#     # print(len(dp.keys())) 
#     count = 0              
#     for a in range(n+1):
#         # if (n,k,a) in dp:
#         #     count += dp[(n,k,a)]
#         count += dp[n][k][a]
#     print(count)

# def go(selected, buf, current_length, cur_n, cur_max, n):
#     if cur_n == n:
#         if current_length > cur_max:
#             cur_max = current_length
#         return cur_max 
    
#     cur_max = go(selected, buf, current_length + 1, cur_n + 1, cur_max, n)

#     # if CtrlA
#     t = selected
#     selected = current_length
#     cur_max = go(selected, buf, current_length, cur_n + 1, cur_max, n)
#     selected = t
#     # if CtrlC
#     t = buf
#     buf = selected
#     cur_max = go(selected, buf, current_length, cur_n + 1, cur_max, n)
#     buf = t
#     # if CtrlV
#     cur_max = go(selected, buf, current_length + buf, cur_n + 1, cur_max, n)
#     return cur_max
# print(go(0, 0, 0, 0, 0, 15))


# import random
# strs = 'abcdefghijklmnopqrstuvwxyz'
# a = b = ''
# n = 3000
# for i in range(n):
#   x = random.randint(0,25)
#   y = random.randint(0,25)
#   a += strs[x]
#   b += strs[y]

# print(a)
# print(b)

import random
n = 50000
k = 7
print(n, k)
for i in range(n):
    print(random.randint(1,n), random.randint(1,k))



