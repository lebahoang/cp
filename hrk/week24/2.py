import sys
t = int(sys.stdin.readline())
for _ in xrange(t):
  n = int(sys.stdin.readline())
  b = sys.stdin.readline().strip()
  d = {}
  c = 0
  for i in b:
    if i != '_':
      c += 1
      if i not in d: d[i] = 1
      else: d[i] += 1
  # print c,n,d
  if c == n:
    f = 0
    if c == 1:
      f = 1
    else:
      for i in xrange(n):
        if i == 0 and b[i] != b[i+1]:
          f = 1
          break
        elif i == n-1 and b[i] != b[i-1]:
          f = 1
          break
        elif i > 0 and i < n-1 and b[i-1] != b[i] and b[i] != b[i+1]:
          f = 1
          break
    if f == 0: print 'YES'
    else: print 'NO' 
  else:
    f = 0
    for v in d.values():
      if v == 1:
        print 'NO'
        f = 1
        break
    if f == 0: print 'YES'
