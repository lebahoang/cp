# Given A, B, C, find whether C is formed by the interleaving of A and B.
# Input Format:*
# The first argument of input contains a string, A.
# The second argument of input contains a string, B.
# The third argument of input contains a string, C.
# A: cabde
# B: cfg
# C: cabcdfge
        
# Output Format:
# Return an integer, 0 or 1:
# => 0 : False
# => 1 : True
# Constraints:
# 1 <= length(A), length(B), length(C) <= 150


# len_c = len_a + len_b
# c_can_be_formed[i] = 1 -->  c_can_be_formed[n] 

# i = 2 cab
# i = len_c-1 return c_can_be_formed[i]

# len_c = len(c)
# dp = [0 for i in range(len_c)]
# dp[i] = answer for the question: can I form substring of C up to i
# final answer is dp[len_c-1]


# A: cabde
# B: cfg
# C: cabcdfge

# def solve(A, B, C):
#     len_c = len(C)
#     dp = [0 for _ in range(len_c)]
#     if C[0] == A[0] or C[0] == B[0]:
#         dp[0] = 1
#     for i in range(1, len_c):
#         for j in range(min(i+1, len(A))):
#             k = i-j-1
#             print(j, k, i)
#             if dp[i] == 1:
#                 continue
#             if k < 0:
#                 if A[:j+1] == C[:i+1]:
#                     dp[i] = 1
#                 else:
#                     dp[i] = 0
#                 continue
#             if k >= len(B):
#                 continue
#             if dp[i-1] == 1 and (A[j] == C[i] or B[k] == C[i]):
#                 dp[i] = 1
#             else:
#                 dp[i] = 0
#     print(dp)
#     return dp[len_c-1]


# print(solve('cabde', 'cfg', 'cabcdfge'))
# print(solve('abc', 'abc', 'aacbbc'))

# aavaa
# bbccaa

# aabbccvaaa

# def foo(arr):
#     n = len(arr)
#     s = sum(arr)
#     dp1 = [-1]*(s+1)
#     dp2 = [-1]*(s+1)
#     dp1[0] = 0
#     for i in range(n):
#         for k in range(s+1):
#             if k-arr[i] >= 0 and dp1[k-arr[i]] >= 0:
#                 dp2[k] = max(dp2[k], dp1[k-arr[i]] + arr[i])
#             if arr[i]-k >= 0 and dp1[arr[i]-k] >= 0:
#                 dp2[k] = max(dp2[k], dp1[arr[i]-k] + k)
#             if k+arr[i] <= s and dp1[k+arr[i]] >= 0:
#                 dp2[k] = max(dp2[k], dp1[k+arr[i]])
#             # this is the case: we don't use arr[i] and/or we keep value of dp1[k]
#             dp2[k] = max(dp2[k], dp1[k])
#         for k in range(s+1):
#             dp1[k] = dp2[k]
#             dp2[k] = -1
#         print(dp1)
#     return dp1[0]


# a = [102,101,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100]
# a = [50,70,1,1,1,1,1,1]
# a = [1,1,5]
# print(foo(a))

# you can write to stdout for debugging purposes, e.g.
# print("this is a debug message")

# def to_int(a):
#     return int(''.join([str(x) for x in a]))
# def find_duplicate_number(a):
#     for i in range(1, len(a)):
#         if a[i] == a[i-1]:
#             return i
#     return -1
# def backward_step(a, ind):
#     rs = []
#     i = ind
#     add = 1
#     while i >= 0:
#         t = a[i] + add
#         if i-1 >= 0 and t == a[i-1]:
#             t += 1
#         if t < 10:
#             a[i] = t
#             add = 0
#             break
#         i -= 1
#     if add == 1:
#         if i >= 0:
#             return a, i+1
#         else:
#             rs.append(1)
#             rs.extend(a)
#             return rs, 1
#     else:
#         return a, i+1

# def solve(N, flag):
#     a = [int(x) for x in str(N)]
#     if len(a) == 1:
#         a.insert(0, 0)
#     ind = find_duplicate_number(a)
#     if ind != -1:
#         b, j = backward_step(a, ind)
#         f = True
#         for i in range(j, len(b)):
#             if f:
#                 b[i] = 0
#                 f = False
#             else:
#                 b[i] = 1
#                 f = True
#         return to_int(b)
#     else:
#         if flag == 1:
#             return N
#         x = a[-2]*10 + a[-1]
#         if x == 99:
#             x += 2
#             b, j = backward_step(a, len(a)-3)
#             f = True
#             for i in range(j, len(b)):
#                 if f:
#                     b[i] = 0
#                     f = False
#                 else:
#                     b[i] = 1
#                     f = True
#             return to_int(b)
#         elif x == 98:
#             x += 3
#             b, j = backward_step(a, len(a)-3)
#             # print(len(a)-3, b, j)
#             f = True
#             for i in range(j, len(b)):
#                 if f:
#                     b[i] = 0
#                     f = False
#                 else:
#                     b[i] = 1
#                     f = True
#             return to_int(b)
#         else:
#             x += 1
#             strx = str(x)
#             if len(strx) == 1:
#                 strx = '0' + strx
#             y = [int(i) for i in strx]
#             if y[0] == y[1]:
#                 x += 1
#             strx = str(x)
#             if len(strx) == 1:
#                 strx = '0' + strx
#             a[-2] = int(strx[0])
#             a[-1] = int(strx[1])
#             return to_int(a)
# def solution(N):
#     return solve(N, 0)

# print(solution(666))

n = 10
m = 10
for i in range(1, n+1):
    t = []
    for j in range(1, m+1):
        t.append(i*j)
    print(t)