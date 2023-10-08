def solve(n, p, b, k):
    rs = [-1]*n
    q = []
    visited = [0]*n
    for i in b:
        visited[i] = 1
    nn = k//2
    ind = 1
    if k % 2 == 1:
        nn += 1
        ind += 1
    visited[p] = 1
    rs[p] = 0
    for ii in range(nn, k):
        if p-ii < 0 or p+(k-1-ii) >= n or visited[p-ind] == 1:
            ind += 2
            continue
        visited[p-ind] = 1
        rs[p-ind] = 1
        q.append((p-ind, 1))
        ind += 2
    # print(q)
    ind = 1
    if k % 2 == 1:
        nn -= 1
        ind += 1
    for ii in range(nn-1, -1, -1):
        if p-ii < 0 or p+(k-1-ii) >= n or visited[p+ind] == 1:
            ind += 2
            continue
        visited[p+ind] = 1
        rs[p+ind] = 1
        q.append((p+ind, 1))
        ind += 2
    # print(q, visited)
    while q:
        it, c = q.pop(0)
        nn = k//2
        ind = 1
        if k % 2 == 1:
            nn += 1
            ind += 1
        for ii in range(nn, k):
            # if it == 3:
            #     print("xxx", ii, it-ii, it+(k-1-ii), it-ind)
            if it-ii < 0 or it+(k-1-ii) >= n or visited[it-ind] == 1:
                ind += 2
                continue
            visited[it-ind] = 1
            rs[it-ind] = c+1
            q.append((it-ind, c+1))
            ind += 2
        # print(q, visited)
        ind = 1
        if k % 2 == 1:
            nn -= 1
            ind += 1
        for ii in range(nn-1, -1, -1):
            if it-ii < 0 or it+(k-1-ii) >= n or visited[it+ind] == 1:
                ind += 2
                continue
            visited[it+ind] = 1
            rs[it+ind] = c+1
            q.append((it+ind, c+1))
            ind += 2
        # print(q, visited)
        # cnt_visited = 0
        # for x in visited:
        #     if x == 1:
        #         cnt_visited += 1
        # print(cnt_visited)
    return rs


def get_low(it, nn, k, n, ind):
    rs = -1
    l = nn
    r = k-1
    while l <= r:
        mid = (l+r)//2
        rs = max(rs, mid)
        # print(l, r, mid)
        if l == r:
            break
        elif it-mid < 0 and it+(k-1-mid) < n:
            r = mid-1
        elif it-mid < 0 and it+(k-1-mid) >= n:
            rs = max(rs, mid)
            break
        elif it-mid >= 0 and it+(k-1-mid) < n:
            l = mid+1
        elif it-mid >= 0 and it+(k-1-mid) >= n:
            l = mid+1
    if rs >= nn and it-rs >= 0 and it+(k-1-rs) < n:
        return it-ind-2*(rs-nn)
    elif rs-1 >= nn and it-(rs-1) >= 0 and it+(k-1-(rs-1)) < n:
        return it-ind-2*(rs-1-nn)
    return -1


def get_high(it, nn, k, n, ind):
    rs = 10**18
    l = 0
    r = nn-1
    while l <= r:
        mid = (l+r)//2
        rs = min(rs, mid)
        # print(l, r, mid)
        if l == r:
            break
        elif it-mid < 0 and it+(k-1-mid) < n:
            r = mid-1
        elif it-mid < 0 and it+(k-1-mid) >= n:
            break
        elif it-mid >= 0 and it+(k-1-mid) < n:
            r = mid-1
        elif it-mid >= 0 and it+(k-1-mid) >= n:
            l = mid+1
    if it-rs >= 0 and it+(k-1-rs) < n and nn-1 >= rs:
        return it+ind+2*(nn-1-rs)
    elif it-(rs+1) >= 0 and it+(k-1-(rs+1)) < n and nn-1 >= rs+1:
        return it+ind+2*(nn-1-(rs+1))
    return -1


def is_swap(x, y, n, k):
    diff = abs(y-x)-1
    total_ind = -1
    if k % 2 == 1:
        diff -= 1
        total_ind = (k-1)//2
    else:
        total_ind = k//2
    if diff % 2 == 1:
        return False
    idx = diff//2 + 1
    if x < y:
        if x - (total_ind-idx) >= 0 and y + (total_ind-idx) < n:
            return True
        else:
            return False
    else:
        if y - (total_ind-idx) >= 0 and x + (total_ind-idx) < n:
            return True
        else:
            return False


