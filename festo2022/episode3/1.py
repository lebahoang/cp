import math
import re
from traceback import print_tb

from numpy import sort

def dist(a, b):
    return (a[0]-b[0])**2 + (a[1]-b[1])**2
class Person:
    def __init__(self, name, id, home, blood_sample):
        self.name = name
        self.id = int(id)
        self.home = home
        self.blood_sample = blood_sample[1:]
        self.pattern = ['pic', 'opi', 'cop', 'ico']
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
    def _dfs(self, pattern, n, m, i, j, visited, s, cur_pattern, rs):
        if len(s) == 3:
            rs.append(cur_pattern[:])
            return
        visited[i][j] = True
        coords = [(0,-1), (0,1), (-1,0), (1,0)]
        for c in coords:
            ii = i+c[0]
            jj = j+c[1]
            if ii >= 0 and jj >= 0 and ii < n and jj < m and not visited[ii][jj]:
                if self.blood_sample[ii][jj] == pattern[len(s)]:
                    cur_pattern.append((ii, jj))
                    self._dfs(pattern, n, m, ii, jj, visited, s+self.blood_sample[ii][jj], cur_pattern, rs)
                    cur_pattern.pop(-1)
        visited[i][j] = False
    def _detect_a_pico_bot_pattern(self, pattern, rs):
        n = len(self.blood_sample)
        m = len(self.blood_sample[0])
        for i in range(n):
            for j in range(m):
                if self.blood_sample[i][j] == pattern[0]:
                    visited = [[False for j in range(m)] for i in range(n)]
                    if self._dfs(pattern, n, m, i, j, visited, pattern[0], [(i,j)], rs):
                        return True
        return False
    def check_one_seq(self, seqs):
        d = {}
        for s in seqs:
            for p in s:
                if p not in d:
                    d[p] = 1
                else:
                    return False
        return True
    def check(self, seqs, cur_seq):
        if len(cur_seq) == 4:
            if self.check_one_seq(cur_seq):
                return True
            return False
        
        for s in seqs[len(cur_seq)]:
            cur_seq.append(s)
            if self.check(seqs, cur_seq):
                return True
            cur_seq.pop(-1)
        return False
    def is_pico_bot(self):
        n = len(self.blood_sample)
        m = len(self.blood_sample[0])
            
        rs = [[] for _ in range(len(self.pattern))]
        for i, p in enumerate(self.pattern):
            self._detect_a_pico_bot_pattern(p, rs[i])
        
        for p in rs:
            if len(p) == 0:
                return False
        if self.check(rs, []):
            return True

        return False
    def _get_time_minutes(self, x):
        arr = x.split(':')
        return int(arr[0]) * 60 + int(arr[1])
    def _find_moment(self, start, end):
        print(self.visited)
        l = len(self.visited)//2
        if self._get_time_minutes(self.visited[0][0]) >= end:
            return '11:00', ''
        elif self._get_time_minutes(self.visited[2*(l-1)][0]) <= start:
            return '11:00', ''
        for i in range(l):
            x = 2*i+1
            y = 2*(i+1)
            print(i, x,y)
            xt = self._get_time_minutes(self.visited[x][0])
            yt = self._get_time_minutes(self.visited[y][0])
            if xt <= end and yt > end:
                return self.visited[x][0], self.visited[x][1]
        return '', ''
    def is_not_alibi(self, travel_time_dict):
        self.visited = sorted(self.visited)
        start = self._get_time_minutes('11:00')
        end = self._get_time_minutes('13:00')
        


def load_dbs():
    db = open('./population.txt')
    securitydb = open('./security_log.txt')
    travel_time_db = open('./travel_times.txt')
    ps = []
    dps = {}
    travel_time = {}
    for line in travel_time_db.readlines():
        line = line.strip()
        if line == '': continue
        arr = line.split(':')
        travel_time[arr[0].strip()] = int(arr[1].strip())
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
    return ps, dps, travel_time

ps, dps, travel_time = load_dbs()
s = 0
cnt1 = 0
for p in ps:
    # if p.is_pico_bot():
    #     s += p.id
    #     cnt1 += 1
    if p.is_not_alibi(travel_time):
        s += p.id
        cnt1 += 1
print(s, cnt1, travel_time)


