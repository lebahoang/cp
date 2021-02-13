import sys
import random

n = 309
m = 300
print n,m
# print ' '.join(['5' for _ in xrange(m)])
# for i in xrange(n):
# 	s = []
# 	if i%2 == 0:
# 		for j in xrange(m):
# 			s.append('0')
# 	else:
# 		for j in xrange(m):
# 			s.append('1')
	
# 	print ' '.join(s)

for i in xrange(n):
	s = []
	for j in xrange(m):
		s.append('0')
	print ' '.join(s)