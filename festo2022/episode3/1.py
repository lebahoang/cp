import math
from traceback import print_tb

def dist(a, b):
    return (a[0]-b[0])**2 + (a[1]-b[1])**2
class Person:
    def __init__(self, name, id, home, blood_sample):
        self.name = name
        self.id = int(id)
        self.home = home
        self.blood_sample = blood_sample[1:]
        self.pattern = 'picoico'
        self.visited = []
    def get_strings(self, s):
        rs = []
        a = ''
        for i in range(len(s)):
            if s[i] == ' ':
                if a != '': rs.append(a)
                a = ''
            else:
                a += s[i]
        if a != '': rs.append(a)
        return rs
    def _dfs(self, n, m, i, j, visited, s):
        if len(s) == 7:
            return True
        visited[i][j] = True
        coords = [(0,-1), (0,1), (-1,0), (1,0)]
        for c in coords:
            ii = i+c[0]
            jj = j+c[1]
            if ii >= 0 and jj >= 0 and ii < n and jj < m and not visited[ii][jj]:
                if self.blood_sample[ii][jj] == self.pattern[len(s)]:
                    t = self._dfs(n, m, ii, jj, visited, s+self.blood_sample[ii][jj])
                    if t:
                        return t
        visited[i][j] = False
        return False
    def is_pico_bot(self):
        n = len(self.blood_sample)
        m = len(self.blood_sample[0])
        for i in range(n):
            for j in range(m):
                if self.blood_sample[i][j] == 'p':
                    visited = [[False for j in range(m)] for i in range(n)]
                    if self._dfs(n, m, i, j, visited, 'p'):
                        return True
        return False
    

def load_dbs():
    db = open('./population.txt')
    securitydb = open('./security_log.txt')
    ps = []
    dps = {}
    t = []
    bs_arr = []
    f = False
    for line in db.readlines():
        line = line.strip()
        if line == '': continue
        if line.find('Name') != -1:
            if t:
                name = t[0].split(':')[1].strip()
                id = t[1].split(':')[1].strip()
                home = t[2].split(':')[1].strip()
                person = Person(name, id, home, bs_arr)
                ps.append(person)
                dps[name] = person
            t = [line]
            bs_arr = []
            f = False
        else:
            if line == 'Blood Sample:':
                f = True
            if not f:
                t.append(line)
            else:
                bs_arr.append(line)
    assert len(t) > 0
    name = t[0].split(':')[1].strip()
    id = t[1].split(':')[1].strip()
    home = t[2].split(':')[1].strip()
    person = Person(name, id, home, bs_arr)
    ps.append(person)
    dps[name] = person

    str_places = []
    t = []
    for line in securitydb.readlines():
        line = line.strip()
        if line == '': continue
        if line.find('Place') != -1:
            if t: str_places.append(t)
            t = [line]
        else:
            t.append(line)
    str_places.append(t)
    assert len(str_places) == 12
    for place in str_places:
        place_name = place[0].split(':')[1].strip()
        for l in place[1:]:
            if l.find('in') == -1 and l.find('out') == -1:
                time_visit = l
            else:
                arr = l.split(':')
                in_or_out = arr[0].strip()
                person_names = arr[1].split(',')
                for person_name in person_names:
                    person_name = person_name.strip()
                    dps[person_name].visited.append([time_visit, place_name, in_or_out])
    return ps, dps

ps, dps = load_dbs()
s = 0
for p in ps:
    
print(s)


