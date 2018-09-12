#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<cstdlib>
using namespace std;
#define ll long long 
#define rep(i,a,b) for (int i=a;i<=b;++i)
long long pp=110119;
#define fi first
#define se second
pair<ll,ll>q[110];
ll dp[110][10];
ll b[210100],inv[210100];
ll mo(ll a,ll pp){if(a>=0 && a<pp)return a;a%=pp;if(a<0)a+=pp;return a;}
ll powmod(ll a,ll b,ll pp){ll ans=1;for(;b;b>>=1,a=mo(a*a,pp))if(b&1)ans=mo(ans*a,pp);return ans;}
ll C(ll n,ll m){
   if(n<m)return 0;
   if(!m||n==m)return 1;
   return b[n]*inv[n-m]%pp*inv[m]%pp;
}
ll lucas(ll n,ll m){
   if(!n)return 1;
   return C(n%pp,m%pp)*lucas(n/pp,m/pp)%pp;
}
ll work(ll n,ll m){
   if ((n+m-2)%3)return 0;
   ll t=(n+m-2)/3;
   if (1+t>n||1+t>m)return 0;
   ll x=n-1-t;
   ll y=m-1-t;
   return lucas(t,x);
}
int main(){
    b[0]=1;
    rep(i,1,pp)b[i]=b[i-1]*i%pp;
    rep(i,0,pp)inv[i]=powmod(b[i],pp-2,pp);
    ll n,m,k;
    int cas=0;
    while (scanf("%lld%lld%lld",&n,&m,&k)!=EOF){
          memset(dp,0,sizeof(dp));
          ++cas;
          rep(i,1,k)scanf("%lld%lld",&q[i].fi,&q[i].se);
          q[0].fi=q[0].se=1;
          sort(q,q+k+1);
          q[k+1].fi=n;
          q[k+1].se=m;
          dp[0][1]=1;
          rep(i,0,k)
            rep(j,0,1)
              rep(z,i+1,k+1)
                dp[z][j^1]=mo(dp[z][j^1]+dp[i][j]*work(q[z].fi-q[i].fi+1,q[z].se-q[i].se+1),pp);
          printf("Case #%d: %d\n",cas,mo(dp[k+1][0]-dp[k+1][1],pp));
    }
    return 0;
}
