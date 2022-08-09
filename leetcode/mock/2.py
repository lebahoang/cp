def convert_time(x):
    hour = x.split(':')[0]
    if len(hour) == 1:
        return '0{}'.format(x)
    return x
def convert_time_back(x):
    m = x%60
    h = (x-m)//60
    if len(str(m)) == 1:
        return '{:d}:0{:d}'.format(h, m)
    return '{:d}:{:d}'.format(h, m)
def toMinutes(x):
    arr = x.split(':')
    return int(arr[0])*60 + int(arr[1])
def search(c, val):
    l = 0
    r = len(c)-1
    s = val
    e = s+30
    if e <= c[l][0]:
        return -1
    if s >= c[r][1]:
        return r
    while l <= r:
        mid = (l+r)//2
        if c[mid][1] <= s and c[mid+1][0] >= s:
            if c[mid][1] <= e and c[mid+1][0] >= e:
                return mid
            return -2
        elif c[mid][1] > s:
            r = mid-1    
        else:
            l = mid+1
    return -2
        
def calendarMatching(c1, d1, c2, d2, duration):
    n = len(c1)
    for i in range(n):
        c1[i][0] = toMinutes(c1[i][0])
        c1[i][1] = toMinutes(c1[i][1])
    n = len(c2)
    for i in range(n):
        c2[i][0] = toMinutes(c2[i][0])
        c2[i][1] = toMinutes(c2[i][1])
    c1 = sorted(c1)
    c2 = sorted(c2)
    t = []
    i = toMinutes(d1[0])
    e = toMinutes(d1[1])
    s2 = toMinutes(d2[0])
    e2 = toMinutes(d2[1])
    while i < e:
        if i >= s2 and i <= e2 and i+30 >= s2 and i+30 <= e2:
            ind1 = search(c1, i)
            ind2 = search(c2, i)
            if ind1 != -2 and ind2 != -2:
                # rs.append([convert_time_back(i), convert_time_back(i+30)])
                t.append([i, i+30])
        i += 30
    for x in t:
        print(convert_time_back(x[0]), convert_time_back(x[1]))
    rs = []
    i = 0
    a = t[i][0]
    b = t[i][1]
    while True:
        for j in range(i+1, len(t)):
            i = j
            if b != t[j][0]:
                break
            else:
                b = t[j][1]
        rs.append([convert_time_back(a), convert_time_back(b)])
        if i == len(t)-1:
            break
        a = t[i][0]
        b = t[i][1]
    return rs