import sys
def maxIncrementalSubList(l):
  def discovery(start, l):
    j = start
    s = l[start]
    while j+1 < len(l):
      if l[j+1] - l[j] == 1:
        s += l[j+1]
        j += 1
      else:
        break
    return j+1,s

  max = -1
  i = 0
  while i < len(l):
    j,s = discovery(i, l)
    if max == -1 or max < s:
      max = s
    if i == j:
      i += 1
    else:
      i = j
  return max

def maxIncrementalSubList_randomly(l):
  def discovery(start, l):
    j = start
    s = l[start][0]
    minInd = l[start][1]
    maxInd = l[start][1]
    c = 1
    while j+1 < len(l):
      if l[j+1][0] - l[j][0] == 1:
        s += l[j+1][0]
        if minInd == -1 or minInd > l[j+1][1]:
          minInd = l[j+1][1]
        if maxInd == -1 or maxInd < l[j+1][1]:
          maxInd = l[j+1][1]
        j += 1
        c += 1
      else:
        break

    if maxInd - minInd + 1 == c:
      return j+1,s
    return None, None

  t = [(l[i], i) for i in xrange(len(l))]
  l = sorted(t)
  print l
  max = -1
  i = 0
  while i < len(l):
    j,s = discovery(i, l)
    if j == None: 
      i += 1
    else:
      if max == -1 or max < s:
        max = s
      if i == j:
        i += 1
      else:
        i = j
  return max


def swapInplace(a,k):
  a = list(a)
  for i in xrange(k):
    for j in xrange(len(a)-1):
      t = a[j]
      a[j] = a[j+1]
      a[j+1] = t
  print ''.join(a)

def preorderTraversal(tree, i, rs, sum):
  rs.append(tree[i])
  if i*2+1 < len(tree) and tree[i*2+1] != None:
    rs = preorderTraversal(tree, i*2+1, rs)
  if i*2+2 < len(tree) and tree[i*2+2] != None:
    rs = preorderTraversal(tree, i*2+2, rs)
  return rs


def inorderTraversal(tree, i, rs):
  if i*2+1 < len(tree) and tree[i*2+1] != None:
    rs = inorderTraversal(tree, i*2+1, rs)
  rs.append(tree[i])
  if i*2+2 < len(tree) and tree[i*2+2] != None:
    rs = inorderTraversal(tree, i*2+2, rs)
  return rs


def postorderTraversal(tree, i, rs):
  if i*2+1 < len(tree) and tree[i*2+1] != None:
    rs = postorderTraversal(tree, i*2+1, rs)
  if i*2+2 < len(tree) and tree[i*2+2] != None:
    rs = postorderTraversal(tree, i*2+2, rs)
  rs.append(tree[i])
  return rs


def findPaths(tree, i, rs, sum, target, path):
  if sum + tree[i] == target:
    t = path[:]
    t.append(tree[i])
    rs.append(t)
  if i*2+1 < len(tree) and tree[i*2+1] != None:
    t = path[:]
    t.append(tree[i])
    rs = findPaths(tree, i*2+1, rs, sum + tree[i], target, t)
  if i*2+2 < len(tree) and tree[i*2+2] != None:
    t = path[:]
    t.append(tree[i])
    rs = findPaths(tree, i*2+2, rs, sum + tree[i], target, t)
  return rs



def findNodesFromKDistance(tree, root, k, target):
  nodes = {}
  its = [root]
  while its:
    i = its.pop(0)
    if i*2+1 < len(tree) and tree[i*2+1] != None:
      x = tree[i]
      y = tree[i*2+1]
      its.append(i*2+1)
      if x not in nodes:
        nodes[x] = [y]
      else:
        nodes[x].append(y)
      if y not in nodes:
        nodes[y] = [x]
      else:
        nodes[y].append(x)
    if i*2+2 < len(tree) and tree[i*2+2] != None:
      x = tree[i]
      y = tree[i*2+2]
      its.append(i*2+2)
      if x not in nodes:
        nodes[x] = [y]
      else:
        nodes[x].append(y)
      if y not in nodes:
        nodes[y] = [x]
      else:
        nodes[y].append(x)

  print nodes
  rs = []
  v = {}
  dis = {target: 0}
  its = [target]
  while its:
    i = its.pop(0)
    v[i] = 1
    for j in nodes[i]:
      if j not in v:
        its.append(j)
        dis[j] = dis[i] + 1
        if dis[j] == k:
          rs.append(j)
  return rs


def matchSimpleRegex(regex, string):
  j = 0
  for re in regex:
    if re != '*':
      f = 0
      while j < len(string):
        if string[j] == re:
          j += 1
          f = 1
          break
        j += 1
      if f == 0:
        return False
  return True

