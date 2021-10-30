import sys

def countPalindromicString(string):
  n = len(string)
  d = [[-1 for j in xrange(n)] for i in xrange(n)]
  for i in xrange(n):
    d[i][i] = 1
    if i+1 < n:
      if string[i] == string[i+1]:
        d[i][i+1] = 3
      else:
        d[i][i+1] = 2

  for j in xrange(2, n):
    for i in xrange(n):
      if i + 1 < n and i + j < n:
        if string[i] == string[i+j]:
          d[i][i+j] = 3
          if d[i+1][i+j-1] > 0:
            d[i][i+j] += 2*d[i+1][i+j-1] 
        else:
          d[i][i+j] = -1
          if d[i][i+j-1] > 0:
            d[i][i+j] += d[i][i+j-1]
          if d[i+1][i+j] > 0:
            d[i][i+j] += d[i+1][i+j]

  print d
  print d[0][n-1]
  return d[0][n-1]

def solve():
  string = 'aaa'
  countPalindromicString(string)

solve()

# q = int(sys.stdin.readline())
# for _ in xrange(q):
#   n = int(sys.stdin.readline())
#   ns = []
#   for _ in xrange(n):
#     ns.append(sys.stdin.readline().strip())
#   rs = countPalindromicStringInGroups(n, ns)
#   print rs