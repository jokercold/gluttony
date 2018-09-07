#include<iostream>
#include<cstdio>
using namespace std;
#define N 5000
#define M 6000000
int A[N],B[N],hed[N],cur[N],dis[N],Q[N];
int val[M],Next[M],vet[M];
int num,S,T;
void add(int u,int v,int w){
  ++num;
	vet[num]=v;
	val[num]=w;
	Next[num]=hed[u];
	hed[u]=num;
}
void add_flow(int u,int v,int w){
  add(u,v,w);
	add(v,u,0);
}
bool bfs(){
  int hh=0,tt=1;
	for (int i=1;i<=T;++i) dis[i]=-1;
	Q[hh]=S;
	dis[S]=1;
	while (hh!=tt){
	  int u=Q[hh];++hh;
		for (int i=hed[u];i!=-1;i=Next[i]){
		  int v=vet[i];
			if (val[i]&&dis[v]==-1){
			  dis[v]=dis[u]+1;
				Q[tt]=v;
				++tt;
			}
		}
	}
	return dis[T]!=-1;
}
int dfs(int u,int low){
  if (u==T) return low;
	int used=0;
	for (int i=hed[u];i!=-1;i=Next[i]){
	  int v=vet[i];
		if (val[i]&&dis[v]==dis[u]+1){
		  int w=dfs(v,min(val[i],low-used));
			val[i]-=w;
			val[i^1]+=w;
			used+=w;
			cur[u]=i;
			if (used==low) return low;
		}
	}
	if (used==0) dis[u]=-1;
	return used;
}
int dinic(){
  int ans=0;
  while (bfs()){
	  for (int i=1;i<=T;++i) cur[i]=hed[i];
		ans+=dfs(S,1<<29);
	}
	return ans;
}
int main(){
  int n;
	scanf("%d",&n);
	for (int i=1;i<=n;++i) scanf("%d",&A[i]);
	for (int i=1;i<=n;++i) scanf("%d",&B[i]);
	int m;
	scanf("%d",&m);
	S=n+n+m+m+1;
	T=n+n+m+m+2;
	for (int i=1;i<=T;++i) hed[i]=-1;
	num=1;
	int ans=0;
	for (int i=1;i<=n;++i){
		add_flow(S,i,A[i]);add_flow(n+i,T,B[i]);
	  add_flow(i,n+i,1<<29);
		ans+=A[i]+B[i];
	}
	for (int i=1;i<=m;++i){
	  int k,c1,c2;
		scanf("%d%d%d",&k,&c1,&c2);
		add_flow(S,n+n+i,c1);
		add_flow(n+n+m+i,T,c2);
		ans+=c1+c2;
		for (int j=1;j<=k;++j){
			int x;
		  scanf("%d",&x);
			add_flow(x,n+n+m+i,1<<29);
			add_flow(n+n+i,x+n,1<<29);
		}
	}
  printf("%d\n",ans-dinic());
	return 0;
}
