#include<iostream>
#include<cstdio>
using namespace std;
#define ll long long
#define N 50100
bool visit[N];
int mu[N],prime[N];
void pre(){
  visit[1]=mu[1]=1;
	int num=0;
	for (int i=2;i<=50000;++i){
	  if (!visit[i]){
		  prime[++num]=i;
			mu[i]=-1;
		}
		for (int j=1;j<=num;++j){
		  if (i*prime[j]>50000) break;
			visit[i*prime[j]]=true;
			if (i%prime[j]){
				mu[i*prime[j]]=-mu[i];
			}else break;
		}
	}	
	for (int i=2;i<=50000;++i) mu[i]=mu[i-1]+mu[i];
	return;
}
ll query(int n,int m,int k){
	if (n>m) swap(n,m);
  ll ans=0;
	int last=0;
	n/=k;m/=k;
	for (int i=1;i<=n;i=last+1){
	  last=min(n/(n/i),m/(m/i));
    ans+=(ll)(mu[last]-mu[i-1])*(n/i)*(m/i);
	}
	return ans;
}
int main(){
  pre();
	int n;
	scanf("%d",&n);
	for (int i=1;i<=n;++i){
	  int a,b,c,d,k;
		scanf("%d%d%d%d%d",&a,&b,&c,&d,&k);
    printf("%lld\n",query(b,d,k)-query(b,c-1,k)-query(a-1,d,k)+query(a-1,c-1,k));
	}
	return 0;
}
