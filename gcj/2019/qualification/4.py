import sys

def env(string, brokens):
    rs = []
    string_t = string[:]
    for i in brokens:
        string_t[i] = -1
    for i in string_t:
        if i != -1:
            rs.append(i)
    return rs


def find_0(resp_string_range, resp_string):
    for i in range(resp_string_range[0], resp_string_range[1]+1):
        if resp_string[i] == 0: return True
    return False
def diff(string_range, string, resp_string_range, resp_string):
    # if not found 0 then we detected an index
    if not find_0(resp_string_range, resp_string):
        return []

    a1 = 0
    a2 = 0
    a1_ind = -1
    a2_ind = -1
    flag = True
    for i in range(string_range[0], string_range[1]+1):
        if string[i] == 0:
            flag = False
        if flag == True and string[i] == 1:
            a1 += 1
            a1_ind = i
        elif flag == False and string[i] == 1:
            a2 += 1
            if a2_ind == -1:
                a2_ind = i
    b1 = 0
    b2 = 0
    b1_ind = -1
    b2_ind = -1
    flag = True
    for i in range(resp_string_range[0], resp_string_range[1]+1):
        if resp_string[i] == 0:
            flag = False
        if flag == True and resp_string[i] == 1:
            b1 += 1
            b1_ind = i
        elif flag == False and resp_string[i] == 1:
            b2 += 1
            if b2_ind == -1:
                b2_ind = i

    rs = []
    if b1 == 0 and a1_ind > -1:
        rs.append([string_range[0], a1_ind])
    if a1 > 0 and b1 > 0 and a1 != b1:
        rs.append([string_range[0], a1_ind, resp_string_range[0], b1_ind])

    if b2 == 0 and a2_ind > -1:
        rs.append([a2_ind, string_range[1]])
    if a2 > 0 and b2 > 0 and a2 != b2:
        rs.append([a2_ind, string_range[1], b2_ind, resp_string_range[1]])
    return rs


def go(string_range, string, resp_string_range, brokens, rs, f_calls):
    if string_range[0] >= string_range[1]:
        return

    mid = (string_range[0] + string_range[1])//2
    t = mid
    ranges = []
    flag1 = True
    while True:
        string[t] = 0
        f_calls.append(1)
        resp_string = env(string, brokens)
        print(string, resp_string)
        ranges = diff(string_range, string, resp_string_range, resp_string)
        print(ranges)
        if len(ranges) == 0:
            string[t] = 1
            if flag1:
                t -=1
                if t < string_range[0]:
                    t = mid + 1
                    flag1 = False
            else:
                t += 1
                if t > string_range[1]:
                    break
        else:
            break
            
    
    for r in ranges:
        if len(r) == 2:
            rs.extend([k for k in range(r[0], r[1]+1)])
            continue

        string_range_t = [r[0], r[1]]
        resp_string_range_t = [r[2], r[3]]
        go(string_range_t, string, resp_string_range_t, brokens, rs, f_calls)

def solve(n, brokens):
    string = [1]*n
    string_range = [0, n-1]
    resp_string_range = [0, n-len(brokens)-1]
    rs = []
    f_calls = []
    go(string_range, string, resp_string_range, brokens, rs, f_calls)
    print('----------')
    print('Number F calls', len(f_calls))
    return rs


n = 2**10
brokens = [0,7,80]
print(solve(n, brokens))





