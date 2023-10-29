def isCompleted(pigs, n, b):

def solve(b, test, die):
    n = -1
    if test%die == 0:
        n = test//die
    else:
        n = (test - (test%die))//die
    ans = -1
    l = 1
    r = n
    while l <= r:
        mid = (l+r)//2
        if isCompleted(mid, n, b):
            ans = min(ans, mid)
            r = mid-1
        else:
            l = mid+1
    return ans

print(solve(4, 15, 15))