def solve1(n, p, b, k):
    from collections import deque
    from sortedcontainers import SortedList
    rs = [-1]*n
    q = deque()
    banned = [0]*n
    for i in b:
        banned[i] = 1
    arr = []
    for i in range(n):
        if banned[i] == 0:
            arr.append(i)
    visited = SortedList(arr)
    nn = k//2
    ind = 1
    if k % 2 == 1:
        nn += 1
        ind += 1
    visited.remove(p)
    rs[p] = 0
    if k == 1:
        return rs
    # for ii in range(nn, k):
    #     if p-ii < 0 or p+(k-1-ii) >= n or visited[p-ind] == 1:
    #         ind += 2
    #         continue
    #     visited[p-ind] = 1
    #     rs[p-ind] = 1
    #     q.append((p-ind, 1))
    #     ind += 2
    low = p - ind
    if k-1-nn > 0:
        low -= 2*(k-1-nn)
    high = p - ind
    j = visited.bisect_left(low)
    # print(p, ind, low, high, j)
    while len(visited) > j:
        v = visited.pop(j)
        if v > high:
            visited.add(v)
            break
        if is_swap(p, v, n, k):
            rs[v] = 1
            q.append((v, 1))
        else:
            visited.add(v)
            j += 1
    # print(visited)
    ind = 1
    if k % 2 == 1:
        nn -= 1
        ind += 1
    # for ii in range(nn-1, -1, -1):
    #     if p-ii < 0 or p+(k-1-ii) >= n or visited[p+ind] == 1:
    #         ind += 2
    #         continue
    #     visited[p+ind] = 1
    #     rs[p+ind] = 1
    #     q.append((p+ind, 1))
    #     ind += 2
    low = p + ind
    high = p + ind + 2*(nn-1)
    j = visited.bisect_left(low)
    # print(p, ind, low, high, j)
    while len(visited) > j:
        v = visited.pop(j)
        if v > high:
            visited.add(v)
            break
        if is_swap(p, v, n, k):
            rs[v] = 1
            q.append((v, 1))
        else:
            visited.add(v)
            j += 1
    # print(visited, q)
    while q:
        it, c = q.popleft()
        nn = k//2
        ind = 1
        if k % 2 == 1:
            nn += 1
            ind += 1
        # for ii in range(nn, k):
        #     if it-ii < 0 or it+(k-1-ii) >= n or visited[it-ind] == 1:
        #         ind += 2
        #         continue
        #     visited[it-ind] = 1
        #     rs[it-ind] = c+1
        #     q.append((it-ind, c+1))
        #     ind += 2
        low = it - ind
        if k-1-nn > 0:
            low -= 2*(k-1-nn)
        high = it - ind
        if low < 0:
            print('TOANG TOANG LOW LOW')
        j = visited.bisect_left(low)
        # print(it, ind, low, high, j)
        cnt = 0
        cnt2 = 0
        while len(visited) > j:
            v = visited.pop(j)
            if v > high:
                visited.add(v)
                break
            # print('is_swap', it, v, n, k, is_swap(it, v, n, k))
            if is_swap(it, v, n, k):
                rs[v] = c+1
                q.append((v, c+1))
                cnt2 += 1
            else:
                visited.add(v)
                j += 1
            cnt += 1
        print("CNT", cnt, cnt2)
        ind = 1
        if k % 2 == 1:
            nn -= 1
            ind += 1
        # for ii in range(nn-1, -1, -1):
        #     if it-ii < 0 or it+(k-1-ii) >= n or visited[it+ind] == 1:
        #         ind += 2
        #         continue
        #     visited[it+ind] = 1
        #     rs[it+ind] = c+1
        #     q.append((it+ind, c+1))
        #     ind += 2
        low = it + ind
        high = it + ind + 2*(nn-1)
        if high >= n:
            print('TOANG TOANG HIGH HIGH')
        j = visited.bisect_left(low)
        cnt = 0
        cnt2 = 0
        while len(visited) > j:
            v = visited.pop(j)
            if v > high:
                visited.add(v)
                break
            if is_swap(it, v, n, k):
                rs[v] = c+1
                q.append((v, c+1))
                cnt2 += 1
            else:
                visited.add(v)
                j += 1
            cnt += 1
        print("CNT", cnt, cnt2)
        # print(len(q))
    print("len visited", len(visited))
    return rs


n = 100000
k = 28803
nn = k//2
ind = 1
if k % 2 == 1:
    nn += 1
    ind += 1
for it in range(n):
    print(it, get_low(it, nn, k, n, ind))
print('-------')
nn = k//2
ind = 1
if k % 2 == 1:
    ind += 1
for it in range(n):
    print(it, get_high(it, nn, k, n, ind))
# print(get_low(2, 3, 6, 8, 1))
# print(get_low(3, 3, 6, 8, 1))
# print(get_low(4, 3, 6, 8, 1))
# print(get_low(5, 3, 6, 8, 1))
# print(get_high(2, 3, 6, 8, 1))
# print(get_high(3, 3, 6, 8, 1))
# print(get_high(4, 3, 6, 8, 1))
# print(get_high(0, 3, 6, 8, 1))
# n = 5
# p = 0
# b = []
# k = 4
# n = 2
# p = 1
# b = []
# k = 2
# n = 4
# p = 0
# b = []
# k = 4
# n = 5
# p = 0
# b = [2, 4]
# k = 3
# n = 4
# p = 2
# b = [0, 1, 3]
# k = 1
# n = 6
# p = 1
# b = []
# k = 6
# n = 10**5
# p = 1
# b = []
# k = 10**5
# print(solve(n, p, b, k))
# print(solve1(n, p, b, k))
