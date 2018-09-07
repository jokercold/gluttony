#include<iostream>
#include<cstdio>
using namespace std;
#define M 20101009
#define ll long long
int n,m;
int prime[10001000];
ll F[10001000],S[10001000];
bool visit[10001000];
void pre(){
  visit[1]=1;
	F[1]=1;
	int num=0;
	for (int i=1;i<=m;++i){
	  if (!visit[i]) prime[++num]=i,F[i]=(-i+1+M)%M;
		for (int j=1;j<=num;++j){
		  if ((ll)i*prime[j]>m) break;
			visit[i*prime[j]]=true;
			if (i%prime[j]) F[i*prime[j]]=F[i]*F[prime[j]]%M;
			else{
			  F[i*prime[j]]=F[i];
				break;
			}
		}
	}
	S[0]=0;
  for (int i=1;i<=m;++i) F[i]=(F[i]*i%M+F[i-1])%M,S[i]=(S[i-1]+i)%M;
}
void solve(){
  int j=0;
	ll ans=0;
	for (int i=1;i<=n;i=j+1){
	  j=min(m/(m/i),n/(n/i));
		ans=(ans+(F[j]-F[i-1]+M)%M*S[n/i]%M*S[m/i]%M)%M;
	}
	printf("%lld\n",ans);
}
int main(){
	scanf("%d%d",&n,&m);
	if (n>m) swap(n,m);
 	pre();
	solve();	
	return 0;
}

