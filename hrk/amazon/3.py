import sys

def getKthFromTailOfLinkList(l, k):
  s = []
  c = 0
  for i in l:
    if c < k:
      s.append(i)
      c += 1
    else:
      s.pop(0)
      s.append(i)

  return s[0]
class Node():
  def __init__(self, value, next, otherNode):
    self.value = value
    self.next = next
    self.otherNode = otherNode

def buildLinkedListfromArray(arr):
  root = None
  nodes = []
  i = 0
  prevNode = None
  while i < len(arr):
    node = Node(arr[i][0], None, None)
    nodes.append(node)
    if prevNode:
      prevNode.next = node
    else:
      root = node
    prevNode = node
    i += 1

  i = 0
  t = root
  while i < len(arr):
    if arr[i][1]:
      t.otherNode = nodes[arr[i][1]-1]
    t = t.next
    i += 1
  return root


def cloneLinkList(root):
  clonedRoot = None
  prevNode = None
  t = root
  while t is not None:
    node = Node(t.value+10**6, None, t)
    if prevNode:
      prevNode.next = node
    else:
      clonedRoot = node
    prevNode = node
    k = t.next
    t.next = node
    t = k

  # clone otherNode
  print 'dadas'
  t = clonedRoot
  while t is not None:
    t.otherNode = t.otherNode.otherNode.next
    t = t.next
  return clonedRoot

def reverseSegmentInLinkedList(node, k):
  rs = None
  t = node
  prevEnd = node
  curEnd = None
  curStart = None
  c = 1
  prev = None
  while t:
    temp = t.next
    if prev:
      t.next = prev
    prev = t
    if c % k == 1:
      curEnd = t 
    if c % k == 0 or temp == None:
      curStart = t
      if c / k > 1 or temp == None:
        prevEnd.next = curStart
        prevEnd = curEnd
      else:
        rs = t
    t = temp
    c += 1
  curEnd.next = None
  return rs


def printLinkList(node):
  s = []
  t = node
  while t != None:
    #print t.value
    s.append(str(t.value)+'|'+str(t.otherNode.value))
    t = t.next
  return ' '.join(s)

def reverseKElementsLinkList(l, k):
  s = []
  c = 0
  rs = []
  for i in l:
    s.append(i)
    c += 1
    if c%k == 0 or c == len(l):
      for j in xrange(k):
        if s:
          t = s.pop()
          rs.append(t)

  return rs

def findNumberInSortedMatrix(matrix, number):
  def find(matrix, number, i, j, rs, visited):
    if (i,j) in visited:
      return rs
    if number == matrix[i][j]:
      rs.append((i,j))
      visited[i,j] = 1

    if number <= matrix[i][j] and i-1 >=0 and number <= matrix[i-1][j]:
      rs = find(matrix, number, i-1, j, rs, visited)
      visited[i-1,j] = 1
    if number <= matrix[i][j] and j-1 >=0 and number <= matrix[i][j-1]:
      rs = find(matrix, number, i, j-1, rs, visited)
      visited[i,j-1] = 1
    return rs

  n = len(matrix) - 1
  m = len(matrix[0]) - 1
  rs = []
  visited = {}
  find(matrix, number, n, m, rs, visited)
  return rs

def findMinimumCutPalindrome(string):
  def isPalindrome(x,start,end):
    i = start
    j = end
    while i < j:
      if x[i] != x[j]:
        return False
      i += 1
      j -= 1
    return True
  def find(string, i, j, s):
    if (i,j) in s:
      return s[i,j]
    if isPalindrome(string,i,j):
      s[i,j] = 0
      return 0
    minV = -1
    for k in xrange(i,j):
      x = find(string, i, k, s)
      y = find(string, k+1, j, s)
      if minV == -1 or minV > x+y+1:
        minV = x+y+1

    s[i,j] = minV
    return minV

  i = 0
  j = len(string)-1
  rs = find(string, i, j, {})
  return rs

def fourSum(nums, target):
  """
  :type nums: List[int]
  :type target: int
  :rtype: List[List[int]]
  """
  a = []
  d = {}
  dd = {}
  for i in xrange(len(nums)-1):
    for j in xrange(i+1, len(nums)):
        a.append((i,j,nums[i]+nums[j]))
        t = nums[i]+nums[j]
        if t not in d:
            d[t] = [(i,j)]
        else:
            d[t].append((i,j))
  rs = []
  for k in xrange(len(a)):
    i,j,v = a[k]
    if target-v in d:
      for v in d[target-v]:
        if i != v[0] and i != v[1] and j != v[0] and j != v[1]:
          k = sorted([nums[i],nums[j],nums[v[0]],nums[v[1]]])
          string = ','.join([str(x) for x in k])
          if string not in dd:
            dd[string] = 1
            rs.append([nums[i],nums[j],nums[v[0]],nums[v[1]]])
           
  return rs

def findMaxSumSubArray(arr):
  maxV = [-1]*len(arr)
  maxV[0] = arr[0]
  c = arr[0]
  for i in xrange(1, len(arr)):
    if c+arr[i] > 0:
      c += arr[i]
    else:
      c = 0
    if c > 0:
      maxV[i] = max(maxV[i-1], arr[i], c)
    else:
      maxV[i] = max(maxV[i-1], arr[i])
  return maxV[len(arr)-1]
    


#print getKthFromTailOfLinkList([1,2,3,4,5,6], 6)
#x = cloneLinkList([1,2,3,4,5,6], [2,2,2,2,2,2])
#print printLinkList(x)

#print reverseKElementsLinkList([1,2,3,4,5,6,7,8,9],3)
# print findNumberInSortedMatrix([
#                           [1,2,3,4,7,888],
#                           [2,4,6,7,8,999],
#                           [5,8,9,10,11,1567],
#                           [6,9,11,12,14,1790]
#                          ], 9)
# print findNumberInSortedMatrix([
#                           [1,1,1],
#                           [1,1,1]
#                          ], 1)

#print findMinimumCutPalindrome('ababbbabbababa')
#print findMinimumCutPalindrome('abccddbak')
#print findMinimumCutPalindrome('abcdedcbak')

# root = buildLinkedListfromArray([(1,2), (4,1), (5,4), (4,2)])
# print printLinkList(root)
# clonedRoot = cloneLinkList(root)
# print printLinkList(clonedRoot)
# print fourSum([1,0,-1,0,-2,2], 0)

# root = buildLinkedListfromArray([(1,2), (2,1), (3,1), (4,1), (5,1), (6,1), (7,1), (8,1)])
# rs = reverseSegmentInLinkedList(root, 3)
# print printLinkList(rs)
print findMaxSumSubArray([-1,-2,8,-3,9])