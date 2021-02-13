import sys
import copy

class Solution(object):
    def isValidSubString(self, i, s, words):
        x = len(words[0])
        d = {}
        for w in words:
            if w not in d:
                d[w] = 1
            else:
                d[w] += 1
        for j in xrange(len(words)):
            t = s[i:i+x]
            if t not in d:
                return False
            else:
                d[t] -= 1
                if d[t] < 0:
                    return False
            i += x
        return True
    def findSubstring(self, s, words):
        """
        :type s: str
        :type words: List[str]
        :rtype: List[int]
        """
        print len(s), len(words)
        rs = []
        i = 0
        while i + len(words[0])*len(words) - 1 < len(s):
            if self.isValidSubString(i, s, words):
                rs.append(i)
            i += 1
        return rs

    def findMinimumCover(self, s, t):
        c = len(t)
        d = {}
        for i in t:
            if i in d: d[i] += 1
            else: d[i] = 1
        i = 0
        prev = i
        minV = -1
        minInd = -1
        sum = 1
        print d
        while i < len(s):
            if s[i] in d:
                d[s[i]] -= 1
                c -= 1
            if c == 0:
                print 'kkk', prev, sum
                if minV == -1 or minV > sum:
                    minInd = prev
                    minV = sum
                    sum -= 1
                if s[prev] in d:
                    d[s[prev]] += 1
                    c += 1
                prev += 1
            i += 1
            sum += 1
        print minInd, minV
        return s[minInd: minV]
class TreeNode():
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None

def findPathSumToK(root, k):
    def printPath(path,i):
        s = []
        for j in xrange(i,len(path)):
            s.append(str(path[j]))
        return ' '.join(s)
    def find(root, k, path, rs):
        path.append(root.value)
        print 'x',path
        s = 0
        for i in xrange(len(path)-1, -1, -1):
            s += path[i]
            if s == k:
                rs.append(printPath(path,i))
        if root.left:
            rs = find(root.left, k, path, rs)
            path.pop()
        if root.right:
            rs = find(root.right, k, path, rs)
            path.pop()
        return rs

    return find(root, k, [], [])

def findKDistanceFromNode(root, node, k):
    def find(root, path, rs):
        path.append(root.value)
        rs[root.value] = path[:]
        if root.left:
            rs = find(root.left, path, rs)
            path.pop()
        if root.right:
            rs = find(root.right, path, rs)
            path.pop()
        return rs

    rs = find(root, [], {})
    print rs


def findMaxSubstringWithDistinctCharacters(a):
    d = {}
    maxV = -1
    maxInd = -1
    for i in xrange(len(a)):
        if a[i] not in d:
            d[a[i]] = i
            c = len(d.keys())
        else:
            for k in d.keys():
                if d[k] < d[a[i]]:
                    del d[k]
            d[a[i]] = i
            c = len(d.keys())
        if maxV == -1 or maxV < c:
            maxV = c
            maxInd = i
    return maxV,a[maxInd]

def findMaxSubstringWithDistinctCharacters2(a):
    d = {}
    maxV = -1
    maxInd = -1
    for i in xrange(len(a)):
        if a[i] not in d:
            d[a[i]] = i
            c = len(d.keys())
        else:
            d = {}
            d[a[i]] = i
            c = len(d.keys())
        if maxV == -1 or maxV < c:
            maxV = c
            maxInd = i
    return maxV,a[maxInd]
def printInOrderTree(node, rs):
    if node.left:
        rs = printInOrderTree(node.left, rs)
    rs.append(str(node.value))
    if node.right:
        rs = printInOrderTree(node.right, rs)
    return rs

def buildTreeFromSortedArray(arr, start, end):
    if start > end:
        return None
    if start == end:
        node = TreeNode(arr[start])
        return node
    mid = (start + end)/2
    node = TreeNode(arr[mid])
    node.left = buildTreeFromSortedArray(arr, start, mid-1)
    node.right = buildTreeFromSortedArray(arr, mid+1, end)
    return node

def compressString(string):
    rs = ''
    char = ''
    c = 0
    for i in string:
        if char == '' or char != i:
            if char != '':
                rs += char + str(c)
            char = i
            c = 1
        else:
            c += 1
    rs += char + str(c)
    return rs
            
