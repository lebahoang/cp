import sys
import re


def search(arr, v, left, right):
  if left > right:
    return None

  mid = (left + right)/2
  if v > arr[mid-1] and v < arr[mid]:
    return mid
  if v > arr[mid]:
    return search(arr, v, mid+1, right)
  return search(arr, v, left, mid-1)
string = sys.stdin.readline().strip()
k = int(sys.stdin.readline().strip())

s = []
h = {}
for i,x in enumerate(string):
  if x not in h:
    s.append(x)
    h[x] = [i]
  else:
    h[x].append(i)

s = sorted(s, reverse=True)
ss = []
for x in s:
  if len(h[x]) >= k:
    ss.append(x)
s = ss
#print s
#print h

t = ''

if s:
  last = h[s[0]][-1]
  count = len(h[s[0]])
  for i, x in enumerate(s):
    t += x*count
    if i+1 < len(s):
      if last < h[s[i+1]][0]:
        ind = 0
        last = h[s[i+1]][-1]
      elif last > h[s[i+1]][-1]:
        ind = len(h[s[i+1]])
      else:
        ind = search(h[s[i+1]], last, 0, len(h[s[i+1]]))
        last = h[s[i+1]][-1]

      if ind != None:
        count = len(h[s[i+1]]) - ind
        if count < k:
          count = 0

print t

# a = [1,5]
# print search([2,3,5], 1, 0, len(a)-1)