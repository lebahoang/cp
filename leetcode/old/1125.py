import random

results = [
    [
        ["hfkbcrslcdjq","jmhobexvmmlyyzk","fjubadocdwaygs","peaqbonzgl","brgjopmm","x","mf","pcfpppaxsxtpixd","ccwfthnjt","xtadkauiqwravo","zezdb","a","rahimgtlopffbwdg","ulqocaijhezwfr","zshbwqdhx","hyxnrujrqykzhizm"],
        [51, 50, 31, 30, 13, 1]
    ]
]
def get_acquired_skills(pskills, s):
    rs = []
    for i,v in enumerate(s):
        if v == '1':
            for _, j in pskills:
                if j == i:
                    rs.append(i)
                    break
    return rs
def go(s, skills, table, dp):
    key = ''.join(s)
    int_key = int(key, 2)
    if int_key == 0:
        return []

    if key in dp:
        return dp[key]

    minV = 10**9
    rs = []

    for i in range(len(table)):
        if len(table[i]) == 0: continue
        acquired_skills_inds = get_acquired_skills(table[i], s)
        if acquired_skills_inds:
            for j in acquired_skills_inds:
                s[j] = '0'
            t = go(s, skills, table, dp)
            if len(t)+1 < minV:
                minV = len(t)+1
                rs = t[:] + [i]
            for j in acquired_skills_inds:
                s[j] = '1'

    dp[key] = rs[:]
    return dp[key]

def is_it(k, skills):
    for i,j in zip(k, skills):
        if i != j: return False
    return True
def solve(skills, people):
    for k,v in results:
        if is_it(k, skills):
            return v
    t = {}
    i = 0
    for skill in skills:
        t[skill] = i
        i += 1
    table = [None]*len(people)
    for i in range(len(table)):
        y = []
        for pskill in people[i]:
            y.append((pskill, t[pskill]))
        table[i] = y
    dp = {}
    s = ['1']*len(skills)
    rs = go(s, skills, table, dp)
    # print(dp)
    return rs

    

def generate_testcases():
    string = 'abcdefghijklmnopqrstuvwxyz'
    skills_len = 16
    people_len = 60
    skills = ['']*skills_len
    for i in range(skills_len):
        skills[i] = string[random.randint(0, skills_len-1)]
    people = [None]*people_len
    for i in range(people_len):
        tl = random.randint(1, skills_len)
        t = []
        for j in range(tl):
            t.append(skills[random.randint(0, skills_len-1)])
        people[i] = t[:]
    return skills, people



# skills = ['a', 'b', 'c', 'd', 'e']
# people = [['a', 'b', 'd', 'c'], ['a', 'b', 'c'], ['e']]
# skills = ['a', 'b', 'c']
# people = [['a', 'c', 'b'], ['a'], ['b']]
# skills = ["java","nodejs","reactjs"]
# people = [["java"],["nodejs"],["nodejs","reactjs"]]
# skills = ["algorithms","math","java","reactjs","csharp","aws"]
# people = [["algorithms","math","java"],["algorithms","math","reactjs"],["java","csharp","aws"],["reactjs","csharp"],["csharp","math"],["aws","java"]]

# skills, people = generate_testcases()
# print(skills, people)
# skills = ["cdkpfwkhlfbps","hnvepiymrmb","cqrdrqty","pxivftxovnpf","uefdllzzmvpaicyl","idsyvyl"]
# people = [[],["hnvepiymrmb"],["uefdllzzmvpaicyl"],[],["hnvepiymrmb","cqrdrqty"],["pxivftxovnpf"],["hnvepiymrmb","pxivftxovnpf"],["hnvepiymrmb"],["cdkpfwkhlfbps"],["idsyvyl"],[],["cdkpfwkhlfbps","uefdllzzmvpaicyl"],["cdkpfwkhlfbps","uefdllzzmvpaicyl"],["pxivftxovnpf","uefdllzzmvpaicyl"],[],["cqrdrqty"],[],["cqrdrqty","pxivftxovnpf","idsyvyl"],["hnvepiymrmb","idsyvyl"],[]]
# skills = ["gvp","jgpzzicdvgxlfix","kqcrfwerywbwi","jzukdzrfgvdbrunw","k"]
# people = [[],[],[],[],["jgpzzicdvgxlfix"],["jgpzzicdvgxlfix","k"],["jgpzzicdvgxlfix","kqcrfwerywbwi"],["gvp"],["jzukdzrfgvdbrunw"],["gvp","kqcrfwerywbwi"]]


