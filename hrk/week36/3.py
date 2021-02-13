import sys

def canPawnMoveToEight(chess, i, j):
    if chess[i][j] == "#":
        return True
    return False
def findPawnAndPositionAtEight(chess):
    eight = chess[0]
    seven = chess[1]

    for j, ch in enumerate(seven):
        if ch == 'P' and canPawnMoveToEight(chess, 0, j):
            return 1,j,0,j
    return None, None, None, None

def findKing(chess):
    for i in range(len(chess)):
        for j in range(len(chess[0])):
            if chess[i][j] == 'k':
                return i,j
    return None, None

def findDiagonalPosition(kingI, kingJ, i, j):
    if i > kingI:
        if j > kingJ:
            return -1, -1
        else:
            return -1, 1
    else:
        if j > kingJ:
            return 1, -1
        else:
            return 1, 1 

def queenCanCheckmate(chess, kingI, kingJ, i, j):
    if abs(kingI - i) != abs(kingJ - j) and abs(kingI - i) != 0 and abs(kingJ - j) != 0:
        return False

    if abs(kingI - i) == 0:
        start = min(kingJ, j)
        stop = max(kingJ, j)
        for k in range(start + 1, stop):
            if chess[i][k] != '#':
                return False
        return True
    if abs(kingJ - j) == 0:
        start = min(kingI, i)
        stop = max(kingI, i)
        for k in range(start + 1, stop):
            if chess[k][j] != '#':
                return False
        return True


    m,n = findDiagonalPosition(kingI, kingJ, i, j)
    start = i+m
    stop = j+n
    while start != kingI and stop != kingJ:
        if chess[start][stop] != '#':
            return False
        start += m
        stop  += n
    return True


def knightCanCheckmate(chess, kingI, kingJ, i, j):
    if abs(kingI - i) == 2 and abs(kingJ - j) == 1:
        return True
    if abs(kingJ - j) == 2 and abs(kingI - i) == 1:
        return True
    return False  


def rookCanCheckmate(chess, kingI, kingJ, i, j):
    if abs(kingI - i) != 0 and abs(kingJ - j) != 0:
        return False

    if abs(kingI - i) == 0:
        start = min(kingJ, j)
        stop = max(kingJ, j)
        for k in range(start + 1, stop):
            if chess[i][k] != '#':
                return False
        return True
    
    start = min(kingI, i)
    stop = max(kingI, i)
    for k in range(start + 1, stop):
        if chess[k][j] != '#':
            return False
    return True

def bishopCanCheckmate(chess, kingI, kingJ, i, j):
    if abs(kingI - i) != abs(kingJ - j):
        return False

    m,n = findDiagonalPosition(kingI, kingJ, i, j)
    start = i+m
    stop = j+n
    while start != kingI and stop != kingJ:
        if chess[start][stop] != '#':
            return False
        start += m
        stop  += n
    return True

def isCheckmate(chess, kingI, kingJ):
    n = len(chess)
    m = len(chess[0])
    for i in range(n):
        for j in range(m):
            if chess[i][j] == 'Q':
                if queenCanCheckmate(chess, kingI, kingJ, i, j):
                    return True
            if chess[i][j] == 'N':
                if knightCanCheckmate(chess, kingI, kingJ, i, j):
                    return True
            if chess[i][j] == 'R':
                if rookCanCheckmate(chess, kingI, kingJ, i, j):
                    return True
            if chess[i][j] == 'B':
                if bishopCanCheckmate(chess, kingI, kingJ, i, j):
                    return True
    return False
def solve(chess):
    oldI, oldJ, i, j = findPawnAndPositionAtEight(chess)
    if i == None:
        return -1
    kingI, kingJ = findKing(chess)
    if kingI == None:
        return -1

    c = 0
    chess[oldI][oldJ] = '#'
    for m in ['Q', 'N', 'R', 'B']:
        chess[i][j] = m
        if isCheckmate(chess, kingI, kingJ):
            c += 1
    return c


t = int(sys.stdin.readline())
for _ in range(t):
    chess = []
    for _ in range(8):
        line = list(sys.stdin.readline().strip())
        chess.append(line)

    print(solve(chess))