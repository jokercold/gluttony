#include<iostream>
#include<cstdio>
using namespace std;
#define ll long long
ll p;
ll power(ll x,ll y){
  ll t=1;
	while (y){
	  if (y&1) t=t*x%p;
    x=x*x%p;
		y>>=1;
	}
	return t;
}
int main(){
	ll n,k,m;
  scanf("%lld%lld%lld%lld",&n,&k,&m,&p);
	m=m%p;
	ll ans=(n%p*power(m,k-1)%p-(k-1)%p*power(m,k-2)%p*((m*(m+1)/2)%p)%p+p)%p;
	printf("%lld\n",ans);
	return 0;
}
