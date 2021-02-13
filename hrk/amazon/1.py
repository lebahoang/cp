def hasBalancedBrackets(str):
    def isMatch(i,j):
        if (i == ')' and j == '(') \
        or (i == '}' and j == '{') \
        or (i == ']' and j == '[') \
        or (i == '>' and j == '<'):
            return True
        return False


    stack = []
    for i in str:
        if i == '(' or i == '{' or i == '[' or i == '<':
            stack.append(i)
        elif i == ')' or i == '}' or i == ']' or i == '>':
            if len(stack) > 0 and isMatch(i, stack[-1]):
                stack.pop(-1)
            else:
                return 0

    if len(stack) > 0:
        return 0
    return 1

def bstDistance(values, n, node1, node2):
    if not values:
        return -1
    if node1 == node2:
        return 0
    x = y = None
    tree = []
    tree.append([values[0], None, None, None])
    if node1 == tree[0][0]:
        x = 0
    elif node2 == tree[0][0]:
        y = 0
    for i in values[1:]:
        j = 0
        while True:
            if i < tree[j][0]:
                if tree[j][1] == None:
                    tree[j][1] = len(tree)
                    tree.append([i, None, None, j])
                    if node1 == i:
                        x = len(tree)-1
                    elif node2 == i:
                        y = len(tree)-1
                    break
                else:
                    j = tree[j][1]
            else:
                if tree[j][2] == None:
                    tree[j][2] = len(tree)
                    tree.append([i, None, None, j])
                    if node1 == i:
                        x = len(tree)-1
                    elif node2 == i:
                        y = len(tree)-1
                    break
                else:
                    j = tree[j][2]

    if x == None or y == None:
        return -1
    #print tree
    i = x
    a = {i:0}
    c1 = 0
    while tree[i][3] != None:
        i = tree[i][3]
        c1 += 1
        a[i] = c1

    j = y
    c2 = 0
    while j != None:
        if j in a:
            return a[j] + c2
        j = tree[j][3]
        c2 += 1
    return c1 + c2

def findMaxHouse(arr, M):
    def go(arr, i, m):
        c = 0
        for k in xrange(i, len(arr)):
            if c + arr[k] > m:
                return c,k
            c += arr[k]
        return c,-1


    max = -1
    maxInd = -1
    i = 0
    j = 0
    m = M
    computed = 0
    while i < len(arr):
        c,j = go(arr, j, m)
        if max == -1 or max < c+computed:
            max = c+computed
            maxInd = (i,j)
        if j == -1:
            return max
        i += 1
        computed = c+computed-arr[i-1]
        m = M - computed
    return max,arr[maxInd[0]:maxInd[1]]


def findHeightOfTreeAndSubtrees(tree, root):
    def find(tree, node, heights):
        if not tree[node]:
            heights[node] = 0
        else:
            if len(tree[node]) == 2:
                heights[node] = max(find(tree, tree[node][0], heights), find(tree, tree[node][1], heights)) + 1
            else:
                heights[node] = find(tree, tree[node][0], heights) + 1
        return heights[node]


    heights = [-1] * len(tree)
    find(tree, root, heights)
    return heights

def findLongestPathBetweenLeaves(tree, root):
    def find(tree, node, heights):
        dia = -1
        if len(tree[node]) == 2:
            dia = heights[tree[node][0]] + heights[tree[node][1]] + 2
            dia = max(dia, find(tree, tree[node][0], heights), find(tree, tree[node][1], heights))
        elif len(tree[node]) == 1:
            dia = find(tree, tree[node][0], heights)
        else:
            dia = 0
        return dia

    heights = findHeightOfTreeAndSubtrees(tree, root)
    return find(tree, root, heights)

def printMatrixSpirally(matrix, n, m):
    def printValues(startR, endR, startC, endC, matrix):
        s = []
        i = startR
        j = startC
        while j <= endC:
            s.append(matrix[i][j])
            j += 1
        i += 1
        j = endC
        while i <= endR:
            s.append(matrix[i][j])
            i += 1
        print s
        i = endR
        j -= 1
        while startR < endR and j >= startC:
            s.append(matrix[i][j])
            j -= 1
        print s
        i -= 1
        j = startC
        while startR < endR and i >= startR+1:
            s.append(matrix[i][j])
            i -= 1
        print s
        return s

    rs = []
    startR = 0
    endR = n-1
    startC = 0
    endC = m-1
    while startR <= endR and startC <= endC:
        rs.extend(printValues(startR, endR, startC, endC, matrix))
        startR += 1
        endR -= 1
        startC += 1
        endC -= 1

    return ' '.join([str(i) for i in rs])


def findMaxNotAdjencentSubArray(arr):
    d = [0]*len(arr)
    maxVs = [None]*len(arr)
    maxVs[0] = arr[0]
    for i in xrange(len(arr)):
        if i-2 >= 0:
            d[i] = max(maxVs[i-2] + arr[i], arr[i])
        else:
            d[i] = arr[i]

        if i-1 >= 0:
            maxVs[i] = max(maxVs[i-1], d[i])
        else:
            maxVs[i] = d[i]

    return max(d)

def printPermutationsOfArrays(arrays, i, array, rs):
    if i == len(arrays):
        rs.append(array[:])
        return rs
    for e in arrays[i]:
        array.append(e)
        rs = printPermutationsOfArrays(arrays, i+1, array, rs)
        array.pop()

    return rs
def square(num, left, right):
    num = Decimal(num)
    s = [(Decimal(left), Decimal(right))]
    while s:
        it = s.pop()
        l = it[0]
        r = it[1]
        if l > r:
            return None
        mid = (l+r)/Decimal(2)

        if abs(mid**2-num) <= 0.0000001:
            return mid
        if mid**2 > num:
            s.append((Decimal(l), Decimal(mid)))
        else:
            s.append((Decimal(mid), Decimal(r)))


#print bstDistance([2,1,3,4],3,1,4)

# print findLongestPathBetweenLeaves([
#                                     [1,2],
#                                     [3],
#                                     [4,6],
#                                     [],
#                                     [5],
#                                     [],
#                                     [7],
#                                     [8,9],
#                                     [],
#                                     []
#                                    ], 0)
# arr =[i for i in xrange(1,300001)]
# print findMaxHouse(arr, 28)

# matrix = [
#             [1,2],
#             [4,5]
#          ]
# n = len(matrix)
# m = len(matrix[0])
# print printMatrixSpirally(matrix, n, m)
#print findMaxNotAdjencentSubArray([-1, 0, -3, -9, 2])
#print printPermutationsOfArrays([[1, 2, 3], [4], [5, 6]], 0, [], [])
from decimal import *
getcontext().prec = 20
num = 1000000000.0
print square(num, 0, num)



        


    
