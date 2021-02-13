h#import sys
# a = map(int, sys.stdin.readline().strip().split(' '))
# b = []
# for i in xrange(len(a)):
#   if i == 0:
#     b.append(str(a[i]))
#   else:
#     x = a[i]-a[i-1]
#     if x < -127 or x > 127:
#       b.append(str(-128))
#     b.append(str(x))
# print ' '.join(b)


# a = int(sys.stdin.readline())
# M = int(sys.stdin.readline())
# arr = []
# d = {}
# for _ in xrange(M):
#   x = int(sys.stdin.readline())
#   arr.append(x)
#   if x in d:
#     d[x] += 1
#   else:
#     d[x] = 1
# f = 0
# for num in arr:
#   if a-num in d:
#     if a-num != num:
#       f = 1
#     else:
#       if d[a-num] > 1:
#         f = 1 

# print f

# import sys
# s = 0
# r = 0
# o = 0
# lines = sys.stdin.readlines()
# for line in lines:
#   line = line.strip().split(' ')
#   if len(line) == 4:
#     A,B,C,D = map(int, line)
#     if A <= 0 or B <= 0 or C <= 0 or D <= 0:
#       o += 1
#     else:
#       if A == B and A == C and C == D:
#         s += 1
#       elif A == C and D == B and A != B:
#         r += 1
#       else:
#         o += 1
# print s,r,o


import sys

n,m = map(int, sys.stdin.readline().strip().split(' '))
arr = map(int, sys.stdin.readline().strip().split(' '))
d = [[0 for j in xrange(n+1)] for i in xrange(m)]
s = [[0 for j in xrange(n+1)] for i in xrange(m)]
for i in xrange(m):
  for j in xrange(n+1):
    for k in xrange(j):
      if (j-k)%arr[i] == 0:
        if k == 0: 
          d[i][j] += 1
          s[i][j] += 1
        d[i][j] += s[i-1][k]

    s[i][j] = s[i-1][j] + d[i][j]

rs = 0
for i in xrange(m):
  rs += d[i][n]

#print n,m,arr
#print d
print rs
