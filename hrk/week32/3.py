import sys

def getInd(point, n):
  x = -1
  if point < 0:
    x = abs(point)
    x = int(point + n*((x-x%n)/n + 1))
  else:
    x = point
  if x >= n:
    return x%n
  return x

n,s,t = map(int, sys.stdin.readline().strip().split())
R0,g,seed,p = map(int, sys.stdin.readline().strip().split())

if s == t:
  print(0)
else:
  R = [0]*n
  distance = [None]*n
  distance[s] = 0
  R[0] = R0
  for i in range(1,n):
    R[i] = (R[i-1]*g+seed)%p

  negative = s
  positive = s

  q = [(s,0)]
  qInd = 0
  while qInd < len(q):
    point, dist = q[qInd]
    ind = getInd(point,n)
    #print(point, ind, R[ind])
    if R[ind] == 0:
      qInd += 1
      continue
    if R[ind] >= int(n/2)-1:
      distance[t] = dist + 1
      break


    if negative > point - R[ind]:
      for k in range(1, negative-(point - R[ind])+1):
        tt = getInd(negative-k, n)
        if distance[tt] is None:
          q.append((negative-k, dist+1))
          distance[tt] = dist+1
      negative = point - R[ind]
    #print('xxx')
    if distance[t] is not None:
      break
    if positive < point + R[ind]:
      for k in range(1, (point + R[ind] - positive)+1):
        tt = getInd(positive+k, n)
        if distance[tt] is None:
          q.append((positive+k, dist+1))
          distance[tt] = dist+1
      positive = point + R[ind]
    if distance[t] is not None:
      break
    qInd += 1

  if distance[t] is not None: print(distance[t])
  else: print(-1)