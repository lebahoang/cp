#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <map>
#include <stack>
#include <queue>
#include <vector>
#include <utility>

using namespace std;
#define M 1000000007
#define ll long long
#define fo(i,a,n) for(ll i=a;i<n;i++)
 
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	ll t,n,i,j,ans,q;
	cin>>t;
	while(t--){
        cin>>n;
        ll a[n+1],pref[n+1];
        for(ll i=1;i<=n;i++)
        cin>>a[i];
        ll f=0,in,sum=0;
        for(ll i=1;i<=n;i++) {
            if(a[i]==1 && i==1){ // f=1 for 1 at start
                f=1;break;
            }
            else if(a[i]==1 && i==n){ // f=0 for no 1 or 1 at end
                f=0;break;
            }
            else if(a[i]==1){ // f=2 for 1 at mid
                f=2;
                in=i; break;
            }
        }
    
        pref[0]=0;
        if(!f) {                    // No 1 or 1 at end
            fo(i,1,n)
            pref[i]=(pref[i-1]+((a[i]&1)?(a[i]-1):a[i]))%M;
            if(a[n]&1)
                pref[n]=(pref[n-1]+a[n])%M;
            else
                pref[n]=(pref[n-1]+a[n]-1)%M;
            pref[0]=pref[n];
        }
        else if(f==2){                 // 1 at mid
            fo(i,1,n){
                if(i==in){
                    pref[i]=pref[i-1];
                    continue;
                }
                if(i+1==in)
                    pref[i]=(pref[i-1]+((a[i]&1)?(a[i]):(a[i]-1)))%M;
                else
                    pref[i]=(pref[i-1]+((a[i]&1)?(a[i]-1):a[i]))%M;
            }
            if(a[n]&1)
                pref[n]=(pref[n-1]+a[n])%M;
            else
                pref[n]=(pref[n-1]+a[n]-1)%M;
            pref[0]=pref[n];
        }
    
        cin>>q;
        while(q--){
            ll r;
            cin>>r;
    
            if(f==1) {                               // 1 at start
                ans=(r/n)%M;
                if(r%n)
                ans++;
                if(r!=1 && r%(n)==1)
                ans--;
                cout<<ans%M<<endl;
                continue;
            }
            // else
            ans=(((r/n)%M)*(pref[n]%M))%M;
            if(r%n!=0)
            ans=(ans+pref[r%(n)])%M;
    
            if(!f) {                                     // No 1 or 1 at end
                if(r%(n)!=0 && (a[r%(n)]&1))
                ans++;
                if(r%n==0 && (a[n]%2==0))
                ans++;
                cout<<ans%M<<endl;
                continue;
            }
    
            if(f==2) {                                   // 1 at mid
                if(r%(n)!=0 && r%n!=in-1 && r%n!=in && (a[r%(n)]&1) )
                ans++;
                if(r%n==0 && (a[n]%2==0))
                ans++;
                if(r%n==in-1 && a[r%n]%2==0)
                ans++;
                if(r%n==in && a[in-1]%2==0)
                ans+=2;
                cout<<ans%M<<endl;
                continue;
            }
        }
	}
}