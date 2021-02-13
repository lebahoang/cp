import sys
import heapq

class Box():
  def __init__(self, h=None, c=None):
    if h is not None and c is not None:
      self.h = h
      self.c = c
    else: 
      self.h = []
      self.c = 0

  def pushNewItem(self, item):
    heapq.heappush(self.h, item)
    self.c += 1
    
  def getSmallestItem(self):
    if len(self.h) == 0:
      return None
    self.c -= 1
    item = heapq.heappop(self.h)
    return item

n,m = map(int, sys.stdin.readline().strip().split())
A = list(map(int, sys.stdin.readline().strip().split()))
C = list(map(int, sys.stdin.readline().strip().split()))
B = [None]*n

boxes = [Box() for _ in range(m)]
for i in range(n):
  js = list(map(int, sys.stdin.readline().strip().split()))
  box = [(js[j], j) for j in range(m)]
  B[i] = sorted(box, reverse=True)


for i in range(n):
  x = min(m, A[i])
  remaining = x
  j = 0
  while j < x and remaining > 0:
    money, index = B[i][j]
    if boxes[index].c >= C[index]:
      if money - (boxes[index].c - C[index] + 1)**2 > 0:
        remaining -= 1
        boxes[index].pushNewItem(money)
      else:
        store = Box(boxes[index].h[:], boxes[index].c)
        y = sum(store.h) - (store.c - C[index])**2
        boxes[index].pushNewItem(money)
        yy = sum(boxes[index].h) - (boxes[index].c - C[index])**2
        #print(i, index, y, yy)
        while len(boxes[index].h) > 0:
          if yy > y: break
          i = boxes[index].c
          smallest = boxes[index].getSmallestItem()
          yy = yy - smallest + 2*i - 1
          
        if yy > y:
          remaining -= 1
        else:
          boxes[index] = store
    else:
      remaining -= 1
      boxes[index].pushNewItem(money)
    j += 1

rs = 0
for i in range(m):
  print(boxes[i].h)
  rs += sum(boxes[i].h)
  if boxes[i].c >= C[i]:
    rs -= (boxes[i].c-C[i])**2
print(rs)