#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
#define ll long long
int m;
ll phi(ll x){
  ll num=x;
	for (int i=2;i<=m;++i)
	if (x%i==0){
	  num=num*(i-1)/i;
		while (x%i==0) x/=i;
	}
	if (x>1) num=num*(x-1)/x;
	return num;
}
int main(){
	ll n;
	scanf("%lld",&n);
	m=sqrt(n);
	ll ans=0;
	for (int i=1;i<=m;++i)
	if (n%i==0){
		ans+=(ll)i*phi(n/i);
		if (i*i<n) ans+=(ll)(n/i)*phi(i);
	}
	printf("%lld\n",ans);
  return 0;
}
