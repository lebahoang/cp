import random

case = 1
r = 3000
c = 3000
print(case)
print(r, c)
for i in range(r):
    t = []
    for j in range(c):
        x = random.randint(0, 2)
        if x == 0:
            t.append(".")
        elif x == 1:
            t.append("^")
        else:
            t.append(".")
    print("".join(t))
