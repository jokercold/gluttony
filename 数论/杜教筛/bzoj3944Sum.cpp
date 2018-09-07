#include<iostream>
#include<cstdio>
#include<map>
using namespace std;
#define N 2500000
#define M 2500010
#define ll long long
struct node{ll phi,mu;};
map <ll,ll> Phi,Mu;
ll phi[M],mu[M];
int prime[M];
bool visit[M];
void pre(){
  visit[1]=phi[1]=mu[1]=1;
	int num=0;
	for (int i=2;i<=N;++i){
		if (!visit[i]){
		  phi[i]=i-1;
			mu[i]=-1;
			prime[++num]=i;
		}
    for (int j=1;j<=num;++j){
		  if ((ll)i*prime[j]>N) break;
			visit[i*prime[j]]=true;
			if (i%prime[j]){
			  phi[i*prime[j]]=phi[i]*phi[prime[j]];
				mu[i*prime[j]]=-mu[i];
			}else{
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
		}
	}
	for (int i=2;i<=N;++i) phi[i]+=phi[i-1],mu[i]+=mu[i-1];
	return;
}
node DU(ll n){
  if (n<=N) return (node){phi[n],mu[n]};
	if (Phi[n]) return (node){Phi[n],Mu[n]};
	ll ans1=n*(n+1)>>1,ans2=1,pos=0;
	for (ll i=2;i<=n;i=pos+1){
	  pos=n/(n/i);
		node res=DU(n/i);
		ans1-=(pos-i+1)*res.phi;
    ans2-=(pos-i+1)*res.mu;
	}
	Phi[n]=ans1;Mu[n]=ans2;
	return (node){ans1,ans2};
}
void solve(){
  ll n;
	scanf("%lld",&n);
	node ans=DU(n);
	printf("%lld %lld\n",ans.phi,ans.mu);
}
int main(){
  pre();
	int T;
	scanf("%d",&T);
	while (T--){
	  solve();
	}
	return 0;
}
