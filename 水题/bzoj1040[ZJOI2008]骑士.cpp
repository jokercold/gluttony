#include<iostream>
#include<cstdio>
using namespace std;
#define N 1000005
#define ll long long 
int num;
int vet[N*2],Next[N*2];
int hed[N],f[N],val[N];
ll dp[N][2];
void add(int u,int v){
  ++num;
	vet[num]=v;
	Next[num]=hed[u];
	hed[u]=num;
}
void dfs(int x,int fa){
	//cout<<x<<" "<<fa<<endl;
  dp[x][1]=val[x];
	dp[x][0]=0;
	for (int i=hed[x];i!=-1;i=Next[i]){
	  int v=vet[i];
		if (v==fa) continue;
		dfs(v,x);
		dp[x][1]+=dp[v][0];
		dp[x][0]+=max(dp[v][1],dp[v][0]);
	}
}
int find(int x){
  if (f[x]!=x) f[x]=find(f[x]);
	return f[x];
}
struct node{
  int x,y;
}Q[N];
int main(){
  int n;
	scanf("%d",&n);
	for (int i=1;i<=n;++i) hed[i]=-1;
	for (int i=1;i<=n;++i) f[i]=i;
	int m=0;
	num=0;
	for (int i=1;i<=n;++i){
		int v;
		scanf("%d%d",&val[i],&v);
	  int rota=find(i),rotb=find(v);
		//cout<<rota<<" "<<rotb<<endl;
		if (rota!=rotb){ 
			add(i,v);
		  add(v,i);
		  f[rota]=rotb;
		}else Q[++m].x=i,Q[m].y=v;
	}
	ll ans=0;
	for (int i=1;i<=m;++i){
	  dfs(Q[i].x,0);
		ll t=dp[Q[i].x][0];
		dfs(Q[i].y,0);
    t=max(t,dp[Q[i].y][0]);
		ans+=t;
	}
	printf("%lld\n",ans);
	return 0;
}
