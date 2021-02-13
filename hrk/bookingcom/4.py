import sys

def cmpFunc(a, b):
  if len(a[2].keys()) > len(b[2].keys()): return -1
  if len(a[2].keys()) < len(b[2].keys()): return 1
  if a[1] < b[1]: return -1
  if a[1] > b[1]: return 1
  if a[0] < b[0]: return -1
  if a[0] > b[0]: return 1
  return 0

hotels = []
N = int(sys.stdin.readline())
for _ in xrange(N):
  line = sys.stdin.readline().strip().split(' ')
  d = {}
  for f in line[2:]:
    d[f] = 1
  hotel = (int(line[0]), int(line[1]), d)
  hotels.append(hotel)
M = int(sys.stdin.readline())
for _ in xrange(M):
  line = sys.stdin.readline().strip().split(' ')
  money = int(line[0])
  reqs = line[1:]
  ok = []
  for hotel in hotels:
    f = 0
    for req in reqs:
      if req not in hotel[2] or money < hotel[1]:
        f = 1
    if f == 0: ok.append(hotel)

  if ok:
    ok = sorted(ok, cmp = cmpFunc)
    string = [str(x[0]) for x in ok]
    print ' '.join(string)
  else:
    print ''
