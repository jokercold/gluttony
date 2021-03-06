#include<iostream>
#include<cstdio>
using namespace std;
#define M 4000100
#define N 3010
int n,m,num,S,T,ans;
bool map[N][N];
namespace Dinic{
	int Next[M],val[M],vet[M];
	int hed[N],q[N],cur[N],h[N];
	void add(int u,int v,int z){
  	++num;
		vet[num]=v;
		val[num]=z;
		Next[num]=hed[u];
		hed[u]=num;
	}
	void addflow(int u,int v,int z){
  	add(u,v,z);
		add(v,u,0);
	}
	bool bfs(){
		int tt=1,hh=1;
		for (int i=1;i<=T;++i) h[i]=-1;
		q[1]=S;h[S]=0;
		while (hh<=tt){
			int u=q[hh];
			++hh;
			for (int i=hed[u];i!=-1;i=Next[i])
			if (val[i]&&h[vet[i]]==-1){
				++tt;
				q[tt]=vet[i];
				h[vet[i]]=h[u]+1;
			}
		}
		return h[T]!=-1;
	}
	int dfs(int u,int low){
		if (u==T) return low;
		int used=0;
		for (int i=cur[u];i!=-1;i=Next[i]){
			int v=vet[i];
			if (h[v]==h[u]+1&&val[i]){
				int w=dfs(v,min(val[i],low-used));
				val[i]-=w;
				val[i^1]+=w;
				used+=w;
				cur[u]=i;
				if (used==low) return low;
			}
		}
		if (used==0) h[u]=-1;
		return used;
	}
	void dinic(){
		while (bfs()){
			for (int i=1;i<=T;++i) cur[i]=hed[i];
			ans-=dfs(S,1<<29);
		}
	}
}
void init(){
	using namespace Dinic;
	scanf("%d%d",&n,&m);
  S=n+m+1;
	T=n+m+2;
	num=1;
	for (int i=1;i<=T;++i) hed[i]=-1;
}
void build(){	
	ans=0;
	for (int i=1;i<=n;++i){
	  int money,k;
		scanf("%d%d",&money,&k);
		ans+=money;
		Dinic::addflow(S,i,money);
		for (int j=1;j<=k;++j){
		  int v,z;
			scanf("%d%d",&v,&z);
			Dinic::addflow(i,v+n,z);
		}
	}
	for (int i=1;i<=m;++i){
	  int money;
		scanf("%d",&money);
		Dinic::addflow(n+i,T,money);
	}
}
int main(){
	init();
	build();
	Dinic::dinic();
	printf("%d\n",ans);
	return 0;
}
