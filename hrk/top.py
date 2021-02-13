# import sys

# def count(a):
#   x = y = z = 0
#   for i in a:
#       if i == 'a':
#           x += 1
#       elif i == 'b':
#           y += 1
#       elif i == 'c':
#           z += 1
#   return (x,y,z)

# def getSignature(a):
#   x = y = z = 0
#   for i in a:
#       if i == 'a':
#           x += 1
#       elif i == 'b':
#           y += 1
#       elif i == 'c':
#           z += 1
#   #return (x,y,z)
#   return x*10 + y*10**2 + z*10**3


# t = int(sys.stdin.readline().strip())
# for _ in range(t):
#   a = sys.stdin.readline().strip()
#   x,y,z = count(a)
#   #print('sss',x,y,z)
#   if x+y+z == x or  x+y+z == y or  x+y+z == z:
#       print(len(a))
#   else:
#       if (x%2 == 1 and y%2 == 1 and z%2 == 1) or (x%2 == 0 and y%2 == 0 and z%2 == 0):
#           print(2)
#       else:
#

# import itertools
# a = list(itertools.permutations([1, 2, 3, 4, 5, 6, 7, 8, 9, 10]))
# a = list(itertools.permutations([1, 2, 3, 4, 5]))
# for i in a:
# 	print(i)
import random
tc = 30
n = 10
print(tc)
for _ in range(tc):
	print(n, n)
	for _ in range(2):
		for i in range(n):
			x = []
			for j in range(n):
				x.append(str(random.randint(1, 1000)))
			print(' '.join(x))



