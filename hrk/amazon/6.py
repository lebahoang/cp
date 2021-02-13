import sys

def findLongestPalindromeSubsequence(string, d, i, j):
    for i in xrange(len(string)):
        d[i,i] = 1
    for j in xrange(1,len(string)):
        for i in xrange(len(string)):
            if i + j < len(string):
                a = d[i, i+j-1] 
                b = d[i+1, i+j]
                if string[i] == string[i+j]:
                    if i+1 <= i+j-1:
                        c = d[i+1, i+j-1] + 2
                    else:
                        c = 2
                else:
                    c = 0
                d[i, i+j] = max(a,b,c)
    return d[0, len(string)-1]

def countNumberofPlalindromeSubsequences(string):
    for i in xrange(len(string)):
        d[i,i] = 1
    for j in xrange(1,len(string)):
        for i in xrange(len(string)):
            if i + j < len(string):
                t = d[i, i+j-1] + d[i+1, i+j]
                if i+1 <= i+j-1:
                    t -= d[i+1, i+j-1]
                if string[i] == string[i+j]:
                    t += 1
                    if i+1 <= i+j-1:
                        t += d[i+1, i+j-1]
                        
                d[i,i+j] = t
    return d[0, len(string)-1]

def findShortestPathBetween2Word(start, end, dictionary):
    alphabet = 'abcdefghijklmnopqrstuvwxyz'
    visited = {start: 1}
    queue = [(start,0)]
    while queue:
        string, distance = queue.pop(0)
        visited[string] = 1
        for i in alphabet:
            for j in xrange(len(string)):
                t = string[:j] + i + string[j+1:]
                if t == end:
                    return distance+1
                if t in dictionary and t not in visited:
                    queue.append((t, distance+1))
    return -1



#string = 'abbcxxxyyyzcbba'
string = '11191'
i = 0
j = len(string)-1
d = {}
print findLongestPalindromeSubsequence(string, d, i, j)
#print countNumberofPlalindromeSubsequences(string)
#print findShortestPathBetween2Word('ab', 'dr', {'ab':1, 'ae':1, 'de':1,'bd':1, 'br':1, 'dr':1})
