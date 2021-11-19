import sys

def flip_s(s):
    rs = ''
    for i in s:
        if i == '1': rs += '0'
        else: rs += '1'
    return rs

def calculate_left_right_sum(x):
    lx = []
    for i in range(len(x)):
        if i == 0:
            lx.append(x[i])
        else:
            lx.append(x[i] + lx[-1])
    rx = []
    for i in range(len(x)-1, -1, -1):
        if i == len(x)-1:
            rx.append(x[i])
        else:
            rx.append(x[i] + rx[-1])
    return lx, rx

def solve(a,b,p):
    if p == 0:
        return sum(a) + sum(b)
    if p >= max(len(a), len(b)):
        return 0
    # if p == len(a):
    #     return min(b[0], b[-1])
    # if p == len(b):
    #     return min(a[0], a[-1])


    sumA = sum(a)
    sumB = sum(b)
    la, ra = calculate_left_right_sum(a)
    lb, rb = calculate_left_right_sum(b)
    minV = 10**12
    for i in range(p+1):
        j = p-i
        # minV = min(minV, sum(a[i:len(a)-j]) + sum(b[i:len(b)-j]))
        if i-1 < 0:
            minV = min(minV, sumA-ra[j-1] + sumB-rb[j-1])
            # print('sss', sumA-ra[j-1] + sumB-rb[j-1])
        elif j-1 < 0:
            minV = min(minV, sumA-la[i-1] + sumB-lb[i-1] )
            # print('sss', sumA-la[i-1] + sumB-lb[i-1])
        else:
            minV = min(minV, sumA-la[i-1]-ra[j-1] + sumB-lb[i-1]-rb[j-1])
            print('sss', la[i-1], ra[j-1], lb[i-1], rb[j-1], sumA-la[i-1]-ra[j-1] + sumB-lb[i-1]-rb[j-1])
        print(minV, i, j)
    return minV

def main():
    t = int(sys.stdin.readline().strip())
    for tt in range(t):
        n, p = map(int, sys.stdin.readline().strip().split(' '))
        s = sys.stdin.readline().strip()

        sss = ''
        a = []
        b = []
        c = 1
        t = s[0]
        for i in range(1, len(s)):
            if s[i] != t:
                if t == '1':
                    b.append(c)
                else:
                    a.append(c)
                sss += t
                t = s[i]
                c = 1
            else:
                c += 1
        if s[-1] == '0': sss += '0'
        else: sss += '1'
        
        if s[0] == '0': a = a[1:]
        else: b = b[1:]
        print(s)
        print(sss)
        print('a', a, len(a))
        print('b', b, len(b))

        for i in range(len(a)):
            for j in range(i, len(a)):
                x = sum(a[i:j+1]) + sum(b[i:j+1])
                if x == 27: print(i, j, x, 'rrrrr')


        print(tt, solve(a,b,p))

main()
# print(flip_s('1011110010000000010100010001010000101001001011100001111101111100000010001001001010110010011100011010'))
