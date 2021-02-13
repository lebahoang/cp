import sys
mod = 10**9 + 7
def point2interval(i, intervals):
    l = 0
    r = len(intervals)-1
    while True:
        if l > r: break
        mid = (l+r)//2
        s = intervals[mid][0]
        e = intervals[mid][1]
        if (s <= i and e >= i): return mid
        if (s > i):
            r = mid-1
        elif (e < i):
            l = mid+1
    return -1

def solve(n, w, l, h, intervals, ps):
    dp = []
    dp.append((w+h[0])*2)
    total = [dp[0]]
    # print(dp[0])
    for i in range(1, n):
        p = ((ps[i][0]+l[i]+w-ps[i][1])*2)%mod
        j = point2interval(i, intervals)
        if j-1 >= 0:
            total.append((p%mod + total[intervals[j-1][1]]%mod)%mod)
        else:
            total.append(p%mod)
        # print('P', total[-1])
        dp.append(((dp[-1]%mod)*(total[-1]))%mod)
    return dp[n-1]

t = int(sys.stdin.readline())
for cs in range(t):
    n,k,w = map(int, sys.stdin.readline().strip().split(' '))
    l = list(map(int, sys.stdin.readline().strip().split(' ')))
    a,b,c,d = map(int, sys.stdin.readline().strip().split(' '))
    for i in range(k, n):
        l.append(((a*l[-2] + b*l[-1] + c)%d) + 1)
    h = list(map(int, sys.stdin.readline().strip().split(' ')))
    a,b,c,d = map(int, sys.stdin.readline().strip().split(' '))
    for i in range(k, n):
        h.append(((a*h[-2] + b*h[-1] + c)%d) + 1)
    
    intervals = []
    ps = []
    s = 0
    e = 0
    maxH = h[0]
    ps.append((maxH, l[s]))
    for i in range(1, n):
        if (l[i] < l[i-1]+w):
            e = i
            maxH = max(maxH, h[i])
        else:
            intervals.append((s, e))
            s = i
            e = i
            maxH = h[i]
        ps.append((maxH, l[s]))
    intervals.append((s, e))
    # print(intervals, ps)
    print('Case #{:d}: {:d}'.format(cs+1, solve(n,w,l,h,intervals,ps)))