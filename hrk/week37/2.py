import sys

n = int(sys.stdin.readline())
total = 0
for _ in range(n):
	cmd, y = sys.stdin.readline().strip().split(' ')
	y = int(y)
	if y < 0: continue
	if cmd == 'set':
		if y > total:
			total = y
	else:
		total += y
print(total)
