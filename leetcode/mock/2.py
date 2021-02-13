def solve(s):
    s = s.replace(' ', '')
    f = []
    c = ''
    for i in s:
        if i == '-' or i == '+':
            f.append(c)
            f.append(i)
            c = ''
        else:
            c += i
    f.append(c)

    # print(f)
    rs = 0
    op1 = ''
    for ind, i in enumerate(f):
        if i == '+' or i == '-':
            op1 = i
        else:
            temp = -1
            if i.find('+') == -1 and i.find('-') == -1 and i.find('*') == -1 and i.find('/') == -1:
                temp = int(i)
            else:
                k = 1
                c = ''
                op = ''
                for j in i:
                    if j != '*' and j != '/': c += j
                    else:
                        k = int(c)
                        if op == '':
                            temp = k
                        elif op == '*':
                            temp *= k
                        else:
                            temp //= k
                        op = j
                        c = ''
                k = int(c)
                if op == '':
                    temp = k
                elif op == '*':
                    temp *= k
                else:
                    temp //= k
                # print(temp, 'ddd')
            if op1 == '':
                rs = temp
            elif op1 == '+':
                rs += temp
            else:
                rs -= temp
    return rs


print(solve("1*2-3/4+5*6-7*8+9/10"))
