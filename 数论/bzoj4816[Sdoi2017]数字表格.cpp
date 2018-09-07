#include<iostream>
#include<cstdio>
using namespace std;
#define ll long long
#define M 1000000007
int num;
#define N 1010000
int Nn[2000],Mm[2000];
int F[N],invF[N];
int prime[N],mu[N];
int f[N];
bool vis[N];
int nn;
inline int mi(int x,int y){
  ll ans=1;
	while (y){
		if (y&1) ans=ans*x%M;
		x=(ll)x*x%M;
		y>>=1;
	}
	return ans%M;
}
void makemu(){
  vis[1]=mu[1]=1;
	num=0;
	for (int i=2;i<=nn;++i){
	  if (!vis[i]) prime[++num]=i,mu[i]=-1;
		for (int j=1;j<=num;++j){
		  if ((ll)prime[j]*i>nn) break;
			vis[prime[j]*i]=true;
			if (i%prime[j]) mu[i*prime[j]]=-mu[i]; 
			else break;
		}
	}
}
void pre(){
  makemu();
	F[0]=F[1]=1;
	f[0]=0;f[1]=1;
	for (int i=2;i<=nn;++i) f[i]=(f[i-1]+f[i-2])%M;
	for (int i=2;i<=nn;++i){
		int invi=mi(f[i],M-2);
		for (int j=i;j<=nn;j+=i){
		  if (!F[j]) F[j]=1;
			if (mu[j/i]==-1) F[j]=(ll)F[j]*invi%M;
			if (mu[j/i]==1) F[j]=(ll)F[j]*f[i]%M;
		}
	}
  for (int i=1;i<=nn;++i) F[i]=(ll)F[i-1]*F[i]%M;
	invF[0]=1;
  for (int i=1;i<=nn;++i) invF[i]=mi(F[i],M-2);
}
int main(){
  int T;
	scanf("%d",&T);
	nn=0;
	for (int i=1;i<=T;++i){
	  scanf("%d%d",&Nn[i],&Mm[i]);
		if (Nn[i]>Mm[i]) swap(Nn[i],Mm[i]);
		nn=max(nn,Nn[i]);
	}
	pre();
	for (int cas=1;cas<=T;++cas){
	  int n=Nn[cas],m=Mm[cas];
		int last=0;
		int ans=1;
		for (int i=1;i<=n;i=last+1){
		  last=min(n/(n/i),m/(m/i));
			ans=(ll)ans*mi((ll)F[last]*invF[i-1]%M,(ll)(n/i)*(m/i)%(M-1))%M;
		}
		printf("%d\n",ans);
	}
	return 0;
}
