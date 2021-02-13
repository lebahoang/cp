import sys

def isDAG(n,v):
  vx = {}
  
  for node in v.keys():
    if node not in vx:
      s = [node]
      visited = {}
      while s:
        it = s.pop(-1)
        visited[it] = 1
        vx[it] = 1
        for node in v[it]:
          if node not in visited:
            s.append(node)
          else:
            return False
  return True

def solve(n,v,totalE,incomingE):
  s = [k for k,num in incomingE.items() if num == 0]
  l = []
  while s:
    s = sorted(s, reverse=True)
    it = s.pop(-1)
    l.append(it)
    for node in v[it]:
      totalE -= 1
      incomingE[node] -= 1
      if incomingE[node] == 0:
        s.append(node)

  if totalE > 0:
    return None
  return l


ans = []
while True:
  n = int(sys.stdin.readline().strip())
  v = {}
  incomingE = {}
  totalE = 0
  if n == 0: break
  for i in xrange(n):
    line = sys.stdin.readline().strip().split(' ')
    totalE += len(line) - 1
    incomingE[line[0]] = len(line) - 1
    if line[0] not in v: v[line[0]] = []
    
    for node in line[1:]:
      if node not in v:
        v[node] = [line[0]]
      else:
        v[node].append(line[0])
  l = solve(n,v,totalE,incomingE)
  rs = ''
  if l:
    rs = '\n'.join(l)
  else:
    rs = 'cannot be ordered'
  ans.append(rs)

print '\n\n'.join(ans)


