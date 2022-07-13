import math
from traceback import print_tb

def dist(a, b):
    return (a[0]-b[0])**2 + (a[1]-b[1])**2
def computeCenters(pa,pb,radius):
    # https://math.stackexchange.com/questions/496070/finding-the-equation-of-a-circle-given-two-points-and-the-radius
    p0 = (0.5*(pa[0]+pb[0]), 0.5*(pa[1]+pb[1]))
    v = (0.5*(pb[0]-pa[0]), 0.5*(pb[1]-pa[1]))
    v_perp = (-v[1],v[0])
    # normalise
    norm = math.sqrt(v_perp[0]**2 + v_perp[1]**2)
    v_pn = (v_perp[0]/norm, v_perp[1]/norm)        
    t = math.sqrt(radius**2 - (v[0]**2+v[1]**2))
    
    return (p0[0]+t*v_pn[0], p0[1]+t*v_pn[1]), (p0[0]-t*v_pn[0], p0[1]-t*v_pn[1])
class Person:
    def __init__(self, name, id, home, blood_sample):
        self.name = name
        self.id = int(id)
        self.home = home
        self.blood_sample = blood_sample[1:]
        self.pattern = ['pico','ocip']
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
    def is_pico_bot(self):
        n = len(self.blood_sample)
        m = len(self.blood_sample[0])
        for i in range(n):
            strs = self.get_strings(self.blood_sample[i])
            for s in strs:
                for pat in self.pattern:
                    if s.find(pat) != -1:
                        return True
        for j in range(m):
            t = ''
            for i in range(n):
                t += self.blood_sample[i][j]
            strs = self.get_strings(t)
            for s in strs:
                for pat in self.pattern:
                    if s.find(pat) != -1:
                        return True
        return False
    def sort_visited_places(self):
        self.visited = sorted(self.visited)
    def is_visit_only(self, orders):
        for p in self.visited:
            f = False
            for po in orders:
                if p[1] == po:
                    f = True
                    break
            if not f:
                return False
        return True
    def is_visited_in_order(self, orders):
        n = len(self.visited)
        if n != 9 and n != 10:
            return False
        elif n == 9:
            for i in range(4):
                if self.visited[2*i][1] != orders[i]:
                    return False
                if self.visited[2*i][2] != 'in' or self.visited[2*i+1][2] != 'out':
                    return False
            if self.visited[8][1] != orders[4] or self.visited[8][2] != 'in':
                return False
            return True
        else:
            for i in range(5):
                if self.visited[2*i][1] != orders[i] or self.visited[2*i+1][1] != orders[i]:
                    return False
                if self.visited[2*i][2] != 'in' or self.visited[2*i+1][2] != 'out':
                    return False
            return True

db = open('./population.txt')
gdb = open('./galaxy_map.txt')
securitydb = open('./security_log.txt')
placedb = open('./place_sequence.txt')
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

# pls = []
# for line in gdb.readlines():
#     arr = line.strip().split(': (')
#     pl = arr[0].strip()
#     x,y,z = arr[1].strip().split(',')
#     x = int(x.strip())
#     y = int(y.strip())
#     z = int(z[:-1].strip())
#     # pls.append([x,y,z,pl])
#     pls.append([y,z,pl])
# print(len(pls))
# pls = sorted(pls)
# for p in pls:
#     print('{:d} {:d}'.format(p[0], p[1]))

# r102 = 100.0
# four_r2 = 16.0 # (2r)^2
# n = len(pls)
# # pairwise
# for i in range(n):
#     for j in range(i+1,n):
#         if pls[i][0] == pls[j][0] and pls[i][1] == pls[j][1]:
#             continue
#         if dist(pls[i], pls[j]) <= four_r2:
#             outliers1 = []
#             outliers2 = []
#             c1, c2 = computeCenters(pls[i],pls[j],2.0)
#             for k in range(n):
#                 if k != i and k != j:
#                     if dist(pls[k], c1) >= r102:
#                         outliers1.append(pls[k])
#                     if dist(pls[k], c2) >= r102:
#                         outliers2.append(pls[k])
#             print(len(outliers1), len(outliers2))

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


cnt1 = 0
s2 = 0
orders = ['Junkyard', 'Pod Racing Track', 'Pod Racing Track', 'Palace', 'Factory']

jj = []
for name in dps.keys():
    p = dps[name]
    p.sort_visited_places()
    if len(p.visited) == 10:
        cnt1 += 1
    if p.is_visit_only(orders) and p.is_visited_in_order(orders):
        s2 += p.id
    if p.is_pico_bot() and p.is_visit_only(orders) and p.is_visited_in_order(orders):
        jj.append([p.name, p.home])

print(cnt1)
print(s2)
print(jj)







                                


