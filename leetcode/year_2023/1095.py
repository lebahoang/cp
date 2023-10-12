def find_peak(m, n):
    l = 0
    r = n-1
    while l <= r:
        mid = (l+r)//2
        if (mid-1 < 0 or m[mid-1] < m[mid]) and (mid+1 >= n or m[mid] < m[mid+1]):
            l = mid+1
        elif (mid-1 < 0 or m[mid-1] > m[mid]) and (mid+1 >= n or m[mid] > m[mid+1]):
            r = mid-1
        else:
            return mid
    return -1
def find_left(m, a, b, target):
    if m[a] == target:
        return a
    if m[b] == target:
        return b
    l = a
    r = b
    while l <= r:
        mid = (l+r)//2
        if m[mid] == target:
            return mid
        elif m[mid] < target:
            l = mid+1
        else:
            r = mid-1
    return -1
def find_right(m, a, b, target):
    if m[a] == target:
        return a
    if m[b] == target:
        return b
    l = a
    r = b
    while l <= r:
        mid = (l+r)//2
        if m[mid] == target:
            return mid
        elif m[mid] < target:
            r = mid-1
        else:
            l = mid+1
    return -1
def solve(m, target):
    n = len(m)
    ind = find_peak(m, n)
    rs1 = find_left(m, 0, ind, target)
    if m[ind] < target:
        return -1
    if rs1 != -1:
        return rs1
    return find_right(m, ind, n-1, target)

# m = [1,2,3,40,39,36,4,2,1]
# target = 4
m = [3,5,3,2,0]
target = 0
print(solve(m, target))