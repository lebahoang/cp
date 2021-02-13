import sys

s,t = map(int, sys.stdin.readline().strip().split())
a,b = map(int, sys.stdin.readline().strip().split())
m,n = map(int, sys.stdin.readline().strip().split())
apple = map(int, sys.stdin.readline().strip().split())
orange = map(int, sys.stdin.readline().strip().split())

x = 0
y = 0
for d in apple:
  if a + d >= s and a + d <= t:
    x += 1
for d in orange:
  if b + d >= s and b + d <= t:
    y += 1
print x
print y