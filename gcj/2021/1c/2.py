import os
import sys

def get_min_of_length(l, m):
    ll = m[l]
    x = 10**(ll-1)
    rs = x
    str_rs = str(rs)
    while len(str_rs) < l:
        rs = rs * 10**ll + (x+1)
        str_rs = str(rs)
        x += 1
        if x+1 == 10**m[l]: ll += 1
    return rs
def go(x, s, ll):
    rs_l = len(str(s))
    rs = 0
    while rs <= s:
        str_x = str(x)
        str_rs = str(rs)
        if len(str_rs) + len(str_x) > rs_l:
            return -1
        if len(str_x) > ll:
            ll += 1
        rs = rs * 10**ll + x
        # print(rs)
        x += 1
    return rs



m = [0 for _ in range(21)]
m[2] = 1
m[3] = 1
m[4] = 2
m[5] = 1
m[6] = 3
m[7] = 1
m[8] = 4
m[9] = 3
m[10] = 5
m[11] = 1
m[12] = 6
m[13] = 1
m[14] = 7
m[15] = 5 
m[16] = 8
m[17] = 1
m[18] = 9
m[19] = 1
t = int(sys.stdin.readline())
for cs in range(t):
    s = sys.stdin.readline().strip()
    l = len(s)
    rs = 10**20
    for ll in range(1, l+1):
        if 2*ll <= len(s):
            x = int(s[:ll])
            y = int(s[ll:2*ll])
            v = -1
            v1 = go(x, int(s), ll)
            v2 = go(x+1, int(s), ll)
            if v1 == -1:
                v = v2
            elif v2 == -1:
                v = v1
            else:
                v = min(v1, v2)

            j = 1
            while j*(ll+1) <= l:
                k = l-(j*(ll+1))
                if k%ll == 0:
                    x = 10**ll - (k//ll)
                    vv = go(x, int(s), ll)
                    if (vv != -1 and v > vv) or v == -1:
                        v = vv
                j += 1
            if v != -1 and rs > v:
                rs = v

    # print('AAAAA', rs, l)
    if rs == 10**20:
        rs = get_min_of_length(l+1, m)
    
    print("Case #{:d}: {:d}".format(cs+1, rs))
