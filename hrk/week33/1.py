import sys
def search(bb, l, r, value):
    if l > r:
        return -1
    mid = (l+r)/2
    if bb[mid]== value:
        return mid
    if bb[mid] > value:
        return search(bb, l, mid-1, value)
    return search(bb, mid+1, r, value)
def solve(n, a, b, bb):
    t = -1;
    for i in xrange(n):
        ind = search(bb, 0, n-1, b[i])
        if ind == 0:
            x = ind + 1
        else:
            x = 0
        if t == -1 or t > a[i] + bb[x]:
            t = a[i] + bb[x]
    return t
n = int(sys.stdin.readline())
a = map(int, sys.stdin.readline().strip().split(' '))
b = map(int, sys.stdin.readline().strip().split(' '))

bb = sorted(b)

print solve(n, a, b, bb)

