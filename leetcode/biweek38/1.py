import functools
def cmp(a, b):
    if a[0] < b[0]: return -1
    elif a[0] > b[0]: return 1
    return 0
def solve(arr):
    arr = sorted(arr, key = functools.cmp_to_key(cmp))
    rs = -1
    for i in range(len(arr)-1):
        rs = max(rs, arr[i+1][0]-arr[i][0])
    return rs
print(solve([[3,1],[9,0],[1,0],[1,4],[5,3],[8,8]]))

