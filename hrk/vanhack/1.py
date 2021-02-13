
def get_exact(date):
    import json
    import urllib.request as request
    strDateArr = '{:%d-%B-%Y}'.format(date).split('-')
    x = '{:%d-%B-%Y}'.format(date)
    if strDateArr[0][0] == '0':
        x = x[1:]
    contents = request.urlopen('https://jsonmock.hackerrank.com/api/stocks/?date={}'.
                format(x)).read()
    contents = json.loads(contents)
    total_pages = int(contents['total_pages'])
    i = 1
    rs = {}
    while i <= total_pages:
        contents = request.urlopen('https://jsonmock.hackerrank.com/api/stocks/?date={}&page={:d}'.
                format(x, i)).read()
        contents = json.loads(contents)
        data = contents['data']
        for d in data:
            # print('{} {} {}'.format(d['date'], d['open'], d['close']))
            t = '{} {} {}'.format(d['date'], d['open'], d['close'])
            if t not in rs:
                rs[t] = 1
        i += 1
    return rs

def foo2(firstDate, lastDate, weekDay):
    import datetime
    weekDays = ['Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday', 'Sunday']
    s = datetime.datetime.strptime(firstDate, '%d-%B-%Y')
    e = datetime.datetime.strptime(lastDate, '%d-%B-%Y')
    while s <= e:
        if weekDays[s.weekday()] == weekDay:
            rs1 = get_exact(s)
            for k in rs1.keys():
                print(k)
        s += datetime.timedelta(days=1)

def foo1(f):
    def g(*args):
        if len(args) == 2 and isinstance(args[0], int) and isinstance(args[1], int):
            return f(args[1], args[0])

        sep = args[0]
        strs = args[1:]
        frs = f(sep, *strs)
        if len(frs.split(sep)) == len(strs):
            return f(sep, *strs[::-1])
        else:
            return f(*args[::-1])
    return g

def go(i, magic, dist):
    energy = magic[i]
    s = i
    e = i-1
    if i == 0:
        e = len(magic)-1
    while s != e:
        if energy < dist[s]:
            return s+1, False
        if s+1 == len(magic):
            t = 0
        else:
            t = s+1
        energy += magic[t]-dist[s]
        s = t
    return e, True


def foo3(magic, dist):
    n = len(magic)
    i = 0
    while True:
        next_i, finished = go(i, magic, dist)
        if finished:
            return i
        if next_i < i:
            break
        i = next_i
    return -1


if __name__ == '__main__':
    # foo2('1-January-2000',  '22-February-2000', 'Monday')
    int_func_map = {
        'pow': pow,
        'cmp': lambda a, b: 0 if a == b else [1, -1][a < b],
    }

    string_func_map = {
        'join_with': lambda separator, *args: separator.join(args),
        # 'join_with': lambda separator, *args: print(args),
        'capitalize_first_and_join': lambda first, *args: ''.join([first.upper()] + list(args)),
    }

    args = [2,3]
    print(foo1(int_func_map['pow'])(*args))
    print(foo1(int_func_map['cmp'])(*args))
    args = [',', 'a', 'b', 'c', 'd']
    print(foo1(string_func_map['join_with'])(*args))
    print(foo1(string_func_map['capitalize_first_and_join'])(*args))

