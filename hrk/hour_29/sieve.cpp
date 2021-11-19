#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

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

int main() {
    // precalculating Smallest Prime Factor 
    sieve();
    int h = -1;
    vector<int> hh;
    for (int i = 2; i < 1e6+1; i++) {
        vector<int> v = getFactorization(i);
        int t = -1;
        int c = 0;
        for (int j = 0; j < v.size(); j++) {
            if (v[j] != t) {
                cout << v[j] << " ";
                t = v[j];
                c++;
            }   
        }
        if (h < c) {
            h = c;
            hh.resize(v.size());
            copy(v.begin(), v.end(), hh.begin());
        }
        cout << "\n";
    }
    cout << "Largest number of prime numbers is " << h << "\n";
    int t = -1;
    for (int j = 0; j < hh.size(); j++) {
        if (hh[j] != t) {
            cout << hh[j] << " ";
            t = hh[j];
        }   
    }
    cout << "\n";
    return 0;
}