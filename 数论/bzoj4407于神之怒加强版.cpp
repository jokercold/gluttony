#include<iostream>
#include<cstdio>
using namespace std;
#define ll long long
#define M 1000000007
#define N 5000000
bool visit[N+10];
int prime[N];
ll h[N+10],sum[N+10];
int K;
ll power(ll x,int y){
  ll t=1;
	while (y){
	  if (y&1) t=t*x%M;
		x=x*x%M;
		y>>=1;
	}
	return t;
}
void pre(){
  visit[1]=h[1]=1;
	int num=0;
	for (int i=2;i<=N;++i){
	  if (!visit[i]) prime[++num]=i,h[i]=(power(i,K)-1+M)%M;
		for (int j=1;j<=num;++j){
		  if ((ll)i*prime[j]>N) break;
			visit[i*prime[j]]=true;
			if (i%prime[j]){
			  h[i*prime[j]]=h[prime[j]]*h[i]%M;
			}else{
			  h[i*prime[j]]=(h[prime[j]]+1)%M*h[i]%M;
				break;
			}
		}
	}
	for (int i=1;i<=N;++i) sum[i]=(sum[i-1]+h[i])%M;
}
int main(){
  int T;
	scanf("%d%d",&T,&K);
	pre();
	while (T--){
	  int n,m;
		scanf("%d%d",&n,&m);
		if (n>m) swap(n,m);
	  int j=0;
		ll ans=0;
		for (int i=1;i<=n;i=j+1){
		  j=min(n/(n/i),m/(m/i));
			ans=(ans+(sum[j]-sum[i-1]+M)%M*(n/i)%M*(m/i)%M)%M;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
