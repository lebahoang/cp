import sys

cs = []
d = []
C, B = map(int, sys.stdin.readline().strip().split(' '))
for _ in xrange(C):
  n = int(sys.stdin.readline())
  y = []
  for _ in xrange(n):
    p,s = sys.stdin.readline().strip().split(' ')
    p = int(p)
    s = float(s)
    y.append((p, s))
  cs.append(y)
  d.append([[-1, -1] for i in xrange(n)])

for i in xrange(len(cs[0])):
  if cs[0][i][0] <= B:
    d[0][i] = [cs[0][i][0], cs[0][i][1]]

for i in xrange(1, C):
  for j in xrange(len(cs[i])):
    maxS = -1.0
    paid = -1
    for k in xrange(len(cs[i-1])):
      if cs[i][j][0] + d[i-1][k][0] <= B:
        if maxS == -1.0 or maxS < d[i-1][k][1]:
          maxS = d[i-1][k][1]
          paid = cs[i][j][0] + d[i-1][k][0]
    if maxS > -1.0:
      d[i][j] = [paid, maxS + cs[i][j][1]]
    else:
      d[i][j] = [-1, -1.0]

maxS = -1.0
for j in xrange(len(d[-1])):
  if d[-1][j][1] > -1:
    if maxS == -1.0 or maxS < d[-1][j][1]:
      maxS = d[-1][j][1]
#print d
if maxS > -1.0:
  print '%.2f' %round(maxS,2)
else:
  print int(maxS)