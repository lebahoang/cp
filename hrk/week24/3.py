import sys

def convertCharToInt(char):
  if char == 'A':
    return 0
  elif char == 'B':
    return 1
  elif char == 'C':
    return 2
  return 3

def getNewPositionsForKnight(row, col):
  piece = 'N'
  positions = []
  if row - 1 >= 0 and col + 2 <= 3:
    positions.append((piece, row - 1, col + 2))
  if row + 1  <= 3 and col + 2 <= 3:
    positions.append((piece, row + 1, col + 2))
  if row - 1 >= 0 and col - 2 >= 0:
    positions.append((piece, row - 1, col - 2))
  if row + 1 <= 3 and col - 2 >= 0:
    positions.append((piece, row + 1, col - 2))
  if row - 2 >= 0 and col + 1 <= 3:
    positions.append((piece, row - 2, col + 1))
  if row + 2 <= 3 and col + 1 <= 3:
    positions.append((piece, row + 2, col + 1))
  if row - 2 >= 0 and col - 1 >= 0:
    positions.append((piece, row - 2, col - 1))
  if row + 2 <= 3 and col - 1 >= 0:
    positions.append((piece, row + 2, col - 1))
  return positions
def getNewPositionForBishop(row, col):
  piece = 'B'
  positions = []
  x = col
  y = col
  for i in xrange(row-1, -1, -1):
    x -= 1
    y += 1
    if x >= 0:
      positions.append((piece, i, x))
    if y <= 3:
      positions.append((piece, i, y))

  x = col
  y = col
  for i in xrange(row+1, 4):
    x -= 1
    y += 1
    if x >= 0:
      positions.append((piece, i, x))
    if y <= 3:
      positions.append((piece, i, y))
  return positions
def getNewPositionForRook(row, col):
  piece = 'R'
  positions = []
  for i in xrange(row+1, 4):
    positions.append((piece, i, col))
  for j in xrange(row-1, -1, -1):
    positions.append((piece, row, j))
  return positions
def getNewPositionForQueen(row, col):
  piece = 'Q'
  positions = getNewPositionForRook(row, col)
  positions.extend(getNewPositionForBishop(row, col))
  rs = []
  for p in positions:
    rs.append((piece, p[1], p[2]))
  return rs
def getNewPositions(piece, row, col):
  positions = []
  if piece == 'N':
    positions = getNewPositionsForKnight(row, col)
  elif piece == 'B':
    positions = getNewPositionForBishop(row, col)    
  elif piece == 'R':
    positions = getNewPositionForRook(row, col)
  else:
    positions = getNewPositionForQueen(row, col)
  return positions

def copyDict(source):
  rs = {}
  for k,v in source.items():
    rs[k] = v
  return rs
def eat(position, bs):
  for k in bs.keys():
    if position[1] == k[1] and position[2] == k[2]:
      return k
  return None
def isWin(ws, bs):
  for k in ws.keys():
    piece,row,col = k
    positions = getNewPositions(piece, row, col)
    for p in positions:
      if ('Q', p[1], p[2]) in bs: return True
  return False
def solve(ws,bs,m,isBTurn):
  if (not isBTurn and isWin(ws, bs)):
    return True
  if m == 0:
    # print ws, bs, isBTurn
    return False
  for k in ws.keys():
    piece,row,col = k
    newPositions = getNewPositions(piece, row, col)
    newWs = copyDict(ws)
    newBs = copyDict(bs)
    del newWs[k]
    for position in newPositions:
      eatenBPiece = eat(position, bs)
      if eatenBPiece:
        del newBs[eatenBPiece]
      newWs[position] = 1
      if not isBTurn:
        solve(newBs, newWs, m, True)
      else:
        t = solve(newBs, newWs, m-1, False)
        if t: return t
      del newWs[position]
      if eatenBPiece:
        newBs[eatenBPiece] = 1
  return False



g = int(sys.stdin.readline())
for _ in xrange(g):
  ws = {}
  bs = {}
  w,b,m = map(int, sys.stdin.readline().strip().split(' '))
  for _ in xrange(w):
    piece,col,row = map(str, sys.stdin.readline().strip().split(' '))
    row = int(row) - 1
    col = convertCharToInt(col)
    ws[piece,row,col] = 1
  for _ in xrange(b):
    piece,col,row = map(str, sys.stdin.readline().strip().split(' '))
    row = int(row) - 1
    col = convertCharToInt(col)
    bs[piece,row,col] = 1
  # for kk in xrange(200):
  rs = solve(ws,bs,m,False)
  if rs: print 'YES'
  else: print 'NO'

