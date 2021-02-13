def f(n, m, grid):
    # create the answer array
    ans = [[0]*m for i in range(n)]

    height = [0]*m
    left   = [0]*m
    right  = [0]*m

    for i in range(n):

        # calculate height
        for j in range(m):
            height[j] += 1
            height[j] *= grid[i][j]

        # calculate left
        stack = [-1]
        for j in range(m):
            while stack[-1] >= 0 and height[stack[-1]] > height[j]:
                stack.pop()
            left[j] = stack[-1]
            stack.append(j)

        # calculate right
        stack = [m]
        for j in range(m-1,-1,-1):
            while stack[-1] < m and height[stack[-1]] >= height[j]:
                stack.pop()
            right[j] = stack[-1]
            stack.append(j)

        # initialize counter structure
        present = set()
        count = [0]*m
        def add(v):
            if v < 0: return
            if not count[v]: present.add(v)
            count[v] += 1
        def rem(v):
            if v < 0: return
            count[v] -= 1
            if not count[v]: present.remove(v)

        add(m-1)

        # calculate events
        mheight = max(height)
        events = [[] for h in range(mheight)]
        for j in range(m):
            if height[j] < mheight:
                events[height[j]].append(j)

        # process events by height
        for h in range(mheight):

            # process events
            for e in events[h]:
                l = left[e]
                r = right[e]
                rem(r - l - 2)
                add(r - e - 2)
                add(e - l - 2)

            #assert len(present)**2 <= 2*m

            # update ans
            for w in present:
                ans[h][w] += count[w]

    # need a final DP to finish everything
    for i in range(n):
        for j in range(m-1,0,-1):
            if j >= 2:
                ans[i][j-2] -= ans[i][j]
            ans[i][j-1] += 2*ans[i][j]
        ans

    return ans

def placeGarden2(land,garden):
    l = []
    for x in land:
        l.append([int(k) for k in x])
    # print(l)
    n = len(l)
    m = len(l[0])
    if n > m:
        ans = list(zip(*f(m, n, list(zip(*l)))))
    else:
        ans = f(n, m, l)
    rs = []
    for x,y in garden:
        if x-1 < n and y-1 < m:
            rs.append(ans[x-1][y-1])
    return rs


print(placeGarden2(['000'], [[1,2]]))
    


