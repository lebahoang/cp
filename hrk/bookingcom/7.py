import sys
from random import randint

def testData():
  n = 1000
  print n
  for i in xrange(n):
    print '%d %d' %(randint(-100, 100), randint(-100, 100))

def solve():
  n = int(sys.stdin.readline())
  data = []
  for i in xrange(n):
    time, earn = map(int, sys.stdin.readline().strip().split(' '))
    data.append((time, earn))
  d = []
  for i in xrange(n):
    y = []
    c = 0
    for j in xrange(i, n):
      c += data[j][1]
      y.append(c)
    d.append(y)

  print 'ok'
  print len(d[1])
solve()