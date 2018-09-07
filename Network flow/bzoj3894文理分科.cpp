#include<iostream>
#include<cstdio>
using namespace std;
#define M 1000050
#define N 30050
int n,m,num,S,T,ans;
int dx[10],dy[10];
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
		//cout<<"haha"<<endl;
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
		//cout<<"----o"<<endl;
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
			//cout<<"haha"<<endl;
			ans-=dfs(S,1<<29);
		  //cout<<"YES"<<endl;
		}
	}
}
void init(){
	dx[0]=-1;dy[0]=0;
	dx[1]=0;dy[1]=-1;
	dx[2]=0;dy[2]=1;
	dx[3]=1;dy[3]=0;
	scanf("%d%d",&n,&m);
	S=n*m*3+1;
	T=n*m*3+2;
	using namespace Dinic;
	for (int i=1;i<=T;++i) hed[i]=-1;
	num=1;
}
void build(){
  using namespace Dinic;
  ans=0;
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j){
		  int x;
			scanf("%d",&x);
			ans+=x;
			addflow(S,(i-1)*m+j,x);
		}
  for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j){
		  int x;
			scanf("%d",&x);
			ans+=x;
			addflow((i-1)*m+j,T,x);
		}
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j){
		  int x;
			scanf("%d",&x);
			ans+=x;
			addflow(S,n*m+(i-1)*m+j,x);
			addflow(n*m+(i-1)*m+j,(i-1)*m+j,1<<29);
			for (int k=0;k<4;++k){
			  int di=i+dx[k];
				int dj=j+dy[k];
				if (di<1||di>n||dj<1||dj>m) continue;
				addflow(n*m+(i-1)*m+j,(di-1)*m+dj,1<<29);
			}
		}
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j){
		  int x;
			scanf("%d",&x);
			ans+=x;
			addflow(n*m*2+(i-1)*m+j,T,x);
			addflow((i-1)*m+j,n*m*2+(i-1)*m+j,1<<29);
			for (int k=0;k<4;++k){
			  int di=i+dx[k];
				int dj=j+dy[k];
				if (di<1||di>n||dj<1||dj>m) continue;
				addflow((di-1)*m+dj,n*m*2+(i-1)*m+j,1<<29);
			}
		}
  //cout<<"YES"<<endl;
}
int main(){
  init();
	build();
	Dinic::dinic();
	printf("%d\n",ans);
	return 0;
}
