import sys

def cmpFunc(a,b):
  if a[1] > b[1]:
    return -1
  if a[1] < b[1]:
    return 1
  if a[0] < b[0]:
    return -1
  if a[0] > b[0]:
    return 1
  return 0
mentions = sys.stdin.readline().strip().lower().split(' ')
d = {}
for mention in mentions:
  d[mention] = 1
M = int(sys.stdin.readline())
hotels = {}
for _ in xrange(M):
  id = int(sys.stdin.readline())
  score = 0
  reviews = sys.stdin.readline().strip().replace(',', '').replace('.', '').lower().split(' ')
  for word in reviews:
    if word in d:
      score += 1
  if id in hotels:
    hotels[id][1] += score
  else:
    hotels[id] = [id, score]

hotels = sorted(hotels.values(), cmp = cmpFunc)
string = [str(hotel[0]) for hotel in hotels]
print ' '.join(string)