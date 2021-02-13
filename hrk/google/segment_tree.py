import math


def update_by_add(node_left, node_right):
    return node_left+node_right
def update_by_max(node_left, node_right):
    return max(node_left, node_right)
def update_by_min(node_left, node_right):
    return min(node_left, node_right)


def get_max(node_left, node_right):
    return max(node_left, node_right)
def get_min(node_left, node_right):
    return min(node_left, node_right)
def get_sum(node_left, node_right):
    return node_left + node_right

class SimpleSegmentTree():
    def __init__(self, num_items, get_two_node_value_func, update_one_node_value_func):
        self.num_items = num_items

        # get_two_node_value_func is a func which outputs a value
        # we want to store in tree nodes, 2 common types are max and sum 
        self.get_two_node_value_func = get_two_node_value_func
        self.update_one_node_value_func = update_one_node_value_func
        self.tree = self._build_tree()
    def _get_number_nodes(self):
        x = math.ceil(math.log(self.num_items, 2))
        return ((1-2**(x+1))//(1-2)) + 1
    def _build_tree(self):
        n = self._get_number_nodes()
        return [0]*n
    def _update(self, value, ind, start, end, l, r):
        # update value of 1 node in tree
        # [start, end] is an updating index interval of segment tree
        # print(start, end, l, r)
        if start > r or end < l:
            return
        if start >= l and end <= r:
            self.tree[ind] = self.update_one_node_value_func(self.tree[ind], value)
            return
        mid = (start+end)//2
        self._update(value, 2*ind+1, start, mid, l, r)
        self._update(value, 2*ind+2, mid+1, end, l, r)

        self.tree[ind] = self.get_two_node_value_func(self.tree[2*ind+1], self.tree[2*ind+2])

    def update(self, value, ind):
        self._update(value, 0, 0, self.num_items-1, ind, ind)
    def _query(self, ind, start, end, l, r):
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



# n = 5
# tree = SimpleSegmentTree(n, get_max, update_by_add)
# tree.update(1, 0)
# tree.update(6, 1)
# tree.update(2, 2)
# tree.update(10, 3)
# tree.update(3, 4)
# print(tree.query(1, 4))
# print('--------------------------------')
# n = 10**6
# tree = LazySegmentTree(n, get_max, update_by_add)
# tree.update(1, 10, 100)
# tree.update(6, 1, 10)
# tree.update(2, 2, 10)
# tree.update(10, 3, 10)
# tree.update(3, 4, 10)
# print(tree.query(1, 4))


def foo_update(node, value):
    if node != 0:
        return node
    return value
def foo_min(node_left, node_right):
    if node_left == 0: return node_right
    if node_right == 0: return node_left
    return min(node_left, node_right)


# arr = [34, 80, 10, 3, 2, 80, 30, 33, 1]
arr = [i for i in range(1, 10**5+1)] + [234*10**6]
b = sorted(arr)
d = {}
for i,a in enumerate(b):
    if a not in d:
        d[a] = i+1

n = len(arr)
tree = SimpleSegmentTree(n, foo_min, foo_update)
print(len(tree.tree))
max_v = -1
for ind, a in enumerate(arr):
    i = d[a]
    tree.update(ind+1, i)
    if i-1 >= 0:
        min_ind = tree.query(0, i-1)
        if min_ind == 0: continue
        min_ind -= 1
        if max_v == -1 or max_v < ind-min_ind:
            # print('ttt', ind, min_ind)
            max_v = ind-min_ind
print('max', max_v)




        