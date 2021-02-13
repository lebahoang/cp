import sys

def calculatePower2AB(a,b):
  return ((a[0]-b[0])**2 + (a[1]-b[1])**2)

def isInCircle(cP, p, r):
  if calculatePower2AB(cP, p) <= r*r:
    return True
  return False

def calculateVectorAB(a,b):
  return [b[0]-a[0], b[1]-a[1]]
def calculateDot2Vectors(vA, vB):
  return vA[0]*vB[0] + vA[1]*vB[1]

def isInSquare(aP, bP, dP, p):
  if aP == None:
    return False
  ab = calculateVectorAB(aP, bP)
  ad = calculateVectorAB(aP, dP)
  ap = calculateVectorAB(aP, p)

  abap = calculateDot2Vectors(ab, ap)
  abab = calculateDot2Vectors(ab, ab)
  adap = calculateDot2Vectors(ad, ap)
  adad = calculateDot2Vectors(ad, ad)

  if abap >= 0 and abap <= abab and adap >= 0 and adap <= adad:
    return True
  return False

def findVerticeInSquare(aP, bP, w, h):
  k = calculatePower2AB(aP, bP)/2
  if k < 1:
    return None
  for i in xrange(w):
    for j in xrange(h):
      mP = [i,j]
      x = calculatePower2AB(aP, mP)
      y = calculatePower2AB(bP, mP)

      if x == k and y == k:
        return mP
  return None

def findVerticeInSquare2(aP, bP, w, h):
  x = [float(aP[0]+aP[1]+bP[0]-bP[1])/2.0, float(bP[0]+bP[1]+aP[1]-aP[0])/2.0]
  y = [float(bP[0]+bP[1]+aP[0]-aP[1])/2.0, float(aP[0]+aP[1]+bP[1]-bP[0])/2.0]

  # if x[0] >= 0 and x[0] <= w-1 and x[1] >= 0 and x[1] <= h-1:
  #   return x
  # if y[0] >= 0 and y[0] <= w-1 and y[1] >= 0 and y[1] <= h-1:
  #   return y
  return x,y


w,h = map(int,sys.stdin.readline().strip().split())
xc, yc, r = map(float,sys.stdin.readline().strip().split())
x1,y1,x3,y3 = map(float,sys.stdin.readline().strip().split())
vP1, vP2 = findVerticeInSquare2([x1,y1], [x3,y3], w, h)

rs = []
for i in xrange(h):
  row = ''
  for j in xrange(w):
    mP = [j,i]
    if isInCircle([xc, yc], mP, r) or isInSquare(vP1, [x1, y1], [x3, y3], mP) or isInSquare(vP2, [x1, y1], [x3, y3], mP):
      row += '#'
    else:
      row += '.'
  rs.append(row)

print '\n'.join(rs)
