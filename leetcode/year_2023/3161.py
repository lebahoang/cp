import math
import sortedcontainers as c
NEG_INF = int(-1e12)


class SimpleSegmentTree:
    def __init__(self, numItemsx, get, update) -> None:
        self.numItems = numItemsx
        self.tree: list[int] = []
        self.getFunc = get
        self.updateFunc = update
        self.buildTree()
        print(len(self.tree))

    def getNumberOfNodes(self):
        x = math.ceil(math.log2(self.numItems))
        return int((1-math.pow(2, x+1))/(1-2)) + 1

    def buildTree(self):
        self.tree = [0]*self.getNumberOfNodes()

    def _update(self, value, ind, start, end, l, r):
        # update value of 1 node in tree
        # [start, end] is an updating index interval of segment tree
        # print(start, end, l, r)
        if start > r or end < l:
            return

        if start >= l and end <= r:
            self.tree[ind] = self.updateFunc(self.tree[ind], value)
            return

        mid = (start+end)//2
        self._update(value, 2*ind+1, start, mid, l, r)
        self._update(value, 2*ind+2, mid+1, end, l, r)

        self.tree[ind] = self.getFunc(self.tree[2*ind+1], self.tree[2*ind+2])

    def _query(self, ind, start, end, l, r) -> int:
        if (start > r or end < l):
            return NEG_INF

        if start >= l and end <= r:
            return self.tree[ind]

        mid = (start + end)//2
        a = self._query(2*ind+1, start, mid, l, r)
        b = self._query(2*ind+2, mid+1, end, l, r)
        if a == NEG_INF:
            return b
        if b == NEG_INF:
            return a
        return self.getFunc(a, b)

    def update(self, value, ind):
        return self._update(value, 0, 0, self.numItems-1, ind, ind)

    def query(self, l, r):
        return self._query(0, 0, self.numItems-1, l, r)


def get(a, b):
    return max(a, b)


def update(_, val):
    return val

def solve(qs):
    rs = []
    l = c.SortedList([])
    tree = SimpleSegmentTree(50005, get, update)
    for q in qs:
        if len(q) == 2:
            _, x = q
            ind = l.bisect_left(x)-1
            if ind >= 0:
                y = l[ind]
                tree.update(x-y, x)
            if ind+1 < len(l):
                y = l[ind+1]
                tree.update(y-x, y)
            l.add(x)
        else:
            _, x, sz = q
            maxV = tree.query(0, x)
            if maxV >= sz:
                rs.append(True)
            else:
                rs.append(False)
    return rs


qs = [[1,2],[2,3,3],[2,3,1],[2,2,2]]
print(solve(qs))