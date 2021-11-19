import sys
import random

def buildSegTree(h, tree, l ,r):
    if l == r:
        tree[l,r] = h[l]
        return tree[l,r]

    mid = (r-l)//2
    v1 = buildSegTree(h, tree, l, l+mid)
    v2 = buildSegTree(h, tree, l+mid+1, r)
    tree[l,r] = max(v1, v2)
    return tree[l,r]


def querySegTree(tree, l, r, start, stop):
    if r < start:
        return -1
    if l > stop:
        return -1
    if start <= l and r <= stop:
        return tree[l,r]
    mid = (r-l)//2
    v1 = querySegTree(tree, l, l+mid, start, stop)
    v2 = querySegTree(tree, l+mid+1, r, start, stop)
    return max(v1, v2)

def findNearestHigher(tree, l, r, start, stop, height):
    #print(start, stop)
    if start > stop:
        return -1

    x = querySegTree(tree, l, r, start, stop)
    if x <= height:
        return -1
    if start == stop:
        return x

    mid = (stop - start)//2
    x = querySegTree(tree, l, r, start, start+mid)
    if x <= height:
        return findNearestHigher(tree, l, r, start+mid+1, stop, height)
    return findNearestHigher(tree, l, r, start, start+mid, height)


h = [random.randint(0, 3000) for _ in range(10**5)]
#h = [2000 for _ in range(10**5)]
tree = {}
buildSegTree(h, tree, 0, len(h)-1)

for i in range(len(h)-1, -1, -1):
    #print('xxxx', i)
    x = findNearestHigher(tree, 0, len(h)-1, i+1, len(h)-1, h[i])
    print('yyyy', i, x)
print('ok')