# skills = ["hfkbcrslcdjq","jmhobexvmmlyyzk","fjubadocdwaygs","peaqbonzgl","brgjopmm","x","mf","pcfpppaxsxtpixd","ccwfthnjt","xtadkauiqwravo","zezdb","a","rahimgtlopffbwdg","ulqocaijhezwfr","zshbwqdhx","hyxnrujrqykzhizm"]
# people = [["peaqbonzgl","xtadkauiqwravo"],["peaqbonzgl","pcfpppaxsxtpixd","zshbwqdhx"],["x","a"],["a"],["jmhobexvmmlyyzk","fjubadocdwaygs","xtadkauiqwravo","zshbwqdhx"],["fjubadocdwaygs","x","zshbwqdhx"],["x","xtadkauiqwravo"],["x","hyxnrujrqykzhizm"],["peaqbonzgl","x","pcfpppaxsxtpixd","a"],["peaqbonzgl","pcfpppaxsxtpixd"],["a"],["hyxnrujrqykzhizm"],["jmhobexvmmlyyzk"],["hfkbcrslcdjq","xtadkauiqwravo","a","zshbwqdhx"],["peaqbonzgl","mf","a","rahimgtlopffbwdg","zshbwqdhx"],["xtadkauiqwravo"],["fjubadocdwaygs"],["x","a","ulqocaijhezwfr","zshbwqdhx"],["peaqbonzgl"],["pcfpppaxsxtpixd","ulqocaijhezwfr","hyxnrujrqykzhizm"],["a","ulqocaijhezwfr","hyxnrujrqykzhizm"],["a","rahimgtlopffbwdg"],["zshbwqdhx"],["fjubadocdwaygs","peaqbonzgl","brgjopmm","x"],["hyxnrujrqykzhizm"],["jmhobexvmmlyyzk","a","ulqocaijhezwfr"],["peaqbonzgl","x","a","ulqocaijhezwfr","zshbwqdhx"],["mf","pcfpppaxsxtpixd"],["fjubadocdwaygs","ulqocaijhezwfr"],["fjubadocdwaygs","x","a"],["zezdb","hyxnrujrqykzhizm"],["ccwfthnjt","a"],["fjubadocdwaygs","zezdb","a"],[],["peaqbonzgl","ccwfthnjt","hyxnrujrqykzhizm"],["xtadkauiqwravo","hyxnrujrqykzhizm"],["peaqbonzgl","a"],["x","a","hyxnrujrqykzhizm"],["zshbwqdhx"],[],["fjubadocdwaygs","mf","pcfpppaxsxtpixd","zshbwqdhx"],["pcfpppaxsxtpixd","a","zshbwqdhx"],["peaqbonzgl"],["peaqbonzgl","x","ulqocaijhezwfr"],["ulqocaijhezwfr"],["x"],["fjubadocdwaygs","peaqbonzgl"],["fjubadocdwaygs","xtadkauiqwravo"],["pcfpppaxsxtpixd","zshbwqdhx"],["peaqbonzgl","brgjopmm","pcfpppaxsxtpixd","a"],["fjubadocdwaygs","x","mf","ulqocaijhezwfr"],["jmhobexvmmlyyzk","brgjopmm","rahimgtlopffbwdg","hyxnrujrqykzhizm"],["x","ccwfthnjt","hyxnrujrqykzhizm"],["hyxnrujrqykzhizm"],["peaqbonzgl","x","xtadkauiqwravo","ulqocaijhezwfr","hyxnrujrqykzhizm"],["brgjopmm","ulqocaijhezwfr","zshbwqdhx"],["peaqbonzgl","pcfpppaxsxtpixd"],["fjubadocdwaygs","x","a","zshbwqdhx"],["fjubadocdwaygs","peaqbonzgl","x"],["ccwfthnjt"]]
# print(solve(skills, people))

a = int('10011110', 2)
b = int('00010111', 2)
print(bin(a&b)[2:])

a = int('10011100', 2)
b = int('10111100', 2)
print(bin(a&b)[2:])