def printTreeinSpiralForm(root):
    rs = [root.value]
    i = 0
    stack = [root]
    while True:
        k = []
        while stack:
            it = stack.pop()
            if i%2 == 0:
                if it.left:
                    rs.append(it.left.value)
                    k.append(it.left)
                if it.right:
                    rs.append(it.right.value)
                    k.append(it.right)
            else:
                if it.right:
                    rs.append(it.right.value)
                    k.append(it.right)
                if it.left:
                    rs.append(it.left.value)
                    k.append(it.left)
        if not k:
            break
        stack = k[:]
        i += 1
    return rs

def buildTreeWithNodeEqualSumFromTree(root):
    if root.left is None and root.right is None:
        newNode = TreeNode(0)
        return newNode

    left = buildTreeWithNodeEqualSumFromTree(root.left)
    right = buildTreeWithNodeEqualSumFromTree(root.right)
    newNode = TreeNode(left.value+right.value+root.left.value+root.right.value)
    newNode.left = left
    newNode.right = right
    return newNode

def printBoundaryNodesOfTree(root):
    rs = []
    level = [[root.value, None]]
    q = [(root,0)]
    while q:
        it = q.pop(0)
        if it[0].left:
            if len(level) <= it[1]+1:
                level.append([it[0].left.value, None])
            else:
                level[it[1]+1][1] = it[0].left.value
            q.append((it[0].left, it[1]+1))
        if it[0].right:
            if len(level) <= it[1]+1:
                level.append([it[0].right.value, None])
            else:
                level[it[1]+1][1] = it[0].right.value
            q.append((it[0].right, it[1]+1))

    print level
    for l in level:
        if l[0] is not None:
            rs.append(l[0])
    for l in level[::-1]:
        if l[1] is not None:
            rs.append(l[1])
    return rs

def removeNodesHave1ChildInTree(root):
    if root.left is None and root.right is None:
        return root

    if root.left:
        root.left = removeNodesHave1ChildInTree(root.left)
    if root.right:
        root.right = removeNodesHave1ChildInTree(root.right)
    if root.left is None and root.right is not None:
        return root.right
    if root.left is not None and root.right is None:
        return root.left
    return root


#print findMaxSubstringWithDistinctCharacters('a'*500000+'b'*50000)
# xx = 'abcdefghijklmnopqrstuvwxyz'
# x = ''
# while len(x) < 100000:
#     x += xx
# print findMaxSubstringWithDistinctCharacters(x)

# root = TreeNode(1)

# root.left = TreeNode(3)
# root.right = TreeNode(-1)

# root.left.left = TreeNode(2)
# root.left.right = TreeNode(1)
# root.right.left = TreeNode(4)
# root.right.right = TreeNode(5)

# root.left.right.left = TreeNode(1)
# root.right.left.left = TreeNode(1)
# root.right.left.right = TreeNode(2)
# root.right.right.right = TreeNode(6)

# print findPathSumToK(root, 7)

#o = Solution()
#print o.findSubstring('wordgoodgoodgoodbestword',["word","good","best","good"])

#print o.findSubstring("abababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababab",
#["ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba"])
#print o.findMinimumCover('ADBCDDDABC', 'ABC')

#print compressString('AAABBBCDEFGHIJKLLLLLLLLLLLLLLL')

# arr = [5]
# root = buildTreeFromSortedArray(arr, 0, len(arr)-1)
# treeInOrder = printInOrderTree(root, [])
# print ' '.join(treeInOrder)


# root = TreeNode(1)

# root.left = TreeNode(2)
# root.right = TreeNode(3)

# root.left.left = TreeNode(7)
# root.left.right = TreeNode(6)
# root.right.left = TreeNode(5)
# root.right.right = TreeNode(4)

# root.left.right.left = TreeNode(1)
# root.right.left.left = TreeNode(1)
# root.right.left.right = TreeNode(2)
# root.right.right.right = TreeNode(6)

#print printTreeinSpiralForm(root)

#print findKDistanceFromNode(root, 3, 3)
# print printInOrderTree(root, [])
# newRoot = buildTreeWithNodeEqualSumFromTree(root)
# print printInOrderTree(newRoot, [])



root = TreeNode(20)

root.left = TreeNode(8)
root.right = TreeNode(22)

root.left.left = TreeNode(4)
root.left.right = TreeNode(12)

root.right.right = TreeNode(25)
#root.left.right.left = TreeNode(10)
root.left.right.right = TreeNode(14)
print printBoundaryNodesOfTree(root)


rs = removeNodesHave1ChildInTree(root)
print printInOrderTree(rs, [])