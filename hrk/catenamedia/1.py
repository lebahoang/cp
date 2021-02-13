import sys

def mergeStrings(a, b):
  i = 0
  j = 0
  rs = ''
  while i < len(a) and j < len(b):
    rs += a[i] + b[j]
    i += 1
    j += 1

  if i < len(a):
    rs += a[i:]
  if j < len(b):
    rs += b[j:]
  return rs

def verifyItems(origItems, origPrices, items, prices):
  h = {}
  for i in xrange(len(origItems)):
    h[origItems[i]] = origPrices[i]

  rs = 0
  for i in xrange(len(items)):
    if items[i] in h and prices[i] != h[items[i]]:
      rs += 1
  return rs

def getNode(node, tag):
  for child in node:
    if child.tag == tag:
      return child
  return None

def solve():
  import sys
  import xml.etree.ElementTree as ET
  N,Q = map(int,sys.stdin.readline().strip().split())

  string = ''
  for _ in xrange(N):
    string += sys.stdin.readline().strip()
  try:
    root = ET.fromstring(string)
    for _ in xrange(Q):
      q = sys.stdin.readline().strip()
      attQ = q.split('~')
      rs = 'Not Found!'
      if len(attQ) > 1:
        children = attQ[0].split('.')
        attQ = attQ[1]
        if len(children) == 1:
          for k,v in root.attrib.items():
            if k == attQ:
              rs = v
        else:
          if root.tag == children[0]:
            t = root
            node = None
            for tag in children[1:]:
              node = getNode(t, tag)
              if node is None:
                break
              else:
                t = node
            if node is not None:
              for k,v in node.attrib.items():
                if k == attQ:
                  rs = v

        print rs
  except:
    print 'Not Found!'

solve()

#print mergeStrings('abc', 'ed')