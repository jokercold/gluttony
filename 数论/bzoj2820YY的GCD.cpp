#include<iostream>
#include<cstdio>
using namespace std;
#define ll long long
int prime[700000];
int mu[10000010],sum[10000010];
bool visit[10000010];
void pre(){
	visit[1]=mu[1]=1;
	int num=0;
  for (int i=2;i<=10000000;++i){
	  if (!visit[i]) prime[++num]=i,mu[i]=-1;
		for (int j=1;j<=num;++j){
		  if ((ll)i*prime[j]>10000000) break;
			visit[i*prime[j]]=true;
			if (i%prime[j]) mu[i*prime[j]]=-mu[i];
			else break;
		}
	}
	for (int i=1;i<=num;++i){
	  for (int j=1;(ll)j*prime[i]<=10000000;++j) sum[j*prime[i]]+=mu[j];
	}
	for (int i=1;i<=10000000;++i) sum[i]+=sum[i-1];
}
ll solve(int N,int M){
  if (N>M) swap(N,M);
	int j=0;
	ll ans=0;
	for (int i=1;i<=N;i=j+1){
	  j=min(N/(N/i),M/(M/i));
		ans+=(ll)(sum[j]-sum[i-1])*(N/i)*(M/i);
	}
	return ans;
}
int main(){
	pre();
	int T;
	scanf("%d",&T);
	while (T--){
		int N,M;
		scanf("%d%d",&N,&M);
		printf("%lld\n",solve(N,M));
	}
	return 0;
}