def findMaxConsecutiveOnes(arr, k):
  def go(start, arr, k, alreadyCountValue):
    i = start
    maxV = alreadyCountValue
    while i < len(arr):
      if arr[i] == 0:
        if k > 0:
          k -= 1
        else:
          break
      maxV += 1
      i += 1
    print 'kkk',maxV,start,i
    return maxV, i

  lastV = 0
  lastStart = 0
  f = 0
  maxF = -1
  i = 0
  while i < len(arr):
    if i-1 >= 0:
      if arr[i-1] == 0:
        k = 1
        l = lastStart
        lastV -= 1
      else:
        k = 0
        l = lastStart
        lastV -= 1
    else:
      l = i
    
    maxV, j = go(l, arr, k, lastV)
    lastV = maxV
    lastStart = j

    if maxF == -1 or maxF < maxV:
      print maxV, l
      maxF = maxV
    i += 1
  return maxF


def searchRotatedSortedArray(arr, v):
  def search(arr, v, left, right):
    print left,right
    if left > right:
      return -1
    mid = (left + right)/2
    if arr[mid] == v:
      return mid

    if arr[-1] > arr[0]:
      if arr[mid] < v:
        return search(arr, v, mid+1, right)
      return search(arr, v, left, mid-1)
    else:
      if v == arr[-1]:
        return len(arr)-1

      if arr[mid] < v and v < arr[-1]:
        return search(arr, v, mid+1, right)


      if arr[mid] < v and v > arr[-1]:
        if arr[mid] <= arr[-1]:
          return search(arr, v, left, mid-1)
        return search(arr, v, mid+1, right)


      if arr[mid] > v and v > arr[-1]:
        return search(arr, v, left, mid-1)


      if arr[mid] > v and v < arr[-1]:
        if arr[mid] <= arr[-1]:
          return search(arr, v, left, mid-1)
        return search(arr, v, mid+1, right)


  return search(arr, v, 0, len(arr)-1)
        

def generateDigitsString(string, arr):
  if arr[6]+1 < len(string):
    arr[6] += 1
    return '%s%s%s%s%s%s%s' %(string[arr[0]], string[arr[1]], string[arr[2]], string[arr[3]], string[arr[4]], string[arr[5]], string[arr[6]]), arr
  t = 6
  while arr[t]+1 >= len(string):
    arr[t] = 0
    t -= 1
  arr[t] += 1
  str = ''
  for i in xrange(len(string)):
    str += string[arr[i]]

  return str, arr

def go(string, startInd, h):
  j = startInd
  while j < len(string):
    if string[j] not in h:
      return j,h
    else:
      if h[string[j]] - 1 < 0:
        return j,h
      else:
        h[string[j]] -= 1
    j += 1
  return j,h
def findSubStringContainsString(string, pattern):
  rs = []
  h = {}
  for i in pattern:
    if i not in h:
      h[i] = 1
    else:
      h[i] += 1

  i = 0
  j = 0
  while i < len(string):
    #print j,h
    j,h = go(string,j,h)
    #print 'dsda', h
    f = 0
    for v in  h.values():
      if v > 0:
        f = 1
        break
    if f == 0:
      rs.append(i)

    if string[i] in h: h[string[i]] += 1
    i += 1
    if i > j:
      j = i

  return rs

# t = [1,2,3]
# l = []
# for i in xrange(100000): l.extend(t)

# print maxIncrementalSubList(l)
# print maxIncrementalSubList_randomly([1,2,9,8,7,6,5])
#print maxIncrementalSubList(l)    6,2,1,3,5,4
#swapInplace('abcdefghjk', 7)
#print preorderTraversal([1,2,3,4,5,6,7], 0, [])
#print inorderTraversal([1,2,3,4,5,6,7], 0, [])
#print postorderTraversal([1,2,3,4,5,6,7], 0, [])
#print findPaths([1,2,3,4,5,6,7], 0, [], 0, 4, [])
#print findNodesFromKDistance([20,8,22,4,12,None,None,None,None,10,14], 0, 3, 4)
#print matchSimpleRegex('a', 'bb')
#print findMaxConsecutiveOnes([1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1], 1)
#print findMaxConsecutiveOnes([0,1,0,1,0,1], 2)

# arr = [i for i in xrange(1,1000000)]
# rs = []
# t = []
# for k in xrange(4000, len(arr)):
#   t.append(arr[k])
# rs = t[:]
# rs.extend(arr[:4000])
# #print 'fffff', rs[len(arr)-4000-400-1:len(arr)-4000-1+100]
# #print 'fffff', rs[len(arr)-4000-400-1:],rs[0]
# k = searchRotatedSortedArray(rs, 3999)
# print k, rs[k]
#print searchRotatedSortedArray([8,9,12,1,2,3,4,5],5)
# arr = [1,1,1,1,3,4,5]
# for _ in xrange(100000):
#   rs, arr = generateDigitsString('1234567', arr)
#   print rs

string = 'ffff'
print findSubStringContainsString(string, 'ff')
