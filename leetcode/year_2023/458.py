def isCompleted(pigs, n, b):
    cnt = 0
    s = b
    while s >= pigs:
        rem = 0
        mod = (s-1-(pigs-1)) % pigs
        if mod == 0:
            rem = (s-1-(pigs-1)) // pigs
        else:
            rem = (s-1-(pigs-1)-mod) // pigs + 1
        s = rem
        cnt += 1
    if s > 1:
        cnt += 1
    print(cnt, n, s)
    if cnt <= n:
        return True
    return False
def solve(b, die, test):
    n = -1
    if test%die == 0:
        n = test//die
    else:
        n = (test - (test%die))//die
    ans = 10**9
    l = 1
    r = b
    while l <= r:
        mid = (l+r)//2
        if isCompleted(mid, n, b):
            print(ans, mid)
            ans = min(ans, mid)
            r = mid-1
        else:
            l = mid+1
    return ans

# print(solve(10, 3, 3))
isCompleted(3, 1, 7)