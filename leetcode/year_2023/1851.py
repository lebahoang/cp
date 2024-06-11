import random
import heapq
def solve(intervals, qs):
    ans = {}
    arr = []
    d = {}
    d1 = {}
    d2 = {}
    d3 = {}
    for x in intervals:
        if x[0] not in d1:
            d1[x[0]] = [(x[1]-x[0]+1, x[1])]
        else:
            d1[x[0]].append((x[1]-x[0]+1, x[1]))
        d2[x[1]] = 1
        d[x[0]] = 1
        d[x[1]] = 1
    for i in qs:
        d3[i] = 1
        d[i] = 1
    arr = []
    for i in d.keys():
        arr.append(i)
    arr = sorted(arr)
    q = []
    heapq.heapify(q)
    for i in arr:
        if i in d1:
            for sz, end in d1[i]:
                heapq.heappush(q, (sz, end))
        if i in d3:
            # print(q)
            if q:
                ans[i]= q[0][0]
            else:
                ans[i] = -1
        if i in d2:
            while True:
                if not q or q[0][1] > i:
                    break
                heapq.heappop(q)
    out = []
    for i in qs:
        out.append(ans[i])
    return out

# intervals = [[1,4],[2,4],[3,6],[4,4]]
# queries = [2,3,4,5]

intervals = [[2,3],[2,5],[1,8],[20,25]]
queries = [2,19,5,22]

print("RS: ", solve(intervals, queries))
