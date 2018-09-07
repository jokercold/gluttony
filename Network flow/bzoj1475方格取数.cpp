#include<iostream>
#include<cstdio>
using namespace std;
#define M 10100
#define N 1010
int dx[5]={-1,0,0,1};
int dy[5]={0,-1,1,0};
int n,num,S,T,ans;
int map[40][40];
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
	scanf("%d",&n);
  S=n*n+1;
	T=n*n+2;
	num=1;
	for (int i=1;i<=T;++i) hed[i]=-1;
}
void build(){	
	int black=0,white=(n*n+1)/2;
	for (int i=1;i<=n;++i)
		for (int j=1;j<=n;++j)
		if ((i+j)%2==0){
		  ++black;
      map[i][j]=black;
		}else ++white,map[i][j]=white;
	using namespace Dinic;
	ans=0;
	for (int i=1;i<=n;++i)
		for (int j=1;j<=n;++j){
		  int x;
			scanf("%d",&x);
			ans+=x;
			if ((i+j)%2==0){
				addflow(S,map[i][j],x);
        for (int k=0;k<4;++k){
				  int di=i+dx[k];
					int dj=j+dy[k];
					if (di<1||di>n||dj<1||dj>n) continue;
					addflow(map[i][j],map[di][dj],1<<29);
				}
			}else addflow(map[i][j],T,x);
		}
}
int main(){
	init();
	build();
	Dinic::dinic();
	printf("%d\n",ans);
	return 0;
}
