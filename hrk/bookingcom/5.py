import sys

def getCommonTags(city1, city2):
  x = []
  for tag in city1[1].keys():
    if tag in city2[1]:
      x.append(tag)
  return ','.join(sorted(x))

def isHavingCommonTags(commonTags, tags):
  for c in commonTags.split(','):
    if c not in tags: return False
  return True

def cmpFunc(a,b):
  if len(a[1].split(',')) > len(b[1].split(',')): return -1
  if len(a[1].split(',')) < len(b[1].split(',')): return 1
  if '%s:%s' %(a[0], a[1]) < '%s:%s' %(b[0], b[1]): return -1
  if '%s:%s' %(a[0], a[1]) > '%s:%s' %(b[0], b[1]): return 1
  return 0

N = int(sys.stdin.readline())

lines = sys.stdin.readlines()
cities = []
for line in lines:
  city,tags = line.strip().split(':')
  d = {}
  for tag in tags.split(','): d[tag] = 1
  cities.append([city, d])

rs = {}
checked = {}
for i in xrange(len(cities)-1):
  for j in xrange(i+1, len(cities)):
    name1 = cities[i][0]
    name2 = cities[j][0]
    commonTags = getCommonTags(cities[i], cities[j])
    if commonTags not in checked and len(commonTags.split(',')) >= N:
      rs['%s_%s:%s' %(name1, name2, commonTags)] = [name1, name2]
      checked[commonTags] = 1

#print 'hhhhh', len(rs.keys())
for k in rs.keys():
  names, tags = k.split(':')
  for city in cities:
    if names.find(city[0]) == -1 and isHavingCommonTags(tags, city[1]):
      rs[k].append(city[0])

output = []
checked = {}
for k,v in rs.items():
  tags = k.split(':')[1]
  if tags not in checked:
    checked[tags] = 1
    y = ','.join(sorted(v))
    output.append((y, tags))

output = sorted(output, cmp = cmpFunc)
string = ''
for x in output:
  string += '%s:%s\n' %(x[0], x[1])
print string.strip()