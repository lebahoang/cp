import sys

sys.setrecursionlimit(100000)
def longestEvenWord(sentence):
    words = sentence.split(' ')
    maxV = -1
    w = ''
    for word in words:
        if len(word)%2 == 0:
            if maxV == -1 or maxV < len(word):
                maxV = len(word)
                w = word
    if w == '':
        return '00'
    return w

def isPangram(strings):
    alphabet = 'abcdefghijklmnopqrstuvwxyz'
    rs = []
    for string in strings:
        t = {}
        for s in string:
            if s not in t:
                t[s] = 1
            else:
                t[s] += 1
        n = '1'
        for char in alphabet:
            if char not in t:
                n = '0'
                break
        rs.append(n)
    return rs

def findShortest(s,d):
    i = 0
    j = len(s)-1
    c = 0
    while i < j:
        if s[i] != s[j]:
            a = findShortest(s[i:j+1]+s[i])
            b = findShortest(s[j]+s[i:j+1])
            c += min(a,b)
        i += 1
        j -= 1
    return c
def shortestPalindrome(s):
    if len(s) == 1: return 0
    i = 0
    j = len(s)-1
    c = 0
    while i < j:
        if s[i] != s[j] and i <= j-1:
            a = shortestPalindrome(s[i+1:j+1])
            b = shortestPalindrome(s[i:j])
            c = min(a,b) + 1
            return c
        i += 1
        j -= 1
    return c

def shortestPalindrome2(s):
    d = [[0 for i in xrange(len(s))] for i in xrange(len(s))]
    for i in xrange(len(s)):
        d[i][i] = 0
    for i in xrange(len(s)-1):
        if s[i] != s[i+1]:
            d[i][i+1] = 1
        else:
            d[i][i+1] = 0

    for j in xrange(len(s)):
        for i in xrange(len(s)):
            if i+j < len(s):
                if s[i] == s[i+j]:
                    if i < i+j-1:
                        d[i][i+j] = d[i+1][i+j-1]
                    else:
                        d[i][i+j] = 0
                else:
                    d[i][i+j] = min(d[i+1][i+j], d[i][i+j-1]) + 1
    return d[0][len(s)-1]

def find(h, k):
    i = k
    while i in h:
        i += 1
    return i
def  getMinimumUniqueSum(arr):
    h = {}
    for i in arr:
        if i not in h:
            h[i] = 1
        else:
            h[i] += 1
    sum = 0
    for k,v in h.items():
        if v == 1:
            sum += k
        else:
            t = v
            while t > 1:
                next = find(h,k)
                h[next] = 1
                t -= 1
                sum += next
            sum += k
    return sum

def findEasyStrings(a, b):
    q = [(a,0)]
    while q:
        string, dis = q.pop(0)
        if string == b: return dis
        for i in xrange(len(string)-1):
            t = string[:i] + string[i+1] + string[i]
            if i+2 < len(string):
                t += string[i+2:]
            q.append((t,dis+1))
        t = string[-1] + string[1:len(string)-1] + string[0]
        q.append((t,dis+1))

def count():
    p = [0 for i in range(10)]
    p[0] = 1
    p[1] = 1
    for i in range(2, 10):
        p[i] = i*p[i-1]

    c = 0
    for k in range(1, 10):
        c += (p[9] / (p[k] * p[9-k])) * (9**k)
    print(c)
#print getMinimumUniqueSum([3,2,1,2,7])
#print shortestPalindrome('aabedaa')
#print findEasyStrings('aadefgrb', 'baedfgra')
count()




    






