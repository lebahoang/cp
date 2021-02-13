import sys

def format(string):
  d = {}
  for i in string:
    if i not in d: d[i] = 1
    else: d[i] += 1
  rs = []
  for k,v in d.items():
    if v%2 == 1:
      rs.append(k)
  return '^'.join(sorted(rs)) 

string = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'j']
#string = ['a', 'b', 'c']
# string = [1,2,3,4,5,6,7,8,9]
print 1, string
for count in xrange(20):
  t = []
  for i in xrange(len(string)):
    if i < len(string)-1:
      x = string[i] + string[i+1]
    else:
      x = string[i] + string[0]
    t.append(format(x))
    # if i < len(string)-1:
    #   x = string[i] ^ string[i+1]
    # else:
    #   x = string[i] ^ string[0]
    # t.append(x)
  string = t[:]
  print count+2, string