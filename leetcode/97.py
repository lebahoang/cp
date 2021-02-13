# def solve(s1, s2, s3): 
#     n = len(s1)
#     m = len(s2)
#     l = len(s3)
#     if n+m != l: return False
#     if n == 0:
#         if s2 == s3:
#             return True
#         else:
#             return False
#     if m == 0:
#         if s1 == s3:
#             return True
#         else:
#             return False


#     dp = [[None for j in range(m)] for i in range(n)]
#     if s1[0]+s2[0] == s3[:2] or s2[0]+s1[0] == s3[:2]:
#         dp[0][0] = True
#     else:
#         dp[0][0] = False

#     for j in range(m):
#         if s1[0]+s2[:j+1] == s3[:j+2] or \
#         s2[0:j+1]+s1[0] == s3[:j+2] or \
#         (dp[0][j-1] and s2[j] == s3[j+1]):
#             dp[0][j] = True
#         else:
#             dp[0][j] = False


#     for i in range(n):
#         if s1[:i+1]+s2[0] == s3[:i+2] or \
#         s2[0]+s1[:i+1] == s3[:i+2] or \
#         (dp[i-1][0] and s1[i] == s3[i+1]):
#             dp[i][0] = True
#         else:
#             dp[i][0] = False

#     for i in range(1, n):
#         for j in range(1, m):
#             if (dp[i-1][j] and s1[i] == s3[i+j+1]) or \
#             (dp[i][j-1] and s2[j] == s3[i+j+1]) or \
#             (dp[i-1][j-1] and s1[i]+s2[j] == s3[i+j:i+j+2]) or \
#             (dp[i-1][j-1] and s2[j]+s1[i] == s3[i+j:i+j+2]):
#                 dp[i][j] = True
#             else:
#                 dp[i][j] = False
#     return dp[n-1][m-1]

# n = len(s1)
# m = len(s2)
# l = len(s3)
# print(n,m,l)
# print(solve(s1, s2, s3, n, m, l, 0, 0, 0, {}))

# print(solve(s1, s2, s3))

# def go(n,k,r,c,kk,pos,visited,rs):
#     if kk == k:
#         rs.append(pos)
#         return
#     next_points = [(r-2,c-1),(r-2,c+1),(r-1,c-2),(r-1,c+2),(r+1,c-2),(r+1,c+2),(r+2,c-1),(r+2,c+1)]
#     for p in next_points:
#         if p[0] < 0 or p[0] >= n or p[1] < 0 or p[1] >= n:
#             continue
#         go(n,k,p[0],p[1],kk+1,pos*1.0/8.0,visited,rs)

# def go1(n,rr,cc,r,c,m,dp):
#     if (r,c,m) in dp:
#         return dp[r,c,m]
#     if m == 0:
#         if rr == r and cc == c: return 1.0
#         return 0.0

#     total_pos = 0.0
#     prev_points = [(r-2,c-1),(r-2,c+1),(r-1,c-2),(r-1,c+2),(r+1,c-2),(r+1,c+2),(r+2,c-1),(r+2,c+1)]
#     for p in prev_points:
#         if p[0] < 0 or p[0] >= n or p[1] < 0 or p[1] >= n:
#             continue
#         total_pos += go1(n,rr,cc,p[0],p[1],m-1,dp)*1.0/8.0
#     dp[r,c,m] = total_pos
#     return total_pos



# def two(n,k,r,c):
#     dp = {}
#     rs = 0.0
#     for i in range(n):
#         for j in range(n):
#             rs += go1(n,r,c,i,j,k,dp)
#     return rs

# print(two(3,2,0,0))
# print(two(30,100,20,20))

