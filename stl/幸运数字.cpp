#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<cstdlib>
using namespace std;
#define ll long long 
#define rep(i,a,b) for (int i=a;i<=b;++i)
ll a[5000],b[5000],ans,l,r;
int n,m;
void dfs1(ll x){
     if(x>r)return;
     if(x)a[++n]=x;
     dfs1(x*10+6);
     dfs1(x*10+8);
}
void dfs2(int k,ll x,int kk){
     if(k==m+1){
         if (x==1)return;
         ans+=(r/x-(l-1)/x)*kk;
         return; 
     }
     dfs2(k+1,x,kk);
     ll y=b[k];
     ll t=__gcd(y,x);
     if(x/t<=(long double)r/y) 
        dfs2(k+1,x/t*y,kk*(-1));
}
int main()
{
    n=0;
    scanf("%lld%lld",&l,&r);
    dfs1(0);
    sort(a+1,a+n+1);
    m=0;
    rep(i,1,n){
       int pf=0;
       rep(j,1,i-1)
          if (a[i]%a[j]==0) pf=1;
       if (!pf)b[++m]=a[i];
    }
    rep(i,1,m/2)
       swap(b[i],b[m-i+1]);
    dfs2(1,1,-1);
	printf("%lld\n",ans);
	//while (1);
	return 0;
}
