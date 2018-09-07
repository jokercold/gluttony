#include<stdio.h>
#include<cmath>
#define N 50000
#define ll long long 
using namespace std;
inline int read(){
  ll x=0,f=1;char ch=getchar();
  while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
  while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
  return x*f;
}
int T;
bool visit[N+10];
int mu[N+10],prime[N+10];
void pre(){
  visit[1]=mu[1]=1;
	int num=0;
	for (int i=1;i<=N;++i){
	  if (!visit[i]) prime[++num]=i,mu[i]=-1;
		for (int j=1;j<=num;++j){
		  if ((ll)i*prime[j]>N) break;
			visit[i*prime[j]]=true;
			if (i%prime[j]) mu[i*prime[j]]=-mu[i];
			else break;
		}
	}
}
inline int check(int x){
  ll sum=0;
  int t=sqrt(x);
  for(int i=1;i<=t;i++) sum+=(ll)x/(i*i)*mu[i];
  return sum;
}
int main(){
  pre();
  T=read();
  while(T--){
		int K;
		K=read();
		int l=K,r=1644934081,ans;
		while(l<=r){
			int mid=((ll)l+r)>>1;
			if(check(mid)>=K)ans=mid,r=mid-1;
			else l=mid+1;
		}
		printf("%d\n",ans);
  }
  return 0;
}
