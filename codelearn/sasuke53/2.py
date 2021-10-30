import re
def filter(string):
    r = ''
    m = re.compile('[0-9a-zA-Z]')
    for x in string:
        if m.match(x):
            r += x
    # print(r)
    return r
def matter(s):
    arr = s.split('=')
    if len(arr) != 2:
        return ''
    a = arr[0].split('+')
    b = arr[1].split('+')
    for i in range(len(a)): a[i] = filter(a[i].strip())
    for i in range(len(b)): b[i] = filter(b[i].strip())
    if len(a) >= 2 and len(b) >= 2:
        return ''
    if len(a) <= 1 and len(b) <= 1:
        return ''
    if len(a) == 1:
        if a[0] != '':
            f = True
            for x in b:
                if x.strip() == '':
                    f = False
                    break
            if f: return 'Phan ung phan huy'
        return ''
    if len(b) == 1:
        if b[0] != '':
            f = True
            for x in a:
                if x.strip() == '':
                    f = False
                    break
            if f: return 'Phan ung hoa hop'
        return ''
    return ''


print(matter(' (a) + ()(a)v()() = c '))
print(matter(' a + b =  '))
print(matter(' + + + '))
print(matter(' + + + '))
print(matter(' + + + '))

