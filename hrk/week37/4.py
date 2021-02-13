import sys
import math


# def getN(lenA):
#   N = int(math.ceil(lenA**0.5))
#   return N**2
# def buildSegTree(arr):
#   N = getN(len(arr))
#   tree = [0]*(2*N+1)
#   lazy = [0]*(2*N+1)
#   return tree,lazy
# def updateSegTree(tree, value, ind, start, end, l, r, lazy):
#   if lazy[ind] != 0:
#     tree[ind] += (end - start + 1) * lazy[ind]
#     if start != end:
#       lazy[2*ind+1] += lazy[ind]
#       lazy[2*ind+2] += lazy[ind]
#     lazy[ind] = 0
#   if start > r or end < l:
#     return
#   if start >= l and end <= r:
#     tree[ind] += (end - start + 1) * value
#     if start != end:
#       lazy[2*ind+1] += value
#       lazy[2*ind+2] += value
#     return
#   mid = (start+end)//2
#   updateSegTree(tree, value, 2*ind+1, start, mid, l, r, lazy)
#   updateSegTree(tree, value, 2*ind+2, mid+1, end, l, r, lazy)

#   tree[ind] = tree[2*ind+1] + tree[2*ind+2]
#   return

# def querySum(tree, ind, start, end, l, r, lazy):
#   if lazy[ind] != 0:
#     tree[ind] += (end - start + 1) * lazy[ind]
#     if start != end:
#       lazy[2*ind+1] += lazy[ind]
#       lazy[2*ind+2] += lazy[ind]
#     lazy[ind] = 0

#   if start > r or end < l:
#     return None

#   if start >= l and end <= r:
#     return tree[ind]

#   mid = (start + end)//2
#   a = querySum(tree, 2*ind+1, start, mid, l, r, lazy)
#   b = querySum(tree, 2*ind+2, mid+1, end, l, r, lazy)
#   if a == None: return b
#   elif b == None: return a
#   return a+b



# arr = [0]*(10**6)
# tree, lazy = buildSegTree(arr)
# updateSegTree(tree, 1,0,0,len(arr)-1,0,2,lazy)
# updateSegTree(tree, 1,0,0,len(arr)-1,1,3,lazy)
# updateSegTree(tree, 1,0,0,len(arr)-1,9,10,lazy)
# updateSegTree(tree, 1,0,0,len(arr)-1,4,7,lazy)
# updateSegTree(tree, 1,0,0,len(arr)-1,4,10,lazy)
#print tree
#updateSegTree(tree, 100,0,0,len(arr)-1,3,4,lazy)
#print tree
# print(querySum(tree, 0, 0, len(arr)-1, 0, 1000, lazy))
# print queryMax(tree, 0, 0, len(arr)-1, 3, 3, lazy)
# print queryMax(tree, 0, 0, len(arr)-1, 0, 3, lazy)
# print queryMax(tree, 0, 0, len(arr)-1, 0, 2, lazy)
# print queryMax(tree, 0, 0, len(arr)-1, 0, 1, lazy)


import sys
import math

def get(op, k, b, qs):
  bottom = math.ceil(-b/k)
  top = math.floor((10**5-b)/k)
  for x in range(bottom, top+1):
    if op == '+':
      qs[k*x+b] += 1
    else:
      qs[k*x+b] -= 1

  
qs = [0 for i in range(10**5+1)]
n = int(sys.stdin.readline())
for _ in range(n):
  cmd = sys.stdin.readline().strip().split(' ')
  if len(cmd) == 3:
    op = cmd[0]
    k = int(cmd[1])
    b = int(cmd[2])
    get(op, k,b,qs)
  else:
    q = int(cmd[1])
    print(qs[q])