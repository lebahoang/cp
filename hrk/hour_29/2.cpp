#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <utility>

using namespace std;
const int NNodes = 1e6 + 9;

int p[NNodes];
int rankAtNode[NNodes];

void initDisjoinSet(int n) {
    for (int i = 0; i < n; i++) {
        p[i] = i;
        rankAtNode[i] = 0;
    }
}

int findSubset(int x) {
    // apply path compression
    // which is the idea: moving the sub tree rooted at x to be a child of root node
    if (x == p[x]) {
        return x;
    }
    p[x] = findSubset(p[x]);
    return p[x];
}

void union2Subsets(int x, int y) {
    // apply union by rank
    // which is the idea: attach the smaller depth tree into the bigger depth tree
    // more specifically the root node of smaller tree will become a child of the root node
    // of bigger tree
    int xroot = findSubset(x);
    int yroot = findSubset(y);
    if (xroot == yroot) {
        return;
    }
    if (rankAtNode[xroot] >= rankAtNode[yroot]) {
        p[yroot] = xroot;
        if (rankAtNode[xroot] == rankAtNode[yroot] ) {
            rankAtNode[xroot]++;
        }
    } else if (rankAtNode[xroot] < rankAtNode[yroot]) {
        p[xroot] = yroot;
    }
}

const int MAXN = 1e6 + 6;
// stores smallest prime factor for every number 
int spf[MAXN]; 
  
// Calculating SPF (Smallest Prime Factor) for every 
// number till MAXN. 
// Time Complexity : O(nloglogn) 
void sieve() 
{ 
    spf[1] = 1; 
    for (int i=2; i<MAXN; i++) 
  
        // marking smallest prime factor for every 
        // number to be itself. 
        spf[i] = i; 
  
    // separately marking spf for every even 
    // number as 2 
    for (int i=4; i<MAXN; i+=2) 
        spf[i] = 2; 
  
    for (int i=3; i*i<MAXN; i++) 
    { 
        // checking if i is prime 
        if (spf[i] == i) 
        { 
            // marking SPF for all numbers divisible by i 
            for (int j=i*i; j<MAXN; j+=i) 
  
                // marking spf[j] if it is not  
                // previously marked 
                if (spf[j]==j) 
                    spf[j] = i; 
        } 
    } 
} 
  
// A O(log n) function returning primefactorization 
// by dividing by smallest prime factor at every step 
vector<int> getFactorization(int x)
{
    vector<int> ret;
    while (x != 1)
    {
        ret.push_back(spf[x]);
        x = x / spf[x];
    }
    return ret;
}

vector<int> getPrimeFactors(vector<int> primes) {
    vector<int> rs;
    rs.push_back(primes[0]);
    for (int i = 1; i < primes.size(); i++) {
        if (primes[i] != primes[i-1]) {
            rs.push_back(primes[i]);
        }
    }
    return rs;
}


int power(int a, int b, int mod) {
    int res = 1;
    while( b ) {
        if( b & 1 ) {
            res = 1ll * res * a % mod;
        }
        a = 1ll * a * a % mod;
        b /= 2;
    }
    return res;
}

long long mod = 1e9 + 7;
int n;
int hasOne;
int arr[NNodes];
unordered_map<int, bool> mapPrimes;
unordered_map<int, bool> mapSets;
int main() {
    // precalculating Smallest Prime Factor 
    sieve();
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        cin >> n;
        initDisjoinSet(NNodes);
        mapPrimes.clear();
        mapSets.clear();
        hasOne = 0;
        for (int j = 0; j < n; j++) {
            cin >> arr[j];
            if (arr[j] == 1) {
                hasOne++;
                continue;
            }
            vector<int> primes = getPrimeFactors(getFactorization(arr[j]));
            // printf("%d\n", primes[0]);
            mapPrimes[primes[0]] = true;
            for (int k = 1; k < primes.size(); k++) {
                mapPrimes[primes[k]] = true;
                union2Subsets(primes[0], primes[k]);
            }
        }
        int count = 0;
        unordered_map<int, bool>::iterator iter;
        for (iter = mapPrimes.begin(); iter != mapPrimes.end(); iter++) {
            int a = iter->first;
            int b = findSubset(a);
            if (mapSets.find(b) == mapSets.end()) {
                mapSets[b] = true;
                count++;
            }
        }
        int rs;
        if (hasOne > 0) {
            rs = (power(2, count, mod) * power(2, hasOne, mod) - 2) % mod;
        } else {
            rs = (power(2, count, mod) - 2) % mod;
        }
        cout << rs << "\n";
    }  
    return 0;
}