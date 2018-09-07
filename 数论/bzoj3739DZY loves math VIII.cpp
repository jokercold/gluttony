#include<iostream>
#include<cstdio>
using namespace std;
#define N 10000005
#define ll long long
int n,cnt,mu[N],prime[N],ask[1005],f[N],a[15],tjj[N],sum[N];
bool vis[N];
void pre(){
  vis[1]=mu[1]=1;
	int num=0;
	for (int i=2;i<=n;++i){
	  if (!vis[i]){prime[++num]=i;tjj[i]=i;mu[i]=-1;}
		for (int j=1;j<=num;++j){
		  if ((ll)prime[j]*i>n) break;
			vis[prime[j]*i]=true;
			tjj[prime[j]*i]=prime[j];
			if (i%prime[j]) mu[prime[j]*i]=-mu[i];
			else break;
		}
	}
}
int dfs(int k,int x,int v){
  if (k>cnt){
	  f[x]+=v;
		return mu[x]*f[x];
	}
	return dfs(k+1,x*a[k],v)+dfs(k+1,x,v);
}
int main(){
	int cas;
	scanf("%d",&cas);
	for (int i=1;i<=cas;++i){
	  scanf("%d",&ask[i]);
		n=max(n,ask[i]);
	}
	pre();
	for (int i=1;i<=n;++i){
	  sum[i]+=sum[i-1];
		if (mu[i]){
		  cnt=0;
			int x=i;
			for (;x>1;x/=tjj[x]) a[++cnt]=tjj[x];
			sum[i]+=mu[i]*dfs(1,1,mu[i]);
		}
	}
	for (int i=1;i<=cas;++i) printf("%d\n",sum[ask[i]]);
	return 0;
}
