import sys

def getSegment(a, start, m):
    n = len(a)
    s = 0
    for i in xrange(start+1, n):
        t = a[i] - a[i-1]
        if t >= hmin and t <= hmax:
            s += t 
            if s > m:
                return i-1
        else:
            return i-1
    return n-1

n = int(sys.stdin.readline())
a = map(int, sys.stdin.readline().strip().split(' '))
m,hmin,hmax = map(int, sys.stdin.readline().strip().split(' '))

a.insert(0, a[0]-hmax)
a.append(a[-1]+hmax)

# for k,i in enumerate(a):
#     if  i == -186143188:
#         print k, 'jjj'

xs = []
for i in xrange(len(a)-1):
    if i-1 < 0 or xs[i-1] == None:
        if a[i+1] - a[i] >= hmin and a[i+1] - a[i] <= hmax:
            j = getSegment(a, i, m)
            if j != i:
                xs.append((i,j, a[j]-a[i]))
            else:
                xs.append(None)
        else:
            xs.append(None)
    elif xs[i-1] != None:
        k = xs[i-1][2] - (a[i] - a[i-1])
        j = getSegment(a, xs[i-1][1], m-k)
        if j != i:
            xs.append((i,j, a[j]-a[i]))
        else:
            xs.append(None)

#print xs[3678:]
rs = None
for l,k in enumerate(xs):
    if k != None:
        i, j, dis = k
        if dis == m:
            rs = a[i]
        else:
            need = m-dis
            if i-1 >= 0:
                t = a[i] - a[i-1]
                if need >= hmin and need <= hmax and need <= t:
                    rs = a[i] - need
            if j+1 < len(a):
                t = a[j+1] - a[j]
                if need >= hmin and need <= hmax and need <= t:
                    rs = a[i]
            x = a[i]-a[i-1] if i-1 > 0 else None
            y = a[j+1]-a[j] if j+1 < len(a) else None

            if x != None and y != None:
                if x >= hmin and y >= hmin:
                    g = need - min(hmax, x)
                    gg = need - min(hmax, y)
                    if g >= hmin and g <= hmax and g <= y:
                        rs = a[i] - min(hmax, x)
                        #print 'hhh', rs
                    if gg >= hmin and gg <= hmax and gg <= x:
                        rs = a[i] - gg
                        #print 'uuu', rs
        #print 'ff', i, rs
    else:
        if l+1 < len(a):
            t = a[l+1] - a[l]
            if t >= hmin and m <= t and m >= hmin and m <= hmax:
                rs = a[l]
#print '------------------'
print rs

