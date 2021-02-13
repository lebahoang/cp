import sys
import math

class LazySegmentTree():
    def __init__(self, num_items, get_two_node_value_func, update_one_node_value_func):
        self.num_items = num_items

        # get_node_value_func is a func which outputs a value
        # we want to store in tree nodes, 2 common types are max and sum 
        self.get_two_node_value_func = get_two_node_value_func
        self.update_one_node_value_func = update_one_node_value_func
        self.tree, self.lazy = self._build_tree()
    def _get_number_nodes(self):
        x = math.ceil(math.log(self.num_items, 2))
        return ((1-2**(x+1))//(1-2)) + 1
    def _build_tree(self):
        n = self._get_number_nodes()
        return [0]*n, [0]*n
    def _update(self, value, ind, start, end, l, r):
        # update value of 1 node in tree
        # [start, end] is an updating index interval of segment tree
        # [l, r] is user input index interval

        # WARNING NEED TO USE UPDATE_VALUE_FUNC !!!
        if self.lazy[ind] != 0:
            self.tree[ind] = self.update_one_node_value_func(self.tree[ind], self.lazy[ind])
            if start != end:
                self.lazy[2*ind+1] = self.update_one_node_value_func(self.lazy[2*ind+1], self.lazy[ind])
                self.lazy[2*ind+2] = self.update_one_node_value_func(self.lazy[2*ind+2], self.lazy[ind])
            self.lazy[ind] = 0
        if start > r or end < l:
            return
        if start >= l and end <= r:
            self.tree[ind] = self.update_one_node_value_func(self.tree[ind], value)
            if start != end:
                self.lazy[2*ind+1] = self.update_one_node_value_func(self.lazy[2*ind+1], value)
                self.lazy[2*ind+2] = self.update_one_node_value_func(self.lazy[2*ind+2], value)
            return
        mid = (start+end)//2
        self._update(value, 2*ind+1, start, mid, l, r)
        self._update(value, 2*ind+2, mid+1, end, l, r)

        self.tree[ind] = self.get_two_node_value_func(self.tree[2*ind+1], self.tree[2*ind+2])

    def update(self, value, l, r):
        self._update(value, 0, 0, self.num_items-1, l, r)
    def _query(self, ind, start, end, l, r):
        if self.lazy[ind] != 0:
            self.tree[ind] = self.update_one_node_value_func(self.tree[ind], self.lazy[ind])
            if start != end:
                self.lazy[2*ind+1] = self.update_one_node_value_func(self.lazy[2*ind+1], self.lazy[ind])
                self.lazy[2*ind+2] = self.update_one_node_value_func(self.lazy[2*ind+2], self.lazy[ind])
            self.lazy[ind] = 0
        if start > r or end < l:
            return None

        if start >= l and end <= r:
            return self.tree[ind]

        mid = (start + end)//2
        a = self._query(2*ind+1, start, mid, l, r)
        b = self._query(2*ind+2, mid+1, end, l, r)
        if a is None: return b
        elif b is None: return a
        return self.get_two_node_value_func(a, b)
    def query(self, l, r):
        return self._query(0, 0, self.num_items-1, l, r)


def _get_2_node(a,b):
    return max(a,b)
def _update_1_node(node, value):
    return node+value
def solve(p,q,people):
    treeX = LazySegmentTree(q+1, _get_2_node, _update_1_node)
    treeY = LazySegmentTree(q+1, _get_2_node, _update_1_node)
    for p in people:
        x,y,direction = p
        if direction == 'S' or direction == 'N':
            if direction == 'S':
                treeY.update(1, 0, y-1)
                treeX.update(y, 0,q)
            else:
                treeY.update(1, y+1, q)
                treeX.update(q-y, 0,q)
        else:
            if direction == 'W':
                treeX.update(1, 0, x-1)
                treeY.update(x, 0,q)
            else:
                treeX.update(1, x+1, q)
                treeY.update(q-x, 0,q)


    # print(treeX.query(0,q))
    # print(treeY.query(0,q))
    
    xmax = -1
    xmaxV = -1
    for x in range(0, q+1):
        k = treeX.query(x,x)
        if xmaxV == -1 or xmaxV < k:
            xmaxV = k
            xmax = x
    
    # print(xmax, xmaxV)
    ymax = -1
    ymaxV = -1
    for y in range(0, q+1):
        k = treeY.query(y,y)
        if ymaxV == -1 or ymaxV < k:
            ymaxV = k
            ymax = y
    # print(ymax, ymaxV)
    return xmax, ymax

   
t = int(sys.stdin.readline().strip())
for case in range(t):
    p,q = map(int, sys.stdin.readline().strip().split(' '))
    people = []
    for _ in range(p):
        line = sys.stdin.readline().strip().split(' ')
        x,y = int(line[0]), int(line[1])
        direction = line[2]
        people.append((x,y,direction))
    rsx, rsy = solve(p,q,people)
    print('Case #{:d}: {:d} {:d}'.format(case+1, rsx, rsy))
