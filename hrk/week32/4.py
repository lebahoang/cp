import sys

def getFactorize(primes, number):
  x = number
  i = 0
  rs = 1
  while x > 1:
    while i < len(primes):
      if x%primes[i] == 0:
        break
      i += 1
    if i < len(primes):
      count = 0
      while x%primes[i] == 0:
        x = x/primes[i]
        count += 1
      if count%2 == 1:
        rs = rs * primes[i]
    else:
      break

  return rs*x

primes = [2,3,5,7,11,  13,  17,  19,  23,
29,  31,  37,  41,  43,  47,  53,  59,  61,  67,
71,  73,  79,  83,  89,  97,  101,   103,   107,   109,
113,   127,   131,   137,   139,   149,   151,   157,   163,   167,
173,   179,   181,   191,   193,   197,   199,   211,   223,   227,
229,   233,   239,   241,   251,   257,   263,   269,   271,   277,
281,   283,   293,   307,   311,   313,   317,   331,   337,   347,
349,   353,   359,   367,   373,   379,   383,   389,   397,   401,
409,   419,   421,   431,   433,   439,   443,   449,   457,   461,
463,   467,   479,   487,   491,   499,   503,   509,   521,   523,
541,   547,   557,   563,   569,   571,   577,   587,   593,   599,
601,   607,   613,   617,   619,   631,   641,   643,   647,   653,
659,   661,   673,   677,   683,   691,   701,   709]



n = int(sys.stdin.readline())
string = sys.stdin.readline().strip()
b = []
c = []
for i, s in enumerate(string):
  if s == 'b':
    b.append(i+1)
  elif s == 'c':
    c.append(i+1)

b = set(b)
c = set(c)
#print(b)
#print('------')
ans = 0
h = {}
for i, s in enumerate(string):
  #if i > 10000: break
  if s == 'a':
    multiple = getFactorize(primes, i+1)
    #print(i+1, multiple)
    for j in xrange(1, n):
      tt = multiple * (j**2)
      if tt > n: break
      if tt in c:
        m = int( (tt * (i+1))**0.5 )
        if m in b:
          #print(m, (i+1), tt)
          ans += 1
print(ans)

  