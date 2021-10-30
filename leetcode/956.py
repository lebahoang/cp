# def solve(rods):
#     n = len(rods)

#     d = [[] for i in range(5001)]
#     for i in range(1, 2**n):
#         y = bin(i)[2:]
#         if len(y) < n: y = '0'*(n-len(y)) + y
#         s = 0
#         for j, yy in enumerate(y):
#             if yy == '1': s += rods[j]
#         if s <= 5000:
#             d[s].append(i)

#     for i in range(5000, -1, -1):
#         if d[i]:
#             print(i, d[i])

#     for i in range(5000, -1, -1):
#         for j in range(len(d[i])-1):
#             for jj in range(j+1, len(d[i])):
#                 if d[i][j] & d[i][jj] == 0:
#                     return i
#     return 0

# rods = [1,2,3,4,5,6]
# rods = [2]*20
# print(solve(rods))

# def is_valid1(n, r):
#     a = 2*n-r*(r-1)
#     b = 2*r
#     # print(r, a, b)
#     if a >= b:
#         return True
#     return False
# def is_valid2(n, r):
#     a = 2*n-r*(r-1)
#     b = 2*r
#     # print(r, a, b)
#     if a >= b and a%b == 0:
#         # print(a//b)
#         return True
#     return False

# def solve829(n):
#     l = 1
#     r = 2
#     while True:
#         if l == r:
#             break
#         if is_valid1(n,r):
#             l = r
#             r = r+2
#         else:
#             r = r-1
#     # print('rrrr', r)
#     c = 0
#     for i in range(1, r+1):
#         if is_valid2(n,i):
#             print(i)
#             c += 1
#     return c

# print(solve829(10**9))

class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

def one(head):
    rs = []
    stack = []
    t = head
    i = 0
    while t is not None:
        if not stack:
            stack.append((i,t.val))
        else:
            while stack and t.val > stack[-1][1]:
                it = stack.pop(-1)
                rs.append((it[0], t.val))
            stack.append((i,t.val))
        t = t.next
        i += 1
    for i in stack:
        rs.append((i[0], 0))
    rs = sorted(rs)
    return [i[1] for i in rs]


a = ListNode(2)
b = ListNode(7)
c = ListNode(4)
d = ListNode(5)
e = ListNode(9)

a.next = b
b.next = c
c.next = d
d.next = e
print(one(a))





# import sys
# sys.setrecursionlimit(1500)
# def go(i,j,s1,s2,s3,dp):
#     if (i,j) in dp:
#         return dp[i,j]

#     if i-1 >= -1:
#         if go(i-1,j,s1,s2,s3,dp) and s1[i] == s3[i+j+1]:
#             dp[i,j] = True
#             return dp[i,j]

#     if j-1 >= -1:
#         if go(i,j-1,s1,s2,s3,dp) and s2[j] == s3[i+j+1]:
#             dp[i,j] = True
#             return dp[i,j]
    
#     dp[i,j] = False
#     return dp[i,j]
# def three(s1, s2, s3):
#     n = len(s1)
#     m = len(s2)
#     k = len(s3)
#     if n+m != k:
#         return False
#     if n+m == 0:
#         return True
#     dp = {}
#     j = 0
#     for i in range(n):
#         if s1[i] == s3[j] and (i == 0 or (i-1,-1) in dp):
#             dp[i,-1] = True
#         j += 1
#     j = 0
#     for i in range(m):
#         if s2[i] == s3[j] and (i == 0 or (i-1,-1) in dp):
#             dp[-1,i] = True
#         j += 1
#     return go(n-1,m-1,s1,s2,s3,dp)

# s1 = "aabcc"
# s2 = "dbbca"
# s3 = "aadbbcbcac"

# s1 = 'a'*1000
# s2 = 'b'*1000
# s3 = 'ab'*1000
# print(three(s1,s2,s3))






