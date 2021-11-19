import sys

def smallestPalindrome(s0):
    def getString(t,n):
        rs = ''
        f = 0
        for i in xrange(n-1,-1,-1):
            if t[i] < 'z' and f == 0:
                rs = chr(ord(t[i]) + 1) + rs
                f = 1
            else:
                rs = t[i] + rs
        return rs


    t = ''
    i = -1
    rs = ''
    if len(s0)%2 == 0:
        t = s0[:len(s0)/2]
        i = len(s0)/2
        if s0[i:] <= t[::-1]:
            rs = t + t[::-1]
        else:
            x = getString(t, len(t))
            rs = x + x[::-1]
    else:
        t = s0[:len(s0)/2]
        i = len(s0)/2+1
        m = s0[len(s0)/2]
        if s0[i:] <= t[::-1]:
            rs = t + m + t[::-1]
        else:
            if m < 'z':
                rs = t + chr(ord(m) + 1) + t[::-1]
            else:
                x = getString(t,len(t))
                rs = x + m + x[::-1]

    return rs



def combinationSum(a, sum):
    d = {}
    for i in a:
        d[i] = [[i]]

    for i in a:
        for s in xrange(0,sum+1):
            if s-i in d:
                t = []
                for k in d[s-i]:
                    y = k[:]
                    y.append(i)
                    t.append(y)
                if s in d:
                    d[s].extend(t)
                else:
                    d[s] = t

    #print d
    if sum in d:
        rs = []
        v = {}
        for k in d[sum]:
            k = sorted(k)
            x = ' '.join([str(i) for i in k])
            x = '(' + x + ')'
            if x not in v:
                rs.append(x)
                v[x] = 1
        return ''.join(sorted(rs))
    return 'Empty'

def findArrangements(n, k):
    if n == 1:
        return 1
    rs = 0
    for i in xrange(k+1):
        rs += findArrangements(n-1,k-i)
    return rs
def findArrangementsDynamic(n,k):
    d = {}
    for i in xrange(k+1):
        d[1,i] = 1
    for i in xrange(2,n+1):
        for j in xrange(k+1):
            d[i,j] = 0
            for m in xrange(j+1):
                d[i,j] += d[i-1,j-m]

    return d[n,k]

def ballPermutations(N, M, K):
    mod = 10**9+7
    x = max(N+K+1, M)
    d = [-1]*(x+1)
    d[0] = 1
    for i in xrange(1, len(d)):
        d[i] = d[i-1]*i
    
    y = findArrangementsDynamic(N+1,K)
    return (y*d[N+K+1]/(d[M]*d[N+K+1-M])) % mod

def findMaxSumPath(a,b):
    c = []
    i = 0
    j = 0
    while i < len(a) and j < len(b):
        if a[i] < b[j]:
            c.append((a[i],1))
            i += 1
        else:
            c.append((b[j],2))
            j += 1
    if i < len(a):
        for num in a[i:]:
            c.append((num, 1))
    if j < len(b):
        for num in b[j:]:
            c.append((num, 2))

    #print c
    m = 0
    n = 0
    rs = 0
    i = 0
    while i < len(c):
        if i == len(c) - 1:
            if c[i][1] == 1:
                m += c[i][0]
            else:
                n += c[i][0]
            i += 1
        else:
            if c[i][0] != c[i+1][0]:
                if c[i][1] == 1:
                    m += c[i][0]
                else:
                    n += c[i][0]
                i += 1
            else:
                #print m,n,c[i],'fff'
                rs += max(m,n) + c[i][0]
                m = 0
                n = 0
                i += 2
    rs += max(m,n)
    return rs

def partition(arr, l, r):
    mid = (l+r)/2

    t = arr[r]
    arr[r] = arr[mid]
    arr[mid] = t

    i = l
    j = r-1
    while i < j:
        while i <= r-1 and arr[i] < arr[r]:
            i += 1
        while j >= 0 and arr[j] > arr[r]:
            j -= 1

        if i < j:
            t = arr[j]
            arr[j] = arr[i]
            arr[i] = t

    t = arr[i]
    arr[i] = arr[r]
    arr[r] = t
    return arr,i


def quickSort1(arr, l, r):
    if l < r:
        arr,i = partition(arr, l ,r)
        quickSort1(arr, l, i-1)
        quickSort1(arr, i+1, r)
    return arr

def quickSort2(arr, q):
    while q:
        l,r = q.pop()
        arr,i = partition(arr, l, r)
        if l <= i-1:
            q.append((l,i-1))
        if i+1 <= r:
            q.append((i+1, r))
    return arr

def findPositionOfElement(arr, i):
    a = []
    b = []
    for e in arr:
        if i > e:
            a.append(e)
        elif i < e:
            b.append(e)

    j = len(a) + 1
    return a,b,j

def getKsmallestElement(arr, k):
    if len(arr) < k:
        return None
    t = arr[:]
    while True:
        mid = len(t)/2
        a,b,j = findPositionOfElement(t, t[mid])
        #print t,a,b,j
        if j == k:
            return t[mid]
        elif j < k:
            t = b[:]
            k = k-j
        else:
            t = a[:]

def getKsmallestElement2(arr, k):
    if len(arr) < k:
        return None
    l = 0
    r = len(arr)-1
    while l < r:
        arr, i = partition(arr, l, r)
        if i-l+1 == k:
            return arr[i]
        elif i-l+1 < k:
            k -= i-l+1
            l = i+1
        else:
            r = i-1



#print smallestPalindrome('afzzzzz')
#print combinationSum([2,3,5,9],9)

#print ballPermutations(100,100,100)
#print findMaxSumPath([2, 3, 7, 10, 12, 15, 30, 34],[1, 5, 7, 8, 10, 15, 16, 19])

#print findMaxSumPath([1,2,3,4,5],[3,4,5,6])
# a = [i for i in xrange(1,500001)]
# b = [i for i in xrange(3000,503001)]
# print len(a) + len(b)
# print findMaxSumPath(a,b)
arr = [i for i in xrange(1,1000001)]
# print getKsmallestElement(arr, 2)
# print getKsmallestElement(arr, 20)
# print getKsmallestElement(arr, 21)
# print getKsmallestElement(arr, 122)
# print getKsmallestElement(arr, 322)
# print getKsmallestElement(arr, 3212)
# print getKsmallestElement(arr, 32212)
# print getKsmallestElement(arr, 12)
# print getKsmallestElement(arr, 54)
#print getKsmallestElement(arr, 464524)
# print getKsmallestElement(arr, 89)
# print getKsmallestElement(arr, 999)
# print getKsmallestElement(arr, 54645)
print getKsmallestElement2(arr, 3